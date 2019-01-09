#include<algorithm>
#include<iostream>
#include<vector>
#include "Salary.h"
using namespace std;
void Salary::Find(vector<Salary>staff)
{
	size_t t;
	Salary salary;
	for (vector<Salary>::iterator r = staff.begin(); r != staff.end(); r++)(*r).salarysum = (*r).basic + (*r).duty + (*r).bonus;
	cout << endl;
	cout << "请选择查询项目" << endl;
	cout << "1.基本工资" << endl;
	cout << "2.职务工资" << endl;
	cout << "3.奖金补贴" << endl;
	cout << "4.应发工资" << endl;
	cin >> t;
	switch (t)
	{
	case 1:
		cout << "请输入基本工资:";
		cin >> salary.basic;
		for (vector<Salary>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).basic == salary.basic)(*r).Print();
		break;
	case 2:
		cout << "请输入职务工资:";
		cin >> salary.duty;
		for (vector<Salary>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).duty == salary.duty)(*r).Print();
		break;
	case 3:
		cout << "请输入奖金补贴:";
		cin >> salary.bonus;
		for (vector<Salary>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).bonus == salary.bonus)(*r).Print();
		break;
	case 4:
		cout << "请输入应发工资:";
		cin >> salary.salarysum;
		for (vector<Salary>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).salarysum == salary.salarysum)(*r).Print();
		break;
	}
}
void Salary::Input()
{
	if (!basic && !duty && !bonus)
	{
		Staff::Print();
		cout << "请输入基本工资、职务工资、奖金补贴:";
		cin >> basic >> duty >> bonus;
	}
	cout << endl;
}
void Salary::Print()
{
	Staff::Print();
	salarysum = basic + duty + bonus;
	cout << "基本工资:" << basic << ends << "职务工资:" << duty << ends << "奖金补贴:" << bonus << ends << "应发工资:" << salarysum << endl;
}
void Salary::Modify()
{
	cout << "请输入新的员工工资信息：基本工资，职务工资，特别奖励" << endl;
	cin >> basic >> duty >> bonus;
	cout << "成功修改员工工资信息" << endl;
}
