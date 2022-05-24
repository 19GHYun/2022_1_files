## 데이터 구조 8,9장 과제. 조선대학교 컴퓨터공학과 20194546 윤경호
	
### 257p 3번											

다음 트리에서 루트 노드는 50 이고 40의 부모 노드는 33 이며 40의 형제 노드는 14, 56, 82 이다. 노드 33의 차수는 2이며 트리의 높이는 4이다.

![image](https://user-images.githubusercontent.com/94778099/170107978-ec7e4bb7-2c42-48ab-a0aa-e66b21412dc5.png)




###  p270에 나와있는 트리에 전위,중위,후위 순회 방식에 따른 방문순서를 표기하시오 (전위, 중위, 후위 순위에 따른 방문순서 중요!)


![1123](https://user-images.githubusercontent.com/94778099/170108408-adc7a42b-a4f9-48e3-aa41-d4c0d6a4e8df.jpg)

#### 전위순회

A -> B -> D -> H -> I -> E -> C -> F -> G -> J -> K


#### 중위순회

H -> D -> I -> B -> E -> A -> F -> C -> J -> G -> K

#### 후위순회

H -> I -> D -> E -> B -> F -> J -> K -> G -> C -> A


### 3.트리에 데이터를 삽입하고 전위,중위,후위 순회 방식으로 데이터를 출력해보시오

```
코드문

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode n1 = {1 ,NULL ,NULL };
TreeNode n2 = {4 ,&n1 ,NULL };
TreeNode n3 = {16 ,NULL ,NULL };
TreeNode n4 = {25 ,NULL ,NULL };
TreeNode n5 = {20 ,&n3 ,&n4 };
TreeNode n6 = {15 ,&n2 ,&n5 };
TreeNode* root = &n6;

void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%d]", root->data);
		inorder(root->right);
	}
}

void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[%d]", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d]", root->data);
	}
}


int main(void) {
	printf("중위 순회=");
	inorder(root);
	printf("\n");

	printf("전위 순회=");
	preorder(root);
	printf("\n");

	printf("후위 순회=");
	postorder(root);
	printf("\n");
}

```

실행결과

![image](https://user-images.githubusercontent.com/94778099/170110842-861e378f-c4f0-4cd9-af32-d8111c78db1e.png)

### 1. p341을 참고하여 히프정렬을 구현해보시오.

```
코드문

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {
	int key;
}element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void heap_sort(element a[], int n) {
	int i;
	HeapType* h;

	h = create();
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);
	}
	free(h);
}

#define SIZE 8
int main(void) {
	element list[SIZE] = { 23, 56, 11, 9, 56, 99, 27, 34 };
	heap_sort(list, SIZE);
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", list[i].key);
	}
	printf("\n");
	return 0;
}

```


실행결과

![image](https://user-images.githubusercontent.com/94778099/170113187-65502c4f-2223-48b4-a845-34f5c8d1b1b7.png)
