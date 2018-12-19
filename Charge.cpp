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
void Charge::BasicIn()
{
	string a;
	cout << "请输入工资卡号/姓名/身份证号:";
	cin >> a;
	wage = stoi(a);
	id = a;
	name = a;
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
		(*s).feagure();
		os << (*s).wage << " " << (*s).id << " " << (*s).name << " " << (*s).gender << " " << (*s).age << " " << (*s).department << " " << (*s).occupation << " " << (*s).phone << " " << (*s).address << " " << " " << (*s).basic << " " << (*s).duty << " " << (*s).bonus << " " << (*s).salarysum << " " << (*s).water << " " << (*s).electricity << " " << (*s).medicare << " " << (*s).rax << " " << (*s).realsalary << " " << (*s).password << endl;
	}
}
void Charge::feagure()
{
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
		cin >> water >> electricity >> medicare;
	}
}
void Charge::Print()
{
	feagure();
	cout << "应发工资:" << salarysum << ends << "水费:" << water << ends << "电费:" << electricity << ends << "医疗保险:" << medicare << ends << "税金:" << rax << ends << "实发工资:" << realsalary << ends << "特别奖励:" << bonus << endl;
}
void Charge::Modify()
{
	Charge t;
	t.BasicIn();
	cout << "请输入新的员工费用信息：水费，电费，保险费" << endl;
	cin >> water >> electricity >> medicare;
	cout << "成功修改员工费用信息" << endl;
}
void Charge::Delete(vector<Charge>&staff)
{
	Charge r;
	r.BasicIn();
	char c;
	vector<Charge>::iterator s = find(staff.begin(), staff.end(), r);
	if (*s == r)
	{
		cout << "你是否要删除该员工信息?y/n" << endl;
		cin >> c;
		if (c == 'y')staff.erase(s);
	}
}
