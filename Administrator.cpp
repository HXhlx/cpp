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
	char c = 'y';
	Administrator Adm;
	do
	{
		cout << "请输入用户名:";
		cin >> Adm.name;
		cout << "请输入密码:";
		cin >> Adm.password;
		adm.push_back(Adm);
		cout << endl << "是否继续添加管理员?";
		cin >> c;
	} while (c == 'y');
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
	return A.name == B.name&&A.password == B.password;
}
void Administrator::Change(list<Administrator>&adm)
{
	string k, p;
	cout << "请输入原有密码:";
seventh:
	cin >> k;
	if (k != password)
	{
		cerr << "密码输入错误,请重新输入:";
		goto seventh;
	}
eighth:
	cout << "请输入新密码:";
	cin >> k;
	cout << "请再次输入新密码:";
	cin >> p;
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
	cout << "请输入登录名和密码:" << endl;
	cin >> n >> k;
	list<Administrator>::iterator r = find(adm.begin(), adm.end(), Administrator(n, k));
	if (r == adm.end())
	{
		cerr << "删除失败" << endl;
		return false;
	}
	else if (*r == *this)
	{
		cout << "你将删除本人的信息,是否确定?(y or n)";
		cin >> c;
		if (c == 'y')
		{
			adm.erase(r);
			cout << "删除成功,程序将自动退出!" << endl;
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
}
void Administrator::Save(fstream &os, list<Administrator>&adm)
{
	for (list<Administrator>::iterator a = adm.begin(); a != adm.end(); a++)os << (*a).name << " " << (*a).password << endl;
}
void Administrator::ModifyStaff(Staff &s)
{
	int t;
	cout << "请选择你需要修改的信息（1.身份证号2.姓名,3.部门,4.职位）" << endl;
	cin >> t;
	switch (t)
	{
	case 1:cout << "请输入新的身份证号:"; cin >> s.id; break;
	case 2:cout << "请输入新的姓名:"; cin >> s.name; break;
	case 3:cout << "请输入新的部门:"; cin >> s.department; break;
	case 4:cout << "请输入新的职位:"; cin >> s.occupation; break;
	default:cout << "输入出错，修改失败" << endl;
	}
}
