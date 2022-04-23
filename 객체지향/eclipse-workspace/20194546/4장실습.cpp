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
