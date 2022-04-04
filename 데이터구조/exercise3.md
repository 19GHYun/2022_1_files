## **조선대학교 컴퓨터공학과 20194546 윤경호**

### 83p 1번

다항식 6x^3 + 8x^2 + 9을 첫 번째 방법으로 표현하여 보라.

첫번째 방법 - 하나의 배열로 표현.

```
typedef struct{
  int degree;             //다항식의 차수
  float coef[MAX_DEGREE]; //MAX_DEGREE(다항식의 계수)는 101로 정의 되어있음.
} polynomial;
..
..
..

int main(void)
{
  polynomial a = { 3,{6, 8, 0, 9} }; //다항식 생성.
  ..
}

```

### 83p 2번

다항식 6x^3 + 8x^2 + 9을 두 번째 방법으로 표현하여 보라.

두 번째 방법 - 두개의 배열로 표현.

```
typedef struct{
  float coef;
  int expon;
} polynomial;
polynomial terms[MAX_TERMS] = {{6, 3}, {8, 2}, {9, 0}};

..
..
..

int main(void){
  int As = 0 , Ae = 2;
  ..
}
```

### 83p 5번

첫 번째 방법과 두 번째 방법으로 각각 특정한 x값에서 다항식의 값을 계산하는 함수 poly_eval(int x)을 작성해 보자.

#### 첫 번째 상황.

배열의 위치 만큼 x를 제곱해주면 됨. 그리고 들어가 있던 상수를 곱함.

```
#include <math.h> // pow 함수 선언

...

int poly_eval(Polynomial a, int x){ // 원래 poly_eval(int x)인데 약간 수정 해 보았읍니다.
  int result = 0;
  for(int i = 0; i < a.degree +1 ; i++){ //최고 차수가 4면 5번 반복됨.
    result = result + a.coef[i] * pow(x, i);  // 다항식의 계수 * x의 i제곱.
  }
  return printf("%d", result);
}
```

#### 두 번째 상황

```
#include <math.h>

...

int poly_eval(Polynomial a, int x int As, int Ae){ 
  int result = 0;
  for(int i = As; i < Ae + 1 < i++){  //항의 갯수만큼 반복.
    result = result + terms[i].coef * Pow(x, terms[i].expon); // 결과는 계수 * x^expon에 들어있는 최고차항.
  }
  return printf("%d", result);
}
```

### 2. 자료조사를 통해 '메모리의 구조'를 설명하고 95쪽 '동적 메모리 할당'을 참고하여 아래의 코드를 설명하시오

```
    float *p;                             //1
    p = (float*)malloc(sizeof(float));    //2
    *p = 36.5;                            //3
    free(p);                              //4
```


//1 float 타입의 포인터p 선언.

//2 float의 경우 4byte 이므로. 4byte의 동적 메모리를 할당 받는다. 더 많이 받을려면 sizeof 앞에 SIZE * sizeof.. 이런식으로 합니다.
    
    malloc는 시작주소를 반환하므로, SIZE * sizeof 이런식으로 된다면 배열의 구조가 됩니다.
    
//3 동적 메모리에 36.5라는 값을 할당 하였습니다. p가 가르키는 값은 36.5입니다.

//4 동적 메모리를 반납합니다. malloc을 사용하여 할당받은 메모리는 꼭 반납을 해줘야합니다.

### 3. 학생정보 관리프로그램을 작성해보시오. 아래의 조건이 맞아야함.
    1. 학생정보를 나타내는 구조체는 이름,학번,평점을 저장할 수 있어야함.
    2. 5명의 학생에 대한 구조체를 동적할당
    3. 학생 이름을 함수의 인자값으로 주었을 때 그 학생의 학번과 평점을 출력할 수 있는 함수

```
#define _CRT_SECURE_NO_WARNINGS //strcpy 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define SIZE 5

typedef struct PersonInformation{ //구조체 Person
 char name[20]; //이름
 int codename; //학번
 double score; //평점
} Person;

void printPerson(char *name2, Person a[]){  //인자값으로 이름과 배열 받음.
  for(int i = 0; i < SIZE ; i++){           // SIZE만큼 반복
    if(strcmp(name2, a[i].name) == 0){      // 이름이 똑같으면 그 때 맞는 배열들 출력.
      printf("%d %0.1f \n", a[i].codename, a[i].score);
    }
  }
}

int main() {

  char char1[20];
  char char2[20];
  int num1;
  float num2;
  
  Person *p;              

  p = (Person *)malloc( SIZE * sizeof(Person));
  if ( p == NULL){
    fprintf(stderr, "메모리가 부족해서 할당할 수 없습니다. \n");
    exit(1);
  }

  for(int i = 0; i < SIZE ; i++){
    printf("%d번째 사람의 이름, 학번, 평점을 입력. 예시) 홍길동 20194546 3.5\n", i+1);
   scanf("%s %d %f", char1, &num1, &num2 );
   strcpy(p[i].name, char1);
   p[i].codename = num1;
   p[i].score = num2;
  }
 
  while(1){
    getchar();    //입력버퍼 제거
    printf("검색할려는 사람 이름을 적어주세요. 프로그램 종료는 exit.\n");
    scanf("%s", char2);
    if(strcmp(char2, "exit") == 0){
      printf("\n프로그램을 종료합니다.");
      break;      
    }
    printPerson(char2, p);
    }
  free(p);
 return 0;
}
```

실행결과. 실행환경 우분투 컴파일러

![image](https://user-images.githubusercontent.com/94778099/161542450-273f3098-eb4c-4a7b-acbe-edc3de917c42.png)
