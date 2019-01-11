#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<vector>
#include"Staff.h"
using namespace std;
void Staff::Find(vector<Staff>staff)
{
	size_t t;
	Staff sta;
	cout << endl;
	cout << "请选择查询项目" << endl;
	cout << "1.工资卡号" << endl;
	cout << "2.身份证号" << endl;
	cout << "3.姓名" << endl;
	cout << "4.性别" << endl;
	cout << "5.年龄" << endl;
	cout << "6.手机号码" << endl;
	cout << "7.部门" << endl;
	cout << "8.职务" << endl;
	cout << "9.住址" << endl;
	cin >> t;
	switch (t)
	{
	case 1:
		cout << "请输入工资卡号:";
		cin >> sta.wage;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).wage == sta.wage)(*r).Print();
		break;
	case 2:
		cout << "请输入身份证号:";
		cin >> sta.id;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).id == sta.id)(*r).Print();
		break;
	case 3:
		cout << "请输入姓名:";
		cin >> sta.name;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).name == sta.name)(*r).Print();
		break;
	case 4:
		cout << "请输入性别:";
		cin >> sta.gender;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).gender == sta.gender)(*r).Print();
		break;
	case 5:
		cout << "请输入年龄:";
		cin >> sta.age;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).age == sta.age)(*r).Print();
		break;
	case 6:
		cout << "请输入手机号码:";
		cin >> sta.phone;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).phone == sta.phone)(*r).Print();
		break;
	case 7:
		cout << "请输入部门:";
		cin >> sta.department;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).department == sta.department)(*r).Print();
		break;
	case 8:
		cout << "请输入职务:";
		cin >> sta.occupation;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).occupation == sta.occupation)(*r).Print();
		break;
	case 9:
		cout << "请输入住址:";
		cin >> sta.address;
		for (vector<Staff>::iterator r = staff.begin(); r != staff.end(); r++)if ((*r).address == sta.address)(*r).Print();
		break;
	}
}
void Staff::BasicIn()
{
	string a;
	cout << "请输入工资卡号/姓名/身份证号:";
	cin >> a;
	wage = stoi(a);
	id = a;
	name = a;
}
void Staff::Input(Staff s)
{
	static int n;
	if (s.wage)n = s.wage;
	else n = 10000;
	cout << "请输入员工信息(身份证号、姓名、性别、年龄、部门、职称、手机号码、住址):" << endl;
K:
	cin >> id >> name >> gender >> age >> department >> occupation >> phone >> address;
	if (id.size() != 18)
	{
		cerr << "身份证号码格式错误,请重新输入:" << endl;
		goto K;
	}
	password = id;
	password.erase(0, 12);
	wage = ++n;
}
void Staff::Print()
{
	cout << "工资卡号" << wage << ends << "身份证号:" << id << ends << "姓名:" << name << ends << "性别:" << gender << ends << "年龄:" << age << ends << "部门:" << department << ends << "职称:" << occupation << ends << "手机号码:" << phone << ends << "住址:" << address << endl;
}
bool operator==(Staff A, Staff B)
{
	return A.wage == B.wage || A.name == B.name || A.id == B.id;
}
void Staff::Change()
{
	string k, p;
	cout << "请输入原有密码:";
ninth:
	cin >> k;
	if (k != password)
	{
		cerr << "密码输入错误,请重新输入";
		goto ninth;
	}
tenth:
	cout << "请输入新密码:";
	cin >> k;
	cout << "请确认新密码:";
	cin >> p;
	if (k == p)
	{
		cout << "密码修改成功" << endl;
		password = p;
	}
	else
	{
		cerr << "密码输入错误,请重新输入:" << endl;
		goto tenth;
	}
}
void Staff::Modify()
{
	int t;
	cout << "请输入你需要修改的信息（1.电话,2.住址）" << endl;
	cin >> t;
	switch (t)
	{
	case 1:cout << "请输入新的电话号码:"; cin >> phone; break;
	case 2:cout << "请输入新的住址:"; cin >> address; break;
	default:cout << "输入错误，修改失败" << endl;
	}
}
