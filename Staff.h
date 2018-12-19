#ifndef STAFF_H
#define STAFF_H
#include<string>
#include<vector>
using std::string;
class Staff
{
	friend class Administrator;
	friend bool operator==(Staff, Staff);
protected:
	string id, name, gender, department, occupation, phone, address, password;
	unsigned wage, age;
public:
	Staff(unsigned w = 0, string i = "", string n = "") :wage(w), id(i), name(n) {}
	void Input(Staff);
	void Print();
	void Change();
	void Modify();
};
#endif
