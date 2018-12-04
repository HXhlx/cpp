#ifndef SALARY_H
#define SALARY_H
#include "Staff.h"
class Salary :public Staff
{
	int basic, duty, bonus;
public:
	void Input();
	void Print();
};
#endif
