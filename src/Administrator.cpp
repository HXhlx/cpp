module;
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
module WageSystem;

Administrator::Administrator(const std::string& n, const std::string& p)
    : name_(n), password_(p) {}

void Administrator::In(std::fstream& is, std::list<Administrator>& adm) {
    Administrator a;
    while (is >> a.name_ >> a.password_)
        adm.push_back(a);
}

void Administrator::Input(std::list<Administrator>& adm) {
    char c = 'y';
    do {
        Administrator adm_obj;
        std::cout << "请输入用户名:";
        std::cin >> adm_obj.name_;
        std::cout << "请输入密码:";
        std::cin >> adm_obj.password_;
        adm.push_back(adm_obj);
        std::cout << "\n是否继续添加管理员?";
        std::cin >> c;
    } while (c == 'y');
}

Administrator Administrator::Login(const std::list<Administrator>& adm) {
    std::string n, p;
    std::cout << "请输入登录名和密码:\n";
    std::cin >> n >> p;
    auto it = std::find(adm.begin(), adm.end(), Administrator(n, p));
    if (it == adm.end()) return Administrator();
    return *it;
}


void Administrator::Change(std::list<Administrator>& adm) {
    std::string k, p;
    std::cout << "请输入原有密码:";
    while (true) {
        std::cin >> k;
        if (k == password_) break;
        std::cerr << "密码输入错误,请重新输入:";
    }
    while (true) {
        std::cout << "请输入新密码:";
        std::cin >> k;
        std::cout << "请再次输入新密码:";
        std::cin >> p;
        if (k == p) {
            std::cout << "密码修改成功\n";
            for (auto& a : adm) {
                if (a == *this) a.password_ = k;
            }
            password_ = p;
            return;
        }
        std::cerr << "密码输入错误,请重新输入\n";
    }
}

bool Administrator::Delete(std::list<Administrator>& adm) {
    char c;
    std::string n, k;
    std::cout << "请输入登录名和密码:\n";
    std::cin >> n >> k;
    auto it = std::find(adm.begin(), adm.end(), Administrator(n, k));
    if (it == adm.end()) {
        std::cerr << "删除失败\n";
        return false;
    }
    if (*it == *this) {
        std::cout << "你将删除本人的信息,是否确定?(y or n)";
        std::cin >> c;
        if (c == 'y') {
            adm.erase(it);
            std::cout << "删除成功,程序将自动退出!\n";
            return true;
        }
    } else {
        std::cout << "你将删除其他管理员的信息,是否确定?(y or n):";
        std::cin >> c;
        if (c == 'y') {
            adm.erase(it);
            std::cout << "删除成功!\n";
            return false;
        }
    }
    return false;
}

void Administrator::Save(std::fstream& os, const std::list<Administrator>& adm) {
    for (const auto& a : adm)
        os << a.name_ << " " << a.password_ << "\n";
}

void Administrator::ModifyStaff(Staff& s) const {
    int t;
    std::cout << "请选择你需要修改的信息（1.身份证号 2.姓名,3.部门,4.职位）\n";
    std::cin >> t;
    switch (t) {
    case 1:
        std::cout << "请输入新的身份证号:";
        std::cin >> s.id_;
        break;
    case 2:
        std::cout << "请输入新的姓名:";
        std::cin >> s.name_;
        break;
    case 3:
        std::cout << "请输入新的部门:";
        std::cin >> s.department_;
        break;
    case 4:
        std::cout << "请输入新的职位:";
        std::cin >> s.occupation_;
        break;
    default:
        std::cout << "输入出错，修改失败\n";
    }
}
