
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
```
//ls -l처럼 상세정보 출력..
static void
print_detail(DIR *dp, char *path)
{
  struct dirent *dirp;
  
  while((dirp = readdir(dp)) != NULL )
      print_attr(path, dirp->d_name);
}


```
print_attr은 강의자료 참고하자


exit함수.
exit랑 _exit 있는데 전자꺼를 쓰자.

wait 함수..

### run 함수.

외부 명령어 쓸 수 있게 해준다.ex) gcc, make ,more, vi, man, find....

내부 명령어가 아닌 경우, 원래 있던 "지원되지 않은 명령어 입니다."를 지우고 run_cmd(); 써서 사용함.

```

void
run_cmd(void)
{
    pid_t pid;
    
    if( (pid = fork() ) <0 )
        PRINT_ERR_RET();
    //프로그램 복제.(cmd가 2개가 되고 동시에 실행됨.)
    //fork함수에서 부모 자식 둘다 복제가 됐기 때문에 fork가 성공적으로 끝나면 둘다 실행위치는 똑같이 fork 리턴부터 시작함.
    //리턴값이 0이면 자식이고 0보다 크면 부모다.
    //부모한테는 pid가 0보다 큰 프로세스 아이디가 발급 됨 자식은 0
    
    else if( pid == 0){ //자식 프로세스면..
        int i, cnt = 0;
        chat *nargv[100];
        
        nargv[cnt++] = cmd;
        for(i = 0; i < optc ; ++i)  //argc는 개수 argv[]는 포인터배열.
            nargv[cnt++] = optv[i]; //int main(int argc, char *argv[])가 쓰이는 이유. char* 를 포인터 써서 char* argv[]임. vi에디터에게 char *argv[]를 보내게 됨.
        for(i = 0; i < optv ; ++i)  //우리가 cmd에서 쓸때 토큰 자르고 앞에서부터 cmd, optv, argv 자른건 전역변수들. 이 것들을 nargv[](새로운거)에넣음.그리고 vi에 전달을 해줌.
            nargv[cnt++] = argv[i]                        //그래서 포인터에 포인터인듯?
        nargv[cnt++] = NULL;
                                    //환경변수... cd 제일 처음에 있는 파일들과, . 랑 .. 임. 환경변수가 있어야 하는 이유가, 우리가 그냥 일반적으로 cmd 치면 cmd 실행 되는 이유가 
                                    //.가 있어서임. 그래서 vi를 실행할려고 할때 환경변수가 있어서 그곳 어딘가에 있는 vi를 실행시켜준다.PATH..
                                    
        if(execvp(cmd, nargv) < 0 ){//execvp호출되고, vi의 메인 함수가 돌기 시작. 자식 프로그램은 사라진다(바꿔치기 했으니까)..
        perror(cmd); // PRINT_ERR_RET()호출하면 안됨.
        exit(1);    //왜냐하면 return이 아니라 exit 해야해서 (자식 프로그램이 
        }
    }
    
    else{ // pid>0인경우. 즉 부모 프로세스.
        //자식(pid)이 종료될 때까지 대기
        if(waitpid(pid, NULL, 0) < 0 ) //자식이 죽으면 리턴이 되고, 아래쪽 실행 0이 리턴되면 정상. 0보다 작으면 비정상. NULL 대신 int a 선언하고 &a로 넣으면 종료되고 리턴되는 값을 알 수 있다. 죽은 원인을 알 수 있다.
            PRINT_ERR_RET();
        //자식 프로세스가 종료되면 waitpid()는 자식 프로세스의 pid값을 리턴.
    }
    //부모가 자식 종료를 기다리지 않으면 자식은 Zombie프로세스가 됨.
}

```

bash가 cmd를 실행시키고, cmd가 vi를 실행시킴. bash - cmd의 부모, cmd - vi의 부모.

그런데 cmd에서 vi로는 바로 실행을 못시키고 일련의 과정이 있다.

cmd를 복제해서(fork()) 또다른 메모리에 붙여넣기. 내용은 똑같은데, 주소는 다름.

