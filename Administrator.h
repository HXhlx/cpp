#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include<list>
#include<string>
#include"Staff.h"
using namespace std;
class Administrator
{
	friend bool operator==(Administrator A, Administrator B);
	string name, password;
public:
	Administrator(string n = "", string p = "") :name(n), password(p) {}
	static void In(fstream&, list<Administrator>&);
	void Input(list<Administrator>&);
	static Administrator Login(list<Administrator>);
	friend bool operator==(Administrator A, Administrator B);
	void Change(list<Administrator>&);
	bool Delete(list<Administrator>&);
	static void Save(fstream&, list<Administrator>&);
	void ModifyStaff(Staff&);
};
#endif
