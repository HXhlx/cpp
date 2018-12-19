#ifndef SALARY_H
#define SALARY_H
#include "Staff.h"
class Salary :public Staff
{
protected:
	double basic, duty, bonus, salarysum;
public:
	Salary(unsigned w = 0, string i = "", string n = "", double ba = 0, double d = 0, double bo = 0) :Staff(w, i, n), basic(ba), duty(d), bonus(bo) 
	{
		salarysum = basic + duty + bonus;
	}
	void Input();
	void Print();
	void Modify();
};
#endif