그 복제한 cmd를 vi로 바꿔치기 한다. 바꿔치기 할때 쓰는 함수는 execvp().

사실 배쉬에서 cmd 실행할때도 똑같다.. fork로 복제하고 exec()로 cmd를 실행시킴.



-------------------


API의 약자는 어플리케이션 프로그래밍 인터페이스

윈도우에서 API를 유닉스에선 System Call함수 라고 함.

좀비프로세스 관련해서 잘 알고 있어야할듯.

sprintf(buf, "%s %d", "abc",2).. - 메모리에 가져다가 씀. - ls에서 잘 씀.

printf- 화면에 출력. fprintf는 파일에 씀.

sscanf(buf, "%s %d", newbuf, &i).. newbuf에 abc가 들어가고, i에는 2가 들어감.

sscanf도 메모리에서 읽는거고 fscanf는 파일 scanf는 화면..

int sec = atoi(argv[0]) 함수임. Aㅏ스키 문자를 to int형으로 . a to i.. 이것도 더 간단한데,

sscanf(argv[0], "%d", &sec)랑 똑같음.

메인 -> A -> B -> C..

C에서 바로 메인으로 점프가 가능?


Set Jump, long Jump 사용하면 가능.

```
jump_buf jb; //<- 선언해야 하는 변수임. 전역변수인듯?

메인에다가

int jmpret;

jmpret = setjmp(jb);
if(jmpret != 0) {
    if(jmpret == -1 )
        Print error 1;
    else if(jmpret == -2)
        Print error 2;
    }
 while(1){
    A();
    process next...;
 }
 
 ```
 
 A()가 불리고, A에서 B가 불러지고..
 
 B에 C함수랑 D함수가 있다.
 
 ```
 
 C
 
 if(error)
  longjmp(jb, -1);
 
 ```
 
 ```
 D
 
 if(error)
  longjmp(jb, -2);
 
 ```
 
 여기서 longjmp가 불리면, 메인에 있는 jmpret = setjmp(jb)에 리턴이 됨. C에선 -1로 리턴.. D에선 -2로 리턴..
 
 그리고 리턴이 됏으면 에러처리 하고 다시 while문 반복수행 함.
 
 단 longjmp의 리턴값을 0으로 하면 안됨. 왜냐면 처음 리턴할때 0이 리턴되기 때문.
 
 
-----------

프로그램간 통신.

cmd to server 이랑 server to cmd 의 fifo 파일.

키보드 -> cmd -> fifo_c_to_s큐 -> server ,

server -> fifo_s_to_c큐 -> cmd -> 모니터.

대충 서버에서 프로그램으로 통신 방법.

char *s_to_c = "fifo_s_to_c"

1. 서버에서 open(s_to_c, O_WRONLY)(쓰기용)로 오픈,

2. 동시에 cmd에서 open(s_to_c, O_RDONLY)(읽기용)로 동시에 오픈.

2-1.파일 이름이 같기 때문에 메시지 큐에 닿을수 있다.(포인터라서 그런거도 잇는듯).

3.먼저 호출 되면 먼저 온 사람이 대기상태에 돌입(상대편이 오기 전까지) 운영체제에서 관리하는듯?.

4.그리고 read write 함수를 써서 큐에 정보를 넣고 뺌.

4-0. 서버에서 out_fd = open(s_to_c, O_WRONLY), cmd에서 in_fd = open(s_to_c, O_RDONLY)실행.

4-1.서버에선 write(out_fd, buf, len)이런식으로 씀.-> 큐에 정보가 저장이 됨.

4-2.cmd에선 len = read(in_fd, buf, BUF_SIZE)로 읽어들임.

4-3. out_fd와 in_fd가 0이냐 1이냐에 따라서 키보드에서 읽고 모니터에서 쓰는지, 키보드에서 쓰고 모니터에서 읽는지 할 수 있다. (파일 핸들이 뭐냐에 따라 어디에 쓰고 읽는지 알 수 있다).

5. 통신을 끝낼땐 서버(보내는쪽)에서 close(out_fd)하면, 프로그램에서 read를 하면 0이 리턴이 됨. 이걸로 통신이 끝났다고 인식하고 프로그램에서도 close(in_fd)를 호출함.

