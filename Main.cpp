#include<iostream>
#include<list>
#include"Staff.h"
#include"Salary.h"
#include"Charge.h"
using namespace std;
int main()
{
	char t = 1;
	list<Charge>staff;
	Charge s;
first:
	cout << endl;
	cout << "请输入员工信息(身份证号、姓名、性别、年龄、部门、职称、手机号码、住址):" << endl;
	s.Staff::Input();
	staff.push_back(s);
	cout << "是否输入完毕?(y or n)";
	cin >> t;
	if (t == 'n')goto first;
	for (auto a : staff)
	{
		a.Staff::Print();
		cout << endl;
	}



	cout << "请选择操作:" << endl;
	cout << "1.添加职工基本信息	2.职工基本信息修改" << endl;
	cout << "3.职工基本信息删除	4.职工工资数据录入" << endl;
	cout << "5.职工工资信息计算	6.职工工资数据查询" << endl;



	cout << "请输入员工工资信息(基本工资、职务工资、奖金补助):" << endl;
	for (auto&a : staff)
	{
		cout << endl;
		a.Staff::Print();
		cout << endl;
		a.Input();
	}
	for (auto a : staff)a.Print();
	return 0;
}
