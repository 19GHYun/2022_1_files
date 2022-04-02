## exercise 2

**20194546 윤경호**

### 1. 팩토리얼을 계산하는 순환호출 함수 factorial에서 매개 변수로 5를 주었다면 최대 몇 개의 factorial 함수의 활성 레코드가 동시에 존재할 수 있는가?

  Answer. factorial(5)부터 factorial(1)까지 총 5개가 존재할 수 있다.

### 3. 다음 중 활성 레코드에 저장되지 않는 것은 무엇인가?

  Answer. 4번 순환호출의 순차번호 이다.
  
  1번과 3번 매개변수의 값과 지역변수는 스택으로부터 할당 받고, 2번 함수호출이 끝나고 복귀할 주소는 시스템스택에 저장되기 때문이다.
  
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

