/*
class Color {
	int red, green, blue;
public:
	Color() { red = green = blue = 0; }
	Color(int r, int g, int b) { red = r; green = g; blue = b; }
	void setColor(int r, int g, int b) { red = r; green = g; blue = b; }
	void show() { cout << red << ' ' << green << ' ' << blue << endl; }
};


int main() {
	Color screenColor(255, 0, 0);
	Color* p;

	p = &screenColor;
	p->show();
	Color colors[3];
	
	p = colors;

	p[0].setColor(255, 0, 0);
	p[1].setColor(0, 255, 0);
	p[2].setColor(0, 0, 255);

	for (int i = 0; i < 3; i++) {
		p[i].show();
	}
	

}

*/

/*
#include <iostream>
using namespace std;


int main() {
	
	int *a = new int[5];

	cout << "정수 5개 입력>>";
	cin >> a[0] >> a[1] >>  a[2] >>  a[3] >> a[4];

	cout << "평균 " << (float)(a[0] + a[1] + a[2] + a[3] + a[4]) / 5 << endl;

	delete[] a;

}



*/

/*

int main() {
	
	string a;
	int index = 0;
	int count = 0;
	cout << "문자열 입력>>";
	cin >> a;

	for (int i = 0; i<a.length(); i++) {
		if (index = a.find("a", index))
			count++;
	}

	cout << "문자 a는 " << count << "개 있습니다.";
}
*/




/*
class Sample {
	int* p;
	int size;
public:
	Sample(int n) {
		size = n; p = new int[n];
	}
	void read();
	void write();
	int big();
	~Sample();
};

void Sample::read() {

	int a[10];
	cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6] >> a[7] >> a[8] >> a[9];

	for (int i = 0; i < 10; i++) {
		p[i] = a[i];
	}

}
void Sample::write() {
	for (int i = 0; i < 10; i++) {
		cout << p[i] << " ";
	}
	cout << endl;
}
int Sample::big() {
	int big1 = 0;

	for (int i = 0; i < 10; i++) {
		if (big1 < p[i]) {
			big1 = p[i];
		}
	}
	return big1;
}
Sample :: ~Sample() {
	delete[] p;
}
int main() {
	Sample s(10);
	s.read();
	s.write();
	cout << "가장 큰 수는 " << s.big() << endl;

}


*/

/*
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


int main() {

	string a;
	
	cout << "아래에 한 줄을 입력하세요.(exit를 입력하면 종료합니다)" << endl;

	while (1) {
		

		getline(cin, a);

		if (a == "exit") {
			break;
		}

		int length = a.length();

		srand((unsigned)time(0));
		int n = rand();

		int random = rand() % length;

		while (1) {
			if (a[random] == ' ') {
				random++;
			}
			else
				break;
		}


		a[random] = n % 26 + 97;

		cout << a << endl;

	}

}
*/


/*
#include <iostream>
#include <string>


using namespace std;


int main() {

	string a;
	cout << "아래에 한 줄을 입력하세요.(exit를 입력하면 종료합니다)" << endl;

	while (1) {

		getline(cin, a);

		if (a == "exit") {
			break;
		}

		int length = a.length();

		for (int i = length - 1; i > -1; i--) {
			cout << a[i];
		}
		cout << endl;

	}
}
*/

/*
#include <iostream>
#include <string>
using namespace std;

class Circle {
	int radius;
public:
	void setRadius(int radius);
	double getArea();
};
void Circle::setRadius(int radius) {
	this->radius = radius;
}


double Circle::getArea() {
	return this->radius* this->radius * 3.14;
}


int main() {
	Circle a[3];
	int b = 0;
	int count = 0;

	for (int i = 0; i < 3; i++) {
		cout << "원 " << i + 1 << "의 반지름 >> ";
		cin >> b;
		a[i].setRadius(b);

	}

	for (int i = 0; i < 3; i++) {
		if (a[i].getArea() > 100) {
			count++;
		}
	}

	cout << "면적이 100보다 큰 원은 " << count << "개 입니다" << endl;
}
*/

/*
#include <iostream>
#include <cstring>
using namespace std;

class Person{
	string name;
	string tel;
public:
	Person();
	string getName() { return name;}
	string getTel() {return tel;}
	void set(string name, string tel);
};
Person::Person(){
	name = "Blank";
	tel = "010-1234-5678";
}


void Person::set(string name, string tel){
	this->name = name;
	this->tel = tel;
}

int main(){
	cout << "이름과 전화 번호를 입력해 주세요" <<endl;

	string a, b;

	Person p[3];

	for(int i = 0; i < 3 ; i++){
	cout << "사람 " << i+1 << ">> ";
	cin >> a >> b;
	p[i].set(a,b);
	}
	cout<<"모든 사람의 이름은 " <<  p[0].getName() << " " << p[1].getName() << " " << p[2].getName() << endl;

	cout << "전화번호 검색합니다. 이름을 입력하세요>>";

	cin >> a;

	for(int i = 0; i <3; i++){
		if(p[i].getName() == a){
			cout << "전화 번호는 " << p[i].getTel();
		}
	}
}
*/
