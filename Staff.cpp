#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<vector>
#include"Staff.h"
using namespace std;
void Staff::Input(Staff s)
{
	static int n;
	if(s.wage)n = s.wage;
	else n = 10000;
	cout << "请输入员工信息(身份证号、姓名、性别、年龄、部门、职称、手机号码、住址):" << endl;
	cin >> id >> name >> gender >> age >> department >> occupation >> phone >> address;
	password = id;
	password.erase(0, 12);
	wage = ++n;
}
void Staff::Print()
{
	cout<<"工资卡号"<<wage<<ends<<"身份证号:"<<id<<ends<<"姓名:"<<name<<ends<<"性别:"<<gender<<ends<<"年龄:"<<age<<ends<<"部门:"<<department<<ends<<"职称:"<<occupation<<ends<<"手机号码:"<<phone<<ends<<"住址:"<<address<<endl;
}
bool operator==(Staff A, Staff B)
{
	if (A.wage == B.wage || A.name == B.name || A.id == B.id)return true;
	else return false;
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
	string newi;
	cout << "请输入你需要修改的信息（1.姓名，2.性别，3.身份证号,4.电话，5.地址）" << endl;
	cin >> t >> newi;
	switch (t)
	{
	case 1:name = newi; break;
	case 2:gender = newi; break;
	case 3:id = newi; break;
	case 4:phone = newi; break;
	case 5:address = newi; break;
	default:cout << "输入错误，请重新选择需要修改的信息" << endl;
	}
}
