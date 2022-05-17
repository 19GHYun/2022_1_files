

덱 구현.
```

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

void error(char* message) {
	fprintf(stderr, "%s/\n", message);
	exit(1);
}

void initDeque(DequeType* q) {
	q->front = q->rear = 0;
}

int isEmpty(DequeType* q) {
	return (q->front == q->rear);
}

int isFull(DequeType* q) {
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void dequePrint(DequeType* q) {
	printf("DEQUE(front=%d rear=%d)", q->front, q->rear);
	if (!isEmpty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void addRear(DequeType* q, element item) {
	if (isFull(q)) {
		error("큐가 포화상태입니다.");
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element deleteRear(DequeType* q) {
	int prev = q->rear;
	if (isEmpty(q)) {
		error("큐가 공백상태입니다.");
	}
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element getRear(DequeType* q) {
	if (isEmpty(q))
		error("큐가 공백상태입니다.");
	return q->data[q->rear];
}
void addFront(DequeType* q, element item) {
	if (isFull(q)) {
		error("큐가 포화상태입니다.");
	}
	q->data[q->front] = item;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element deleteFront(DequeType* q) {
	int prev = q->rear;
	if (isEmpty(q)) {
		error("큐가 공백상태입니다.");
	}
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element getFront(DequeType* q) {
	if (isEmpty(q)) {
		error("큐가 공백상태입니다.");
	}
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void) {
	DequeType queue;
	initDeque(&queue);
	for (int i = 0; i < 3; i++) {
		addFront(&queue, i);
		dequePrint(&queue);
	}
	for (int i = 0; i < 3; i++) {
		deleteRear(&queue);
		dequePrint(&queue);
	}
	return 0;
}

```


실행결과.

![image](https://user-images.githubusercontent.com/94778099/168834457-76356248-9e53-4e27-ac4f-7198abaad590.png)


-------------------


은행 서비스 시뮬레이션 프로그램

```

# include <stdio.h>
# include <stdlib.h>


typedef struct { 
	int id;
	int arrival_time;
	int service_time;
} element;		

#define MAX_QUEUE_SIZE 5

typedef struct { 
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void)
{
	int minutes = 60;
	int total_wait = 0;
	int total_customers = 0;
	int service_time = 0;
	int service_customer;
	QueueType queue;
	QueueType log;
	init_queue(&queue);
	init_queue(&log);

	srand(time(NULL));
	for (int clock = 0; clock < minutes; clock++) {
		printf("현재시각=%d\n", clock);
		if ((rand() % 10) < 3) {
			element customer;
			customer.id = total_customers++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer);
			printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n",
				customer.id, customer.arrival_time, customer.service_time);
		}
		if (service_time > 0) {
			printf("고객 %d 업무처리중입니다. \n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",
					customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;
			}
		}
	}
	printf("전체 대기 시간=%d분 \n", total_wait);

	return 0;
}

```

실행결과

![image](https://user-images.githubusercontent.com/94778099/168836616-37ecb7f0-0d7c-43f4-98e6-85de0ef1fe95.png)

-------------

단순연결리스트 구현.

```
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, int value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}	

int main(void) {
	ListNode* head = NULL;

	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i);
		print_list(head);
	}
	for (int i = 0; i < 5; i++) {
		head = delete_first(head);
		print_list(head);
	}
	return 0;
}

```

실행결과

![image](https://user-images.githubusercontent.com/94778099/168839374-1836f547-8489-4b54-99d0-71e343ae266f.png)


--------------

이중연결리스트

```

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

void print_dlist(DListNode* phead) {
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

void ddelete(DListNode* head, DListNode* removed) {
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("추가 단계\n");
	for (int i = 0; i < 5; i++) {
		dinsert(head, i);
		print_dlist(head);
	}
	printf("\n삭제 단계\n");
	for (int i = 0; i < 5; i++) {
		print_dlist(head);
		ddelete(head, head->rlink);
	}
	free(head);
	return 0;
	
}


```
실행결과

![image](https://user-images.githubusercontent.com/94778099/168841769-898c8116-e4f9-405a-8ba4-e21b1587aabf.png)