그렇다면 프로그램에서 서버로 보낼땐?

0. char* c_to_s = "fifo_c_to_s"

1. 서버에서 in_fd = open(c_to_s, O_RDONLY)호출

2. 프로그램에선 out_fd = open(c_to_s, O_WRONLY)호출.

2-0. 양방향 통신이라면 위에꺼 서버 프로그램 각각 in out 다 호출 해야함.

3. 서버에서 len = read(in_fd, buf, BUF_SIZE) 호출.

4. 프로그램에서 write(out_fd, buf, len) 호출.

5. 서버에서 read(in_fd, BUF_SIZE) 하는데, 프로그램에서 close 호출하면 0이 리턴되서 close이 됨.

6. 프로그램에서 그만 보내고 싶을때 close(out_fd)호출.

실습 11장 11번 중요. 두 프로그램에 다 있어야 하는 것임.

11장 12번. srv1.c 파일 

중요한거.

1.connect_to_clinet() 연결.

2.클라이언트 -> 서버 메세지 수신 문장

3. 서버 -> 클라이언트 메세지 송신 문장.

4.dis_connect() 끊기.

```
strncmp(cmd_line, "exit", 4) == 0 에 관하여, 
```
왜 strcmp 중간에 n이 있는가?. 일단 n은 문자열의 개수까지 비교함. 4가 4개를 뜻함. 

1. exit hahaha 이런식으로 있어도 strcmp면 exit되버림.

2. exit 엔터 까지 넘어갈수 있어서 안될수 있어서... 아무튼 strncmp 써야한다.


```
sprintf(ret_buf, "server: %s", cmd_line); //서버가 프로그램에게 문자열을 보냄.
```

11장 13번.

13 14번은 서버에서 쓰이는 함수임.

```
connect_to_client()함수에서..

in_fd = open(c_to_s, O_RDONLY);
if (in_fd < 0)
    print_err_exit(c_to_s);         //char *c_to_s = "fifo_c_to_s"
          ...1
    
out_fd = open(s_to_c, O_WRONLY);
if(out_fd < 0)  // 위에 in_fd<0과 같이 이런 경우는 open이 잘못된 경우라 에러임.
    print_err_exit(s_to_c);         //char *s_to_c = "fifo_s_to_c"
          ...2
```

이건 서버쪽 에서 클라이언트 쪽임. 먼저 호출된 곳은 반대편을 기다림. 클라이언트 프로그램을 실행해서 연결하기 전까지 in_fd = open... 이랑 out_fd = open.. 에서

return을 안하고 있음. 둘다 호출이 다 되어야 리턴이 되서 in_fd에 값이 들어감.

11장 14번.

dis_connect() 함수에서..

close(out_fd);
close(in_fd);

개간단함

11장 15번.

파일에서 큐로 온거. 서버가 읽는 문장임.

len = read(in_fd, cmd_line, SZ_STR_BUF);

cmd_line에 SZ_STR_BUF만큼 읽어라.. in_fd는 헤드

클라이언트를 컨트롤C로 강제 종료 되거나, 정상적으로 종료되면.. 아무튼 프로그램이 죽으면 자동으로 close을 보냄(운영체제가 해줌). 그렇다면 return되는 len은 0.

물론 close되도 리턴은 0.

널 문자를 제외한 문자 갯수가 리턴이 됨. if ABC라면 len은 3 

if(len <= 0 )
  break;
  
cmd_line[len] = '\0'; //받고나서 문자열로 만들어 줘야함.

아래는 큐에서 파일로. 서버가 보내는 문장임.

if(write(out_fd, ret_buf, len) != len)
    break;

write의 리턴값은 실제로 읽는 길이.



11장 16번 클라이언트 프로그램.

connect_to_server();
single_process();
disconnect();
....

single_process() 함수.
    while무한루프
        if(input_send() < 0 ) break; // 키보드에 읽어서 서버로 보냄.
        if(recv_output() < 0 ) break; // 서버에서 메시지 받아 화면에 출력한다.
        
        
