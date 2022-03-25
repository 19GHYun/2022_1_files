## 20194546 윤경호 데이터 구조 1장 과제.

1장	자료구조와 알고리즘

프로그램에서 자료들을 정리하고 보관하는 구조를 자료구조라고 하며,
문제를 컴퓨터로 해결하는 과정을 알고리즘 이라고 한다.

자료구조와 알고리즘을 합치면 프로그램이 된다.

C언어에서 표현할 수 있는 자료형은 정수 실수 문자 배열 구조체가 있다.
ADT는 객체와 함수를 정의하며 새롭게 연산을 정의하는 것이다.

알고리즘의 성능을 분석 할 때 시간 복잡도를 쓰게 되는데,
여러가지 표기법이 있지만, 빅오 표기법은 간단하게 말 하자면,
2n제곱 + 2n + 2 라면, n이 엄청 커지면 결국 2n제곱에 비례하게 커지며, 상수는 별로 의미가 없어지므로 n제곱에 비례하게 커지며, 빅오 표기법으론 n제곱이 된다.



### 2. 사용자로부터 받은 2개의 정수 중에서 더 큰 수를 찾는 알고리즘을 의사코드로 작성해보자.

scanf (a b) //정수 a b를 받음.
if a  > b 
  return a
else if ( b > a ) 
  return b
else
  비교할 수 있는 값이 아님.
  
  
### 4. Set(집합) 추상 자료형을 정의하라. 다음과 같은 연산자들을 포함시켜라.

객체 : 정수의 범위들. 전화 번호부 같은 배열. Person[0] ~ Person[MAX_Number]

```
참고할 것.

Person에서 쓰인 구조체는

Person.name

Person.number

Person.age

를 가진다.

```

-------
```
Set Create(x) ::= 

Person Person[x] // 여기서 이 내용은 각각 name, number, age에 자료를 넣는 구조체임.
      
  return 0
  
```

```
Set Insert(x) ::=

if( Person[x] != "NULL") { Person[x+1] = Person[x] , Create[x] } //단 x가 Max_number면 안될 것.
                    
  else Create(x)

```
                    
```                    
Set Remove(x) ::= 

  Person(x) == "NULL"
  
```

```
Set Is_In(x) ::=  

if( Person[x] != "NULL") { printf("x번에는 자료가 있습니다.");}

  else printf("x번에는 자료가 없습니다");
  
```

```
Set intersection(x,y) ::=

if(person[x].name == person[y].name)

 printf(person[x].name);
                      
if(person[x].number == person[y].number)

 printf(person[y].number);
                      
if(person[x].age == person[y].age)

 printf(person[y].age);
                      
 //교집합의 뜻을, 두 자료가 같으면 출력하게 해 보았음.
```

```
Set Union(x,y) ::=

if(person[x].name == person[y].name)

 printf(person[x].name)
                      
else
                   
 printf(person[x].name + \n + person[y].name
                       
if(person[x].number == person[y].number)

 printf(person[x].number)
                      
else
                   
 printf(person[x].number + \n + person[y].number
                       
if(person[x].age == person[y].age)

 printf(person[x].age)
                      
else
                   
 printf(person[x].age + \n + person[y].age
                       
// 합집합이라 두 내용을 다 출력 해 보았고, 단, 같은 내용이면 한번만 출력되게 함.
```

```
Set Difference(x,y) ::=

if(person[x] == person[y])

 printf("두 자료의 내용이 같습니다.")
                      
else
                        
 printf("두 자료의 내용이 다릅니다.")
```                    
                  

### 6. 다음과 같은 코드의 시간 복잡도는? 여기서 n이 프로그램의 입력이라고 가정하자.

for(i = 1; i<n ; i *=2 )
  printf("Hello");


n을 숫자를 넣어서, 얼만큼 증가하는지 보면,

n이 4일때 2, n이 8일때 3, n이 16일때 4이므로,

log n에 비례하는 것을 알 수 있다.

O(logn) 이 된다.


### 8. 시간 복잡도 함수 n2 + 10n + 8을 빅오 표기법으로 나타내면?

n이 커지면 결국 n2에 비례하게 커지므로 답은,

3번 O(n2)


### 10.O(n2)의 시간복잡도를 가지는 알고리즘에서 입력의 개수가 2배로 되었다면 실행시간은 어떤 추세로 증가하는가?

간단하게 n2에 1넣으면 1, 2 넣으면 4가 나오니까.. 답은 4배로 증가한다.

3번 (4배)

### 12.다음의 빅오표기법들을 수행시간이 적게 걸리는 것부터 나열하라.

O(1), O(logn), O(n), O(nlogn), O(n2), O(2n), O(n!) 순으로 적게 걸린다.


### 14.다음은 실제로 프로그램에서 수행시간을 측정하여 도표로 나타낸 것이다. 도표로부터 이 프로그램의 시간 복잡도를 예측하여 빅오 표기법으로 나타내라.

| 입력의 개수 n | 수행시간(초) |
|:----:|:---------:|
| 2 | 2 |
| 4 | 8 |
| 8 | 25 |
| 16 | 63 |
| 32 | 162 |

입력은 전에 입력한거에 2배씩 늘어난다.

출력을 보면,
8 -> 2*3

25 -> 3*8

63 -> 4*16

162 -> 5*32

이정도의 비례로 값이 증가한다. 이것은 nlogn비례로 늘어나는 것이기 때문에,

O(nlogn).


### 16. 빅오 표기법의 정의를 이용하여 6n2 + 3n이 O(n)이 될 수 없음을 보여라.

n이 커지면 n2에 비례해서 커지기 때문이다. 3n은 의미가 없어짐.

빅오 표기법을 쓰면 O(n2)이 된다.



