#include<algorithm>
#include<iostream>
#include<vector>
#include "Salary.h"
using namespace std;
void Salary::Input()
{
	if (!basic&&!duty&&!bonus)
	{
		Staff::Print();
		cin >> basic >> duty >> bonus;
	}
}
void Salary::Print()
{
	salarysum = basic + duty + bonus;
	cout<<"工资卡号:"<<wage<<ends<<"姓名:"<<name<<ends<<"应发工资:"<<salarysum<<endl;
}
void Salary::Modify()
{
	cout << "请输入新的员工工资信息：基本工资，职务工资，特别奖励" << endl;
	cin >> basic >> duty >> bonus;
	cout << "成功修改员工工资信息" << endl;
}
