#ifndef STAFF_H
#define STAFF_H
#include<string>
class Staff
{
	std::string id, name, gender, department, occupation, phone, adress;
	unsigned wage, age;
public:
	void Input();
	void Print();
};
#endif
