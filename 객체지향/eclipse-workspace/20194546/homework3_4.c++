//============================================================================
// Name        : test1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
using namespace std;
/*
class Name{
    string first, last;
public:
    string get_first() { return first; }
    string get_last()  { return last; }
    void set_name(string f, string l);  // 멤버 first와 last에 각각 f와 l을 저장
};

class PersonManager{
    Name *p;
    int nofp; //Name의 수, p의 크기
public:
    PersonManager(int n);    // 생성자에서 n개의 원소를 가지는 Name 배열을 동적 메모리 할당 받은 후 p에 저장 후
                             // n개의 Name(first last)을 입력 받아 p 배열의 각 원소에 저장
    void show();             // 모든 n개의 이름의 first name과 last name을 출력
    int serarch(string str); // str과 같은 first 또는 last 이름의 수를 반환
    ~PersonManager();        // 메모리 반환 및 "delete [] p;" 출력
};
// 위에 코드는 수정 불가
void Name::set_name(string f, string l){
	this->first = f;
	this->last = l;
}

PersonManager::PersonManager(int n){
	cout << "Enter" << n << "first and last names."<< endl;
	p = new Name[n];
	string a, b;
	nofp = n;
	for(int i = 0; i < n; i++){
		cin >> a >> b;
		p[i].set_name(a,b);
	}
}

void PersonManager::show(){
	for(int i = 0; i <nofp; i++){
		cout<< p[i].get_first() << " "<< p[i].get_last() << endl;
	}
}

int PersonManager::serarch(string str){
	int check = 0;
	for(int i = 0; i < nofp; i++){
		if(str == p[i].get_first())
			check++;
		if(str == p[i].get_last())
			check++;
	}
	return check;
}

PersonManager::~PersonManager(){
	delete [] p;
	cout << "delete [] p;" << endl;
}

// 아래 main 함수는 수정 불가
int main() {
    int n;
    cout << "Enter number of people." << endl;
    cin >> n;

    PersonManager people(n);

    people.show();

    cout << "Enter search name." << endl;
    string str;
    cin >> str;
    cout << people.serarch(str) << endl;

    return 0;
}
*/



class MyStack {
private:
	string *element; // 스택의 메모리로 사용할 포인터
	int size;           // 스택의 최대 크기
	int tos;            // 스택의 top을 가리키는 인덱스
public:
	MyStack(int size);    // 생성자 스택의 최대 크기를 입력 받아서 element 객체 배열을 생성해줌.
	MyStack(MyStack& s);  // 깊은 복사 생성자
	~MyStack();           // 소멸자

	bool push(string item); // item을 스택에 삽입
			// 스택이 가득 차 있으면 false를, 아니면 true 리턴
	bool pop(string &item); // 스택의 탑에 있는 값을 item에 반환  그리고 top에 있는 자료 삭제
	bool peek(string &item); // 스택의 탑에 있는 값을 item에 반환
	void print_stack();  // 스택 내용 출력

};

// 위에 코드는 수정 불가
MyStack::MyStack(int size){
	this->size = size;
	element = new string[size];
}

MyStack::MyStack(MyStack& s){
	this->size = s.size;
	this->tos = s.tos;
	this->element = new string;
	strcpy(this->element, s.element);
}
//여기에 코드 작성
//아래 main 함수 실행시 출력과 입력 예시
/*
(출력)Enter stack size : (입력)5
(출력)Enter number of input string : (입력)7
(출력)Enter string : (입력)kim
(출력)Enter string : (입력)yang
(출력)Enter string : (입력)park
(출력)Enter string : (입력)shin
(출력)Enter string : (입력)chung
(출력)Enter string : (입력)jung
(출력)stack is full
(출력)Enter string : (입력)lee
(출력)stack is full
(출력)first stack : kim yang park shin chung 
(출력)second stack : kim yang park shin chung 
(출력)first stack : kim yang park shin 
(출력)second stack : kim yang park shin chung 
*/
int main() {

	int stack_size;

	// 스택이 저장할수 있는 최대 크기를 입력 받는다
	cout << "Enter stack size : ";
	cin >> stack_size;

	// 스택을 생성해 줌
	MyStack first_stack(stack_size);

	// 입력할 데이터의 수를 입력 받는다
	// 데이터를 숫자 만큼 입력 받고 stack에 푸시한다.
	int  input_size;
	string  item;
	cout << "Enter number of input string : " ;
	cin >> input_size;

	for (int i=0; i < input_size ;  i++ ) {
		cout << " Enter string : " ;
		cin >> item;
		first_stack.push(item);
	}

	// 스택의 자료를 출력
	cout << "first stack : " ;
	first_stack.print_stack();

	// 스택을 생성해 줌
	MyStack second_stack(first_stack);

	// 스택의 자료를 출력

	cout << "second stack : " ;
	second_stack.print_stack();

	first_stack.pop(item);
	second_stack.peek(item);

	// 스택의 자료를 출력
	cout << "first stack : " ;
	first_stack.print_stack();

	cout << "second stack : " ;
	second_stack.print_stack();

	return 0;
}






