#ifndef SALARY_H
#define SALARY_H
#include "Staff.h"
class Salary :public Staff
{
protected:
	double basic, duty, bonus, salarysum;
public:
	Salary(unsigned w = 0, string i = "", string n = "", double ba = 0, double d = 0, double bo = 0) :Staff(w, i, n), basic(ba), duty(d), bonus(bo) { salarysum = basic + duty + bonus; }
	static void Find(vector<Salary>);		/*按工资信息查询*/
	void Input();							/*添加员工工资信息*/
	void Modify();							/*修改员工工资信息*/
	void Print();							/*工资信息查询*/
};
#endif
