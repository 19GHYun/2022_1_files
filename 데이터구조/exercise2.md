## exercise 2

**20194546 윤경호**

### 1. 팩토리얼을 계산하는 순환호출 함수 factorial에서 매개 변수로 5를 주었다면 최대 몇 개의 factorial 함수의 활성 레코드가 동시에 존재할 수 있는가?

  Answer. factorial(5)부터 factorial(1)까지 총 5개가 존재할 수 있다.
  
-------
### 3. 다음 중 활성 레코드에 저장되지 않는 것은 무엇인가?

  Answer. 4번 순환호출의 순차번호 이다.
  
  1번과 3번 매개변수의 값과 지역변수는 스택으로부터 할당 받고, 2번 함수호출이 끝나고 복귀할 주소는 시스템스택에 저장되기 때문이다.
  
-------
### 5. 다음의 순환호출 함수에서 잘못된 점은 무엇인가?

```
int recursive(int n)
{
  if( n==1 ) return 0;
  return n*recursive(n);
}
```

Answer. 이 경우 n이 1이 아닐 시, n * recursive(n)이 무한으로 호출이 된다.

해결을 한다면, n * recursive(n-1); 이런식으로 바뀌면 된다.

-------
### 7. 다음 함수를 sum(5)로 호출하였을때, 화면에 출력되는 내용과 함수의 반환값을 구하라.

```
int sum(int n)
{
  printf("%d\n", n);
  if (n<1) return 1;
  else return( n+sum(n-1);
}
```

Answer. 일단 화면에 출력되는 것은 printf("%d\n", n);이 출력 되므로
```
//는 반환값 계산임. 화면에 출력이 되지 않음.
5   //5+sum(4)     5+11 = 16 = sum(5)
4   //4+sum(3)     4+7 = 11 = sum(4)
3   //3+sum(2)     3+4 = 7 = sum(3)
2   //2+sum(1)     2+2 = 4 = sum(2)
1   //1+sum(0)     1+1 = 2 = sum(1)
0   //1     
```
이렇게 출력이 되고, 반환값은 16이 된다.

-------
### 9. 다음 함수를 recursive(10)로 호출하였을 때, 화면에 출력되는 내용과 함수의 반환값을 구하라.

```
int recursive (int n)
{
  printf("%d\n", n);
  if( n<1) return -1;
  else return( recursive(n-3)+1);
}
```

Answer. 역시 화면에 출력되는 것은 printf("%d\n", n); 이다.
```
//는 반환값 계산임. 화면에 출력이 되지 않음.
10  //1+recursive(7)    2 + 1 = 3 = recursive(10)
7   //1+recursive(4)    1 + 1 = 2 = recursive(7)
4   //1+recursive(1)    1 + 0 = 1 = recursive(4)
1   //1+recursive(-2)   1 + -1 = 0 = recursive(1)
-2  //-1                -1
```
이렇게 출력이 되며, 반환값은 3이다.

-------
### 11. 다음 함수에서 asterisk(5)를 호출할 때 출력되는 * 의 갯수는?

```
void asterisk( int i)
{
  if (i > 1){
    asterisk(i/2);
    asterisk(i/2);
    }
  printf("*");
}
```

Answer. 우선 이 함수를 보면 asterisk가 호출 될 때 * 이 한번 출력되며, 호출될 때의 i값이 1보다 크다면, 절반으로 각각 분열이 된다.

즉 asterisk(5)가 호출이 한번 된 후, asterisk(2.5) asterisk(2.5)로 2개로 분열이 되고,

2개의 asterisk(2.5)는 4개의 asterisk(1.25)로 분열이 되며

4개의 asterisk(1.25)는 8개의 asterisk(0.625)로 분열이 된다.

그 후 asterisk(0.625)는 1보다 작으므로 * 만 출력이 되고 분열을 하지 않는다.

결론적으로 * 는 asterisk(5) 한번, 2.5 2번. 1.25 4번 0.625 8번.. 즉 1 + 2 + 4 + 8 = 15. 15개의 * 이 출력되었다.

-------

### 13. 다음을 계산하는 순환적인 프로그램을 작성하시오.
```
int sum( int n)
{
  if( n == 1) return 1;
  else return ( n + sum((n-1) );
}
```

### 15. 순환 호출되는 것을 이해하기 위하여 fib함수를 다음과 같이 바꾸어서 실행하여 보라. fib(6)을 호출할 때 화면에 출력되는 내용을 쓰시오.
```
int fib(int n)
{
  printf("fib(%d) is called\n", n);
  if( n == 0 ) return 0;
  if( n == 1 ) return 1;
  return (fib(n-1) + fib(n-2));
}
```

```
실행 과정 및 결과.

fib(6)실행 -> fib(6) -> fib(5) + fib(4)

fib(5) 실행 -> fib(4) + fib(3) + fib(4)

fib(4) 실행 -> fib(3) + fib(2) + fib(3) + fib(4)

fib(3) 실행 -> fib(2) + fib(1) + fib(2) + fib(3) + fib(4)

fib(2) 실행 -> fib(1) + fib(0) + fib(1) + fib(2) + fib(3) + fib(4)

fib(1) 실행 -> return 1/ fib(0) + fib(1) + fib(2) + fib(3) + fib(4)

fib(0) 실행 -> return 0 / fib(1) + fib(2) + fib(3) + fib(4)

fib(1) 실행 -> return 1/ fib(2) + fib(3) + fib(4)

fib(2) 실행 -> fib(1) + fib(0) + fib(3) + fib(4).

fib(1) 실행 후 fib(0) 실행 -> fib(3) + fib(4)

fib(3) 실행 -> fib(2) + fib(1) + fib(4)

fib(2) 실행 -> fib(1) + fib(0) + fib(1) + fib(4)

fib(1) 실행 후 fib(0) 실행 -> fib(1) + fib(4)

fib(1) 실행 -> fib(4)

fib(4) 실행 fib(3) + fib(2)

fib(3) 실행 -> fib(2) + fib(1) + fib(2)

fib(2) 실행 -> fib(1) + fib(0) + fib(1) + fib(2)

fib(1) 실행 후 fib(0) 실행 후 fib(1) 실행 -> fib(2)

fib(2) 실행 -> fib(1) + fib(0)

fib(1) 실행 후 fib(0)실행하고 마무리.

결론적으로 순서는 6 5 4 3 2 1 0 1 2 1 0 3 2 1 0 1 4 3 2 1 0 1 2 1 0 의 순서이고,

출력 결과는

![image](https://user-images.githubusercontent.com/94778099/161405668-e56fbb6c-b66c-416e-83f5-4c143fb92236.png)

가 된다.
```