#include <iostream>
#include <string>
using namespace std;

class ArrayUtility2 {
public:
	static int* concat(int s1[], int s2[], int size_s1, int size_s2); // s1과 s2를 연결한 새로운 배열을 동적 생성하고 포인터 리턴
	                                                                  // size_s1, size_s2는 각각 배열 s1과 s2의 크기
	static int* remove(int s1[], int s2[], int size_s1, int size_s2, int&retSize); // s1에서 s2에 있는 숫자를 모두 삭제한 새로운 배열을 동적 생성하여 리턴
	                                                                               // return하는 배열의 크기는  retSize에 전달
};

// 위에 코드는 수정 불가

int* ArrayUtility2::concat(int s1[], int s2[], int size_s1, int size_s2){
	int total = size_s1 + size_s2;
	int *array1 = new int [total];
	int check = 0;

	for(int i = 0; i<size_s1; i++){
		array1[i] = s1[i];
	}
	for(int i = size_s1; i < total; i++){
		array1[i] = s2[check];
		check++;
	}
	return array1;
}

int* ArrayUtility2::remove(int s1[], int s2[], int size_s1, int size_s2, int&retSize){
	int check = 0;

	int *array2 = new int [size_s1];

	for(int i = 0; i<size_s1; i++){
			array2[i] = s1[i];
		}

	for(int i = 0; i <size_s1; i++){
		for(int j = 0; j < size_s2; j++){
			if(array2[i] == s2[j]){
				array2[i] == NULL;
				check++;
			}
		}
	}
	for(int i = 0; i < size_s1; i++){
		if(array2[i] == NULL){
			array2[i+1] = array2[i];
		}
	}
	return array2;
}
//여기에 코드 작성
//
/* 입력과 출력 예제
(출력)Enter number of integer : (입력)5
(출력)Enter 5 integer(s) : (입력)1 2 4 5 6
(출력)Enter number of integer : (입력)7
(출력)Enter 7 integer(s) : (입력)2 4 6 7 9 0 10
(출력)1 2 4 5 6 2 4 6 7 9 0 10
(출력)1 5


*/
int main() {
	int size1;
	int size2;

    int *x, *y;

    cout << "Enter number of integer : ";
    cin >> size1;
    x = new int [size1];

    cout << "Enter " << size1 << " integer(s) : ";
    for(int i=0; i < size1 ; i++)
    	cin >> x[i];

    cout << "Enter number of integer : ";
    cin >> size2;

    if (size1 == size2) {
    	cout << "Input Error";
    	delete [] x;
		return -1;
    }

    y = new int [size2];
    cout << "Enter " << size2 << " integer(s) : ";
    for(int i=0; i < size2 ; i++)
    	cin >> y[i];

    int* p = ArrayUtility2::concat(x, y, size1, size2);

   // 합친 정수 배열을 출력한다
    for(int i=0; i< size1 + size2 ;  i++) cout << p[i] << ' ';
    cout << endl;

    int retSize;
    int* q = ArrayUtility2::remove(x, y, size1, size2, retSize);

     //배열 x[]에서 y[]를 뺀 결과를 출력한다;
    for(int i=0; i< retSize ; i++) cout << q[i] << ' ';
    cout << endl;

    delete [] p;
    delete [] q;
    delete [] x;
    delete [] y;

}
