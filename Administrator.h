#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include<list>
#include<string>
#include"Staff.h"
using namespace std;
class Administrator
{
	friend bool operator==(Administrator, Administrator);
	string name, password;
public:
	Administrator(string n = "", string p = "") :name(n), password(p) {}
	static void In(fstream&, list<Administrator>&);				/*将管理员文件输出到链表中*/
	static Administrator Login(list<Administrator>);			/*管理员登录*/
	static void Save(fstream&, list<Administrator>&);			/*保存到文件中*/
	void Change(list<Administrator>&);					/*修改密码*/
	bool Delete(list<Administrator>&);					/*删除管理员信息*/
	void Input(list<Administrator>&);					/*添加管理员信息*/
	void ModifyStaff(Staff&);						/*修改员工基本信息*/
};
#endif
