#include <algorithm>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<string>
#include<vector>
#include "Charge.h"
using namespace std;
int Charge::Login(vector<Charge>&staff)
{
	Charge s;
	s.BasicIn();
	cout << "请输入密码(默认身份证后6位):";
	cin >> s.password;
	for (size_t i = 0; i < staff.size(); i++)if (staff[i] == s && staff[i].password == s.password)return i;
	return EOF;
}
void Charge::In(fstream &is, vector<Charge>&staff)
{
	Charge s;
	while (is >> s.wage >> s.id >> s.name >> s.gender >> s.age >> s.department >> s.occupation >> s.phone >> s.address >> s.basic >> s.duty >> s.bonus >> s.salarysum >> s.water >> s.electricity >> s.medicare >> s.rax >> s.realsalary >> s.password)staff.push_back(s);
}
void Charge::Save(fstream &os, vector<Charge>&staff)
{
	for (vector<Charge>::iterator s = staff.begin(); s != staff.end(); s++)
	{
		(*s).Feagure();
		os << (*s).wage << " " << (*s).id << " " << (*s).name << " " << (*s).gender << " " << (*s).age << " " << (*s).department << " " << (*s).occupation << " " << (*s).phone << " " << (*s).address << " " << " " << (*s).basic << " " << (*s).duty << " " << (*s).bonus << " " << (*s).salarysum << " " << (*s).water << " " << (*s).electricity << " " << (*s).medicare << " " << (*s).rax << " " << (*s).realsalary << " " << (*s).password << endl;
	}
}
void Charge::Feagure()
{
	salarysum = basic + duty + bonus;
	if (salarysum <= 800)rax = 0;
	else if (salarysum > 800 && salarysum <= 1500)rax = (salarysum - 800)*0.05;
	else if (salarysum > 1500)rax = (salarysum - 1500)*0.1;
	realsalary = salarysum - rax - medicare - water - electricity;
}
void Charge::Input()
{
	if (!water && !electricity && !medicare)
	{
		Salary::Print();
		cout << "请输入水费、电费、医疗保险:";
		cin >> water >> electricity >> medicare;
	}
	cout << endl;
}
void Charge::Print()
{
	Salary::Print();
	Feagure();
	cout << "水费:" << water << ends << "电费:" << electricity << ends << "医疗保险" << medicare << ends << "税金:" << rax << ends << "实发工资:" << realsalary << endl;
	cout << endl;
}
void Charge::Modify()
{
	cout << "请输入新的员工费用信息(水费，电费，保险费):" << endl;
	cin >> water >> electricity >> medicare;
	cout << "成功修改员工费用信息" << endl;
}
void Charge::Delete(vector<Charge>&staff)
{
	Charge r;
	r.BasicIn();
	char c;
	vector<Charge>::iterator s = find(staff.begin(), staff.end(), r);
	if (s == staff.end())cerr << "删除失败" << endl;
	else if (*s == r)
	{
		cout << "你是否要删除该员工信息?y/n" << endl;
		cin >> c;
		if (c == 'y')
		{
			staff.erase(s);
			cout << "删除成功" << endl;
		}
	}
}
void Charge::Find(vector<Charge>staff)
{
	size_t t;
	Charge charge;
	for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)(*r).Feagure();
	cout << endl;
	cout << "请选择查询项目" << endl;
	cout << "1.水费" << endl;
	cout << "2.电费" << endl;
	cout << "3.医疗保险" << endl;
	cout << "4.税金" << endl;
	cout << "5.实发工资" << endl;
	cin >> t;
	switch (t)
	{
	case 1:
		cout << "请输入水费:";
		cin >> charge.water;
		for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).water == charge.water)(*r).Print();
		break;
	case 2:
		cout << "请输入电费:";
		cin >> charge.electricity;
		for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).electricity == charge.electricity)(*r).Print();
		break;
	case 3:
		cout << "请输入医疗保险:";
		cin >> charge.medicare;
		for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).medicare == charge.medicare)(*r).Print();
		break;
	case 4:
		cout << "请输入税金:";
		cin >> charge.rax;
		for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).rax == charge.rax)(*r).Print();
		break;
	case 5:
		cout << "请输入实发工资:";
		cin >> charge.realsalary;
		for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).realsalary == charge.realsalary)(*r).Print();
		break;
	}
}
void Charge::Statistics(vector<Charge>staff)
{
	double watersum = 0, electricitysum = 0, medicaresum = 0, raxsum = 0, realsalarysum = 0, salarysumsum = 0, basicsum = 0, bonussum = 0, dutysum = 0;
	for (vector<Charge>::iterator s = staff.begin(); s != staff.end(); s++)
	{
		(*s).Feagure();
		basicsum += (*s).basic;
		dutysum += (*s).duty;
		bonussum += (*s).bonus;
		salarysumsum += (*s).salarysum;
		watersum += (*s).water;
		electricitysum += (*s).electricity;
		medicaresum += (*s).medicare;
		raxsum += (*s).rax;
		realsalarysum += (*s).realsalary;
	}
	cout << "总基本工资:" << basicsum << ends << "总职务工资:" << dutysum << ends << "总应发工资:" << salarysumsum << endl << "总水费:" << watersum << ends << "总电费:" << electricitysum << ends << "总医疗保险:" << medicaresum << ends << "总税金:" << raxsum << ends << "总实际工资:" << realsalarysum << endl;
}
