#ifndef SALARY_H
#define SALARY_H
#include "Staff.h"
class Salary :public Staff
{
	int basic, duty, bonus;
public:
	Salary();
	~Salary();
};
#endif
