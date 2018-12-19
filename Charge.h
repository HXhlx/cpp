#ifndef CHARGE_H
#define CHARGE_H
#include"Salary.h"
using namespace std;
class Charge :public Salary
{
	double water, electricity, medicare, rax, realsalary;
public:
	Charge(unsigned w = 0, string i = "", string n = "", double ba = 0, double d = 0, double bo = 0, double wa = 0, double e = 0, double m = 0) :Salary(w, i, n, ba, d, bo), water(wa), electricity(e), medicare(m) {}
	void BasicIn();
	static int Login(vector<Charge>&);
	static void In(fstream&, vector<Charge>&);
	static void Save(fstream&, vector<Charge>&);
	void feagure();
	void Input();
	void Print();
	void Modify();
	void Delete(vector<Charge>&);
};
#endif
