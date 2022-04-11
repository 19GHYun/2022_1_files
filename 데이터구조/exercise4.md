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
