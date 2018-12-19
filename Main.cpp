#include<algorithm>
#include<fstream>
#include<iostream>
#include<list>
#include<sstream>
#include<vector>
#include"Administrator.h"
#include"Charge.h"
#include"Staff.h"
#include"Salary.h"
using namespace std;
bool Input(vector<Charge>&staff)
{
	char c;
	Charge s;
	do
	{
		if (staff.empty())s.Staff::Input(Staff());
		else s.Staff::Input(staff.back());
		for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)if (*r == s)
		{
			cerr << "姓名或者身份证号重复,添加员工失败" << endl;
			return false;
		}
		staff.push_back(s);
		cout << "是否继续添加员工?(y or n):";
		cin >> c;
	} while (c == 'y');
}
void Modify(Administrator administrator,vector<Charge>&staff,int t)
{
	char c;
	Charge s;
	vector<Charge>::iterator r;
	do
	{
		s.BasicIn();
		for (r = staff.begin(); r != staff.end(); r++)if ((*r) == s)
		{
			if (t == 4)administrator.ModifyStaff(*r);
			else if (t == 5)(*r).Salary::Modify();
			else if (t == 6)(*r).Modify();
			break;
		}
		if (r == staff.end())
		{
			cerr << "查无此人" << endl;
			break;
		}
		cout << "是否继续修改?(y or n):";
		cin >> c;
	} while (c == 'y');
}
int main()
{
	bool b;
	char  c = 'n';
	string a, u;
	int i = 1, n, t = 1;
	Administrator administrator;
	Charge s;
	fstream ainout("administrator.bin"), uinout("staff.bin");
	list<Administrator>adm;
	vector<Charge>staff;
	if (ainout.fail() || uinout.fail())
	{
		cerr << "文件打开失败,程序将异常退出";
		return EXIT_FAILURE;
	}
	ainout >> a;
	uinout >> u;
	if (a == "")
	{
		cerr << "找不到管理员信息,程序将异常退出";
		return EXIT_FAILURE;
	}
	else if (u == "")goto first;
	else
	{
		cout << "请选择登录方式:(1.管理员登录	2.用户登录)" << endl;
		cin >> i;
	first:
		ainout.seekg(0);
		uinout.seekg(0);
		for (n = 0; n < 3; n++)
		{
			if (i == 1)
			{
				Administrator::In(ainout, adm);
				administrator = Administrator::Login(adm);
				if (!(administrator == Administrator()))
				{
					if (u == "")Input(staff);
					else
					{
						cout << "检测到系统中已存在用户文件,是否需要打开文件进行操作?" << endl;
						cout << "y:是,我想打开文件	n:否,我想直接输入,并替换掉原有文件" << endl;
						cin >> c;
						if (c == 'y')Charge::In(uinout, staff);
					}
					cout << "****公司（管理员专用）" << endl;
					cout << "1.添加员工基本信息	2.员工工资数据录入" << endl;
					cout << "3.员工费用数据录入	4.员工基本信息修改" << endl;
					cout << "5.员工工资信息修改	6.员工费用信息修改" << endl;
					cout << "7.查询员工信息		8.删除员工数据" << endl;
					cout << "9.修改密码			10.添加管理员信息" << endl;
					cout << "11.删除管理员信息	12.保存更改并退出程序" << endl;
					cout << "请选择操作:";
					while (cin >> t)
					{
						switch (t)
						{
						case 1:Input(staff); break;
						case 2:for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)(*r).Salary::Input(); break;
						case 3:for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)(*r).Input(); break;
						case 4:
						case 5:
						case 6:Modify(administrator, staff, t); break;
						case 7:
							for (vector<Charge>::iterator r = staff.begin(); r != staff.end(); r++)
							{
								(*r).Staff::Print();
								(*r).Print();
							}
							break;
						case 8:s.Delete(staff); break;
						case 9:administrator.Change(adm); break;
						case 10:administrator.Input(adm); break;
						case 11:
							b = administrator.Delete(adm);
							if (b == false)break;
						case 12:
							ainout.close();
							ainout.open("administrator.bin", fstream::out);
							uinout.close();
							uinout.open("staff.bin", fstream::out);
							if (ainout.fail() || uinout.fail())
							{
								cerr << "文件打开失败,程序将异常退出";
								return EXIT_FAILURE;
							}
							Administrator::Save(ainout, adm);
							if (adm.empty())cout << "管理员为空,系统将清除所有用户信息!";
							else Charge::Save(uinout, staff);
							cout << "退出成功!";
							return EXIT_SUCCESS;
						default:return EXIT_FAILURE;
						}
						cout << "请选择操作:";
					}
				}
				else cerr << "登录名或密码错误,请重新输入" << endl;
			}
			else if (i == 2)
			{
				Charge::In(uinout, staff);
				n = Charge::Login(staff);
				if (n != staff.size())
				{
					int t;
					cout << "****公司（员工专用）" << endl;
					cout << "1.基本信息查询	2.工资数据查询" << endl;
					cout << "3.基本信息修改	4.打印工资单" << endl;
					cout << "5.修改密码	6.保存更改并退出程序" << endl;
					cout << "请选择操作:";
					while (cin >> t)
					{
						switch (t)
						{
						case 1:staff[n].Staff::Print(); break;
						case 2:staff[n].Salary::Print(); break;
						case 3:staff[n].Staff::Modify(); break;
						case 4:staff[n].Print(); break;
						case 5:staff[n].Change(); break;
						case 6:
							uinout.close();
							uinout.open("staff.bin", fstream::out);
							Charge::Save(uinout, staff);
							cout << "退出成功!";
							return EXIT_SUCCESS;
						default:return EXIT_FAILURE;
						}
						cout << "请选择操作:";
					}
				}
				else cerr << "工资卡号/姓名/身份证号或密码错误,请重新输入" << endl;
			}
		}
		cerr << "已连续输错三次,程序将异常退出";
		return EXIT_FAILURE;
	}
}
