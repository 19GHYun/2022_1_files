/*
 * Add.h
 *
 *  Created on: 2022. 3. 21.
 *      Author: chosun
 */
#include <iostream>
using namespace std;

#ifndef ADD_H_
#define ADD_H_

class Add {
private:
	int a, b;

public:
	Add();
	void SetValue(int x, int y);
	virtual ~Add();
	int calculate();
};

#endif /* ADD_H_ */
