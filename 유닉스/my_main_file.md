
### touch 함수

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















