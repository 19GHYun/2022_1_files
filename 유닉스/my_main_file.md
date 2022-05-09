
## touch 함수

touch 함수는
```
touch f1
ㄴ cmd ㄴargv[0]
if(utime(?,NULL) == 0)   // 
  return; //정상실행
//에러발생
if (errno !=? ) // 다른 에러 원인이면
  에러 원인 출력 후 리턴.

```
로 구성.

if(utime(?,NULL) -> ?는 argv[0]. 즉 f1의 이름임.

f1의 이름이 있고 타임이 NULL이면 접근시간과 수정시간은 둘 다 현재시간으로 수정함.
 
time이 NULL이 아니면 times에 의해 지시된 구조체 값으로 설정이 됨. -? *이해가 안됏음.*
  
->>> 에러 원인 중에서
1) 다른 에러 인 경우 (접근권한, 글자 크기 초과 등..)
->에러 원인 출력하고 리턴 PRINT_ERR_RCT..

2)파일이 존재하지 않는경우
->새로 파일을 만든다.

-->> errno 은 전역변수임. errno.h 헤더파일 추가하면 바로 사용 가능
if(errno == ENOENT)  // Error NO Entry -> 파일이 존재하지 않으면? 라는 뜻임.

그럼 저기 if는 if(errno != ENOENT) 해야 다른 에러 들인 경우가 됨.

```
즉, if(errno != ENOENT)
      PRINT_ERR_RET..
    else
      파일 새로 생성. 크키가 0이고 접근권한은 0644인..
```   
파일을 새로 생성할려면 creat 함수를 써야 함.
```
int fd;
fd = creat( ?(파일이름) , ?(접근권한))
if(fd < 0)   // 만일 접근 권한이 없어서 못만들면 에러가 생기기에, 체크하는 구간.
  에러 원인 출력 후 리턴.
```
한줄로 줄인다면..
if((fd=creat(?,?)) <0 )

그리고 우리는 파일크기가 0인걸 만들기때문에 저대로 쓰면 파일 수정을 하는 창으로 넘어감

close(fd)하면 바로 파일 닫아짐.

이걸 다 한문장으로 하면?

if((A) ||(B) )
A는 if(errno != ENOENT) B는 if((fd = creat(?,?)) < 0).






## cat 함수

```
void cat
  fd와 len를 int 형 변수로 선언
  buf[SZ_FILE_BUF]사이즈 char형 선언
  
  if((fd = open(파일이름 , O_RDONLY))<0 ) 이면
    에러원인 출력 후 리턴.
  while((len = read(fd, buf, SZ_FILE_BUF)) > 0 ) {
    if(write ( STDOUT_FILENO, buf, len) != len) {
      len = -1;
      break;
    }
  }
  
  if( len < 0 )
    perror(cmd);
  close(fd);
```
O_RDONLY -> 읽기전용

여기서 쓰이는 read write open close 은 유닉스 API 함수를 이용한 것임. (따로 헤더파일 이런거 필요 없는듯 함.)

->한번에 다이렉트로 불러오니까 속도면에서 빠를수도 있다. 

C++ 함수를 쓰면 unix API함수 쓰는거임. 유닉스 API함수 없이 지들끼리 못쓴다고 생각.

read -> SZ_FILE_BUF 만큼 읽어서 buf라는 주소에 저장

파일을 읽을때
ㅁ        ㅁ       ㅁ       ㅁ
1024 kb  1024kb   1024kb   100kb

이렇게 읽게 되는데, 여기서 1024kb는 SZ_FILE_BUF크기와 같음

일반적으로 8kb씩 읽는게 효율이 조타!

------

len = read... 에서 len은 실제로 읽어진 갯수가 리턴이 됨.ㅣ

write(STDOUT_FILENO(화면) , buf , len)
화면에다가 가져다가 쓰는데 buf에다가 len만큼 작성을 함. 
리턴값은 실제 쓴 갯수가 됨.

read write 의 맨 앞에 값은 핸들값이라고 함. fd랑 STDOUT_FILENO->화면 을 뜻함.

------

perror(cmd) 왜 PRINT_ERR_RET를 안쓰는가?

->PRINT.. 이건 리턴을 해버리기 때문임. 에러가 떠도 파일은 닫아줘야 하므로 에러 원인만 출력하고 파일을 닫음.

------

ㅁ -> 1024kb라고 했음.
len = read(...)에서 1024만큼 읽게 됨. len에 1024리턴.

read -> 1024만큼 읽음. 이걸 계속 반복함.

파일을 다 읽으면 len에는 0이 리턴이 됨.(에러 생기면 len에 -1 리턴.)

while 비껴가고 if 비껴가고 close 하게 됨. 

------

시험 예상 문제. 파일 크기는 3KB + 100 이고 SZ_FILE_BUF은 1024이다.

몇번 읽고 출력하고, 얼마를 읽을까?

-> 5번 읽혀짐. 그 이유는 1024 1024 1024 100 0. 이렇게 5번 읽혀짐. 0이 읽혀져야 다 읽었다는 것을 알게 됨.

