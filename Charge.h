#ifndef CHARGE_H
#define CHARGE_H
#include"Salary.h"
using namespace std;
class Charge :public Salary
{
	double water, electricity, medicare, rax, realsalary;
public:
	Charge(unsigned w = 0, string i = "", string n = "", double ba = 0, double d = 0, double bo = 0, double wa = 0, double e = 0, double m = 0) :Salary(w, i, n, ba, d, bo), water(wa), electricity(e), medicare(m) {}
	static void Find(vector<Charge>);				/*按费用信息查询*/
	static void In(fstream&, vector<Charge>&);			/*将员工文件输出到容器*/
	static int Login(vector<Charge>&);				/*员工登录*/
	static void Save(fstream&, vector<Charge>&);			/*保存到文件中*/
	static void Statistics(vector<Charge>);				/*统计总工资*/
	void Delete(vector<Charge>&);					/*删除员工数据*/
	void Feagure();							/*计算税金和实发工资*/
	void Input();							/*添加员工费用信息*/
	void Modify();							/*修改员工费用信息*/
	void Print();							/*打印工资单*/
};
#endif