11장 17번

connect_to_server() 프로그램 -> 서버 연결 함수.

out_fd = open(c_to_s, O_WRONLY); 클라 -> 서버 연결        
if (out_fd <0) 
    print_err_exit(c_to_s);
    
in_fd = open(s_to_c, O_RDONLY); 서버 -> 클라 연결.
if(in_fd <0)
    print_err_exit(s_to_c);
        
11장 18번

input_send()함수 프로그램에서 서버로 보내는 것.

len = read(0, cmd_line, SZ_STR_BUF); // 0은 키보드 1은 출력용 2는 에러가 떳을대 출력용. 1 2 는 모니터.
                                      //SZ_STR_BUF만큼 읽음. cmd_line에 적혀잇는걸. 키보드로 읽는다.
if(len <= 0) return len; // 컨트롤 Z 누르면 생기는 그런 일..                                      

//아래는 서버로 전송하는 코드.
if(write(out_fd, cmd_line, len) != len)
  return -1;
return len;

recv_output() 함수. 서버에서 프로그램으로 보낸걸 받음.

len = read(in_fd, cmd_line, SZ_STR_BUF);// input_send에서 엔터 치기 전까지 키보드로 입력 하는 중. 또는 보내자 마자 서버가 처리 못했을때 len = read.. 에서 스톱되어 있음.
if(len <0 ) return len;                 //아무튼 read가 깨어나서 일 하면 리턴이 됨.

if(write(1, cmd_line, len) != len) // 화면에 출력
  return -1;
return len;


프로그램 죽이면 다른곳도 죽는지 확인하기.


-------

O_REONLY 인가 이 부분 있는곳 시험에 나올듯???

그리고 실습 뒤부분에 테스트하는곳 잘 기억 해두자...

-------

cmdc1와 srv2..



단순하게 만든다. 파일핸들을 0과 1로 할 것.

그런데 그냥 0과 1로 해서 키보드/모니터로 하면 내가 원하는 큐에서 뺴오는게 안되고, 단순하게 키보드-모니터 관계가 됨.

그렇다면 우리가 원한 큐에 0과 1로 이어버리는법은?

Tabkes for Open Files:UNIX 쪽 참고하자. 매우 중요함.

fd flags 잇는 칸. 왼쪽에 0 1 2 는 인덱스임. 0은 키보드, 1 2 는 모니터... 거기에 있는 포인터를 쫒아가서 해당 디바이스를 찾아감.

3은 우리가 가정한 in_fd임. 여길 포인터 쫒아가면 큐가 나오게 됨.

우리가 fd 0의 포인터를 키보드로 되어있는게 아닌, 큐를 향하는 포인터를 복사한다면? -> 복사할때 쓰는 함수는 int dup2(int fd1, int fd2);...

dup2함수 설명

dup2(3,0) -> fd1과 fd2가 같으면 바로 리턴,

fd2(0)이 기존에 열려진 파일이면 close(fd2(0))함.

fd1(3)이 포인트하는 포인터를 fd2(0)에 복사.

쉽게 dup2(3,0) 하면 0위치에 3의값이 복사가 된다. 

그러면 fd3은 필요가 없자너? -> close 따로 해준다.

단 둘다 close되서 가르키는 포인터에 있는 count값이 0이 되면 큐가 닫힘. 두개 연결되면 카운트2, 하나면 카운트1 이런형식이다.

------
본론

in_fd = open("fifo_c_to_s", O_RDONLY);

out_fd = open("fifo_s_to_c", O_WRONLY);

dup2(in_fd,0) // 0이 in_fd를 가리키게 함. 서버 <- 클라이언트

dup2(out_fd,1) // 1이 out_fd를 가리키게 함.  서버 -> 클라이언트

dup2(out_fd, 2) // 2이 out_fd를 가리키게 함. //2는 모니터로 출력하는 에러.. 서버 -> 클라이언트

close(in_fd); close(out_fd); //닫아주면 됨.(카운트가 0이 되지 않으므로 괜찮음)



















