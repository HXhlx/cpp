#ifndef CHARGE_H
#include"Salary.h"
#define CHARGE_H
class Charge :public Salary
{
	int water, electricity, medicare;
public:
	Charge();
	~Charge();
};
#endif