while반복 조건에서 에러가 떠버리면 len에 -1이 리턴. 

while 안 if 구간에서 에러가 나는 법? -> USB 읽고 있는데 USB 뽑아버리기.

------

파일 open 했으면 close도 잘 해주자.

유닉스는 아주 훌륭한 운영체제라 동적할당 안해도 알아서 회수 하고, 알아서 close 한다.

그렇다면 ??? : 유닉스 좋은데 close 안해도 되는거 아니냐?

-> 서버 프로그램일땐 반환 일일히 그때그때 잘해야 한다. 아무튼 동적할당 받고 파일 open 햇으면 그때 끄때 close free 해줘라.

## copy함수

```
사용법cp f1 f2

cp
  int rfd, wfd, len;
  char buf[SZ_FILE_BUF];
  struct stat st_buf;
  
  if((stat(원본파일이름, &st_buf) < 0 ))||  // &st_buf에 밑줄 긋고 여기에 들어갈 건? 주소 넘기는거 제대로 체크 ㄱ
    ((rfd = open(원본파일 이름, O_RDONLY)) < 0 ))
    에러 출력 후 리턴.
  if((wfd = creat(복사된 파일 이름, st_buf.st_mode)) < 0 ){
    에러원인 출력; rfd를 close(); return;
  }
  while((len = read(rfd, buf, SZ_FILE_BUF)) > 0) {
    if(write(wfd,buf,len) != len){
      len = -1;
      break;
    }
  }
  if (len < 0)
    perror(cmd);
  close(rfd); close(wfd);

```
while((len = read(rfd, buf, SZ_FILE_BUF)) ..
-> if(wrtie(wfd,buf,len)...

-> buf에 읽어놓고, wfd에 buf에 읽은걸 쓴다.
즉 cp f1 f2 라면, f1 -> buf ->f2 의 순으로 복사가 된다.

wfd = creat(복사된이름, st_buf.st_mode)) -> 원본파일 접근권한은 st_buf.st_mode에 잇음.

-> stat(원본파일, &st_buf) <에서 st_buf.st_mode에 들어옴.



###open함수.
대충.. open(

oflag -> O_RDONLY : read-only-로 open or create.
          O_WRONLY : write-only 로 open or create.
          O_RDWR
          O_APPEND
          O_CREAT
          O_EXCL
          O_TRUNC
          define으로 정의된 정수값들임.이렇게 7개가 잘 쓰임. 자료 참고.
ex) open(pathname , O_RDONLY);
->읽기모드로 열고, 파일 없으면 에러 - 파일열기

open(pathname, O_WRONLY | O_CREAT| O_TRUNC , mode); 
  ->쓰기모드(O_WRONLY)로 열고, 파일 없으면 생성(O_CREAT), 있으면 파일 내용 삭제 후 파일크기를 0(O_TRUNC)으로 설정. - 저장하기.
  
open(path, O_WRONLY | O_CREAT | O_EXCL, mode);
  ->쓰기모드(O_WRONLY)로 열고, 파일 없으면 생성(O_CREAT), 있으면 에러(O_EXCL) : (새 이름으로 저장하기)
  
open(pathname, O_WRONLY | O_CREAT | O_APPEND, mode);
  ->파일 끝에 덧붙이기 모드로 열고, 파일 없으면 새로 생성 : (로그 파일 열기)

open(pathname, O_RDWR);
  -> 읽고/쓰기 모드(O_RDWR)로 열고, 파일 없으면 에러.
  
open(pathname, O_RDWR | O_CREAT, mode);
  ->읽고 쓰기모드(O_RDWR)로 열고, 파일 없으면 생성(O_CREAT)
  DB파일 또는 기존 파일을 읽고 쓰고자 할 경우.


### creat 함수

write only로만 열림. -> 0644

-> 사실 open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode); 과 같은 기능임.

### lseek함수.

off_t lseek(int filedes, off_t offset, int whence);
->리턴은 옮겨간 위치 값.

int filedes -> 파일 핸들 값.

whence에 들어가는거 -> seek_set - file offset이 file시작(0)위치부터 offset.
                    seek_cur - file offset이 현재 position값 + offset.
                    seek_end - file offset이 파일 크키(파일의 마지막 바이트 다음 위치) + offset. offset은 음수 가능.

파일 끝 위치 찾는법 -> seek_end 선언 offset 0주면 리턴은 파일의 끝임.

배열 a[0], a[1] 있으면 맨 끝은 a[2]. 리턴은 2가 됨.

ex -> lseek(STDIN_FILENO, 600, seek_set)

-> 하면 600이 리턴이 될 것임.

read(rfd, buf, SZ_FILE_BUF))
↑
이때의 위치 주솟값 &st를, buf 대신에 넣음.

### ls 명령어 분석

r - 디렉토리에 Read Permission만 있으면 누구든 directory 읽기 가능. ls -l

w - 디렉토리에 write/execute Permission 있어야 디렉토리 아래에 있는 파일을 만들거나 생성, 제거 가능. cp rm

