#ifndef STAFF_H
#define STAFF_H
#include<string>
#include<vector>
using namespace std;
class Staff
{
	friend class Administrator;
	friend bool operator==(Staff, Staff);
protected:
	string id, name, gender, department, occupation, phone, address, password;
	unsigned wage, age;
public:
	Staff(unsigned w = 0, string i = "", string n = "") :wage(w), id(i), name(n) {}
	static void Find(vector<Staff>);		/*按基本信息查询*/
	void BasicIn();							/*基本输入*/
	void Input(Staff);						/*添加员工基本信息*/
	void Print();							/*基本信息查询*/
	void Change();							/*修改密码*/
	void Modify();							/*员工基本信息修改*/
};
#endif
