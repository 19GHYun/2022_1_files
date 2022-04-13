## 데이터 구조 4장 과제 20194546윤경호

###1
```
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
  element *data;
  int capacity;
  int top;
} StackType;

void init_stack(StackType *s)
{
  s->top = -1;
  s->capacity = 1;
  s->data = (element *)malloc(s->capacity * sizeof(element));
}

int is_empty(StackType *s)
{
  return (s->top == -1);
}

int is_full(StackType *s)
{
  return (s->top == (s->capacity -1));
}

void push(StackType *s, element item)
{
  if (is_full(s)){
    s->capacity *= 2;
    s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
  }
  s->data[++(s->top)] = item;
}

element pop(StackType *s)
{
  if(is_empty(s)){
    fprintf(stderr, "스택 공백 에러\n");
    exit(1);
  }
  else return s->data[(s->top)--];
}

int main(void)
{
  StackType *s;
  init_stack(&s);
  /*
  push(&s, 1);
  push(&s, 2);
  push(&s, 3);
  printf("%d \n", pop(&s));
  printf("%d \n", pop(&s));
  printf("%d \n", pop(&s));
  free(s.data);
  */
  push(&s, 1);
  push(&s, 2);
  push(&s, 3);
  printf("%d \n", pop(&s));
  printf("%d \n", pop(&s));
  printf("%d \n", pop(&s));
  free(s.data);
  return 0;
}
```



### 
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100


typedef int element;
typedef struct {
    element* data;
    int capacity;
    int top;
} StackType;

void init_stack(StackType* s)
{
    s->top = -1;
    s->capacity = 1;
    s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_empty(StackType* s)
{
    return (s->top == -1);
}

int is_full(StackType* s)
{
    return (s->top == (s->capacity - 1));
}

void push(StackType* s, element item)
{
    if (is_full(s)) {
        s->capacity *= 2;
        s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

int check_matching(const char* in)
{
    StackType s;
    char ch, open_ch;
    int i, n = strlen(in);
    init_stack(&s);

    for (i = 0; i < n; i++) {
        ch = in[i];
        switch (ch) {
        case '(': case '[': case'{':
            push(&s, ch);
            break;
        case ')': case']': case'}':
            if (is_empty(&s)) return 0;
            else {
                open_ch = pop(&s);
                if ((open_ch == '(' && ch != ')') ||
                    (open_ch == '{' && ch != '}') ||
                    (open_ch == '[' && ch != ']')) {
                    return 0;
                }
                break;
            }
        }

    }
    if (!is_empty(&s)) return 0;
    return 1;
}

int main(void) {
    const char* p = "{(a+b)*k[2+3*n]}}";

    if (check_matching(p) == 1)
        printf("괄호검사성공\n", p);
    else
        printf("괄호검사실패\n", p);
    return 0;
}
```
코드실행결과
![4-2 사진](https://user-images.githubusercontent.com/94778099/163178449-786a7a16-9bd9-4596-af46-c494427f4401.PNG)

코드 실행 순서(사진)
![데이터 구조 4-2](https://user-images.githubusercontent.com/94778099/163178600-25b1ff73-a89a-42cd-b170-3d6d33a089c6.png)


### 3번
```
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s)
{
    s->top = -1;
}

int is_empty(StackType* s)
{
    return (s->top == -1);
}

int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[s->top];
}

int prec(char op) {
    switch (op) {
    case'(': case')': return 0;
    case'+': case'-': return 1;
    case'*': case'/': return 2;
    }
    return -1;
}

void infix_to_postfix(char exp[]) {
    int i = 0;
    char ch, top_op;
    int len = strlen(exp);
    StackType s;

    init_stack(&s);
    for (i = 0; i < len; i++) {
        ch = exp[i];
        switch (ch) {
        case '+': case '-': case '*': case '/':
            while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
                printf("%c", pop(&s));
            push(&s, ch);
            break;
        case '(':
            push(&s, ch);
            break;
        case ')':
            top_op = pop(&s);
            while (top_op != '(') {
                printf("%c", top_op);
                top_op = pop(&s);
            }
            break;
        default:
            printf("%c", ch);
            break;
        }
    }
    while (!is_empty(&s))
        printf("%c", pop(&s));
}

int main(void)
{
    char* s = "5*(10+2)%2";
    printf("중위표시수식 %s \n", s);
    printf("후위표시수식 ");
    infix_to_postfix(s);
    printf("\n");
    return 0;
}
```

코드 실행 결과
![image](https://user-images.githubusercontent.com/94778099/163178332-846f1ce6-d669-4eaf-9bbe-83fd3ca31702.png)