x - 디렉토리에 execute 퍼미션 있어야 그 디렉토리를 지나갈 수 있음. /home/a2345678/up/cmd



OS에는 2가지로 나뉨. Kernel과 System Program 을 합친게 운영체제다.

시스템프로그램은 시스템을 관리하고 제어하는 프로그램의 집합.(제어판)

커널은 컴퓨터가 부팅될때 커널파트를 메인메모리에 깔아둠. 메인메모리에 함수들을 깔아놓는다. 그런 거대한 함수들의 집합을 kernel이라고 한다. 라이브러리 함수처럼 불러서 쓸수있음. 즉 API함수들이 포함이 됨.

커널 - File I/O, 네트워크, 디바이스 드라이버, Process 관리, 메모리관리, Virtual memory, 스케줄링 알고리즘..............

가장 많이 잡아먹는게 앞에 2개임. 허허

아무튼 이런것들이 함수 집합으로 존재하는걸 통틀어서 Kernel이라고 한다.

ls 사용 예시.

ls
ls-l
ls ../pr4
ls -l ../pr4

ls -l -a // 옵션에러
ls ../jhshim //디렉토리 없음 에러
ls /home/jhshim //접근권한 에러
ls a b c // 인자 개수 에러

ls 함수(대략적으로 한줄씩 설명)
```
char *path;
DIR *dp; //디렉토리 핸들(디렉토리도 하나의 특별한 파일이다.)

//디렉토리 이름을 안줬으면 현재 디렉토리 설정. path -> "."
path = (argc == 0 ) ? "." : argv[0];
//ls 또는 ls -l인 경우 argc = 0, ls ../up 또는 ls -l ../up인 경우 argc = 1
//ls 또는 ls -l이면 path -> "."
//ls ../up 또는 ls -l ../up 인 경우 path -> "../up"

if((dp = opendir(path)) == NULL) // 디렉토리 열기.
  PRINT_ERR_RET();  // 존재하지 않는 디렉토리면 file not found 출력. //읽을수 없으면 permission denyed 뭐 이런식으로..
//예)ls 또는 ls ../up인 경우 optc = 0, ls -l 또는 ls -l ../up인 경우 optc = 1

if(optc == 0 )
  print_name(dp);
else
  print_detail(dp, path); // -l 상세출력.
  
closedir(dp);

```

```

static void print_name(DIR *dp);
{ //디렉토리의 모든 파일에 대해 이름만 출력하기.
  struct dirent *dirp;
  int max_name_len, num_per_line, cnt = 0;
  //max_name_len : 가장 긴 파일이름 길이 +4(이름 뒤 여유공간)
  //num_per_line: 한 줄에 출력할 수 있는 총 파일 이름 개수.
  get_max_name_len(dp, &max_name_len, &num_per_line);
  
  while((dirp = readdir(dp)) != NULL ) {
    printf("%-*s", max_name_len, dirp->d_name);
    //%-*s 는 좌 맞춤임. 한글에서 왼쪽으로 땡겨서 쓰는 그거임. -가 빠지면 우 맞춤이 됨. *대신 20이면  20칸 만큼 좌/우로 넘기는 것임. 근데 이걸 변수로 쓰는데 *은 max_name_len에 맞춰지고 s는 dirp->d_name 에 맞춰짐.
    
    if (( ++cnt % num_per_line) == 0 ) // cnt가 num_per_line의 배수이면,
      printf("\n");
    //cnt: 현재까지 출력한 파일 개수.
    //한 줄에 출력할 수 있는 파일 이름의 개수만큼 이미 출력 했으면 줄바꾸기임.
  }
  //마지막에 줄 바꾸기 문자 출력함.
  //단, 앞에서 이미 한 줄에 출력할 수 있는 파일 이름의 개수만큼 이미 출력하여 줄 바꾸기 했으면 또 다시 줄바꾸기 하지 않음.
  if((cnt % num_per_line) != 0 ) // cnt가 num_per_line의 배수가 아닐때만.
    printf("\n");
}

```
```

static void
get_max_name_len(Dir *dp, int *p_max_name_len, int *p_num_per_line)
{
  struct dirent *dirp;
  int max_name_len = 0; // 가장 긴 파일이름 길이.
  
  //모든 파일 이름을 읽어 내 가장 긴 이름의 길이를 결정함.
  while((dirp = readdir(dp)) != NULL ) {
    int name_len = strlen(dirp->d_name);
    if(name_len > max_name_len)
      max_name_len = name_len;
   //파일 이름 길이가 제일 긴거보다 크면 최신화. 파일 끝까지 반복.
  }
  rewinddir(dp); //안해주면 큰일남. 꼭 해주기. print_name에서 다시 dp 읽어야해서 리와인드 해줘야함.
  //가장 긴 파일이름 + 이름 뒤의 여유 공간.
  max_name_len += 4;
  //한 줄에 출력 할 파일이름의 개수 결정.
  *p_num_per_line = 80 / max_name_len;
  *p_num_name_len = max_name_len;
}

```















