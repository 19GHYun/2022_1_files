
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
  
  if((stat(원본파일이름, &st_buf) < 0 ))
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






























