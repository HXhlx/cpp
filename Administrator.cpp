#include<algorithm>
#include<fstream>
#include<iostream>
#include<list>
#include "Administrator.h"
using namespace std;
void Administrator::In(fstream&is, list<Administrator>&adm)
{
	Administrator a;
	while (is >> a.name >> a.password)adm.push_back(a);
}
void Administrator::Input(list<Administrator>&adm)
{
	cout << "请输入用户名:";
	cin >> name;
	cout << "请输入密码:";
	cin >> password;
	adm.push_back(*this);
}
Administrator Administrator::Login(list<Administrator>adm)
{
	string n, p;
	static int flag = 1;
	cout << "请输入登录名和密码:" << endl;
	cin >> n >> p;
	list<Administrator>::iterator r = find(adm.begin(), adm.end(), Administrator(n, p));
	if (r == adm.end())return Administrator();
	else return *r;
}
bool operator==(Administrator A, Administrator B)
{
	if (A.name == B.name&&A.password == B.password)return true;
	else return false;
}
void Administrator::Change(list<Administrator>&adm)
{
	string k, p;
	cout << "请输入原有密码:";
seventh:
	cin >> k;
	if (k != password)
	{
		cerr << "密码输入错误,请重新输入";
		goto seventh;
	}
eighth:
	cout << "请输入新密码:";
	cin >> k >> p;
	if (k == p)
	{
		cout << "密码修改成功" << endl;
		for (list<Administrator>::iterator r = adm.begin(); r != adm.end(); r++)if (*r == *this)(*r).password = k;
		password = p;
	}
	else
	{
		cerr << "密码输入错误,请重新输入" << endl;
		goto eighth;
	}
}
bool Administrator::Delete(list<Administrator>&adm)
{
	char c;
	string n, k;
sixth:
	cout << "请输入登录名和密码:" << endl;
	cin >> n >> k;
	list<Administrator>::iterator r = find(adm.begin(), adm.end(), Administrator(n, k));
	if (r == adm.end())
	{
		cerr << "登录名或密码输入错误,请重新输入" << endl;
		goto sixth;
	}
	else if (*r == *this)
	{
		cout << "你将删除本人的信息,是否确定?(y or n)";
		cin >> c;
		if (c == 'y')
		{
			adm.erase(r);
			cout << "删除成功,程序将自动退出!";
			return true;
		}
	}
	else
	{
		cout << "你将删除其他管理员的信息,是否确定?(y or n):";
		cin >> c;
		if (c == 'y')
		{
			adm.erase(r);
			cout << "删除成功!" << endl;
			return false;
		}
	}
	cerr << "删除失败";
	return false;
}
void Administrator::Save(fstream &os, list<Administrator>&adm)
{
	for (list<Administrator>::iterator a = adm.begin(); a != adm.end(); a++)os << (*a).name << " " << (*a).password << endl;
}
void Administrator::ModifyStaff(Staff &s)
{
	int t = 0;
	string newi;
	cout << "请选择你需要修改的信息（部门==1，职称==2）" << endl;
	cin >> t >> newi;
	if (t == 1)s.department = newi;
	else if (t == 2)s.occupation = newi;
	else cout << "输入出错，请重新选择要修改的信息" << endl;
}
