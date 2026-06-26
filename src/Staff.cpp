module;
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
module WageSystem;

Staff::Staff(unsigned w, const std::string& i, const std::string& n)
    : id_(i), name_(n), wage_(w) {}

void Staff::Find(const std::vector<Staff>& staff) {
    size_t t;
    Staff sta;
    std::cout << "\n请选择查询项目\n"
              << "1.工资卡号  2.身份证号  3.姓名  4.性别  5.年龄\n"
              << "6.手机号码  7.部门      8.职务  9.住址\n";
    std::cin >> t;
    switch (t) {
    case 1:
        std::cout << "请输入工资卡号:";
        std::cin >> sta.wage_;
        for (const auto& s : staff)
            if (s.wage_ == sta.wage_) s.Print();
        break;
    case 2:
        std::cout << "请输入身份证号:";
        std::cin >> sta.id_;
        for (const auto& s : staff)
            if (s.id_ == sta.id_) s.Print();
        break;
    case 3:
        std::cout << "请输入姓名:";
        std::cin >> sta.name_;
        for (const auto& s : staff)
            if (s.name_ == sta.name_) s.Print();
        break;
    case 4:
        std::cout << "请输入性别:";
        std::cin >> sta.gender_;
        for (const auto& s : staff)
            if (s.gender_ == sta.gender_) s.Print();
        break;
    case 5:
        std::cout << "请输入年龄:";
        std::cin >> sta.age_;
        for (const auto& s : staff)
            if (s.age_ == sta.age_) s.Print();
        break;
    case 6:
        std::cout << "请输入手机号码:";
        std::cin >> sta.phone_;
        for (const auto& s : staff)
            if (s.phone_ == sta.phone_) s.Print();
        break;
    case 7:
        std::cout << "请输入部门:";
        std::cin >> sta.department_;
        for (const auto& s : staff)
            if (s.department_ == sta.department_) s.Print();
        break;
    case 8:
        std::cout << "请输入职务:";
        std::cin >> sta.occupation_;
        for (const auto& s : staff)
            if (s.occupation_ == sta.occupation_) s.Print();
        break;
    case 9:
        std::cout << "请输入住址:";
        std::cin >> sta.address_;
        for (const auto& s : staff)
            if (s.address_ == sta.address_) s.Print();
        break;
    }
}

void Staff::BasicIn() {
    std::string a;
    std::cout << "请输入工资卡号/姓名/身份证号:";
    std::cin >> a;
    try {
        wage_ = static_cast<unsigned>(std::stoi(a));
    } catch (const std::exception&) {
        wage_ = 0;
    }
    id_   = a;
    name_ = a;
}

void Staff::Input(const Staff& prev) {
    unsigned n = prev.wage_ ? prev.wage_ : 10000;
    std::cout << "请输入员工信息(身份证号、姓名、性别、年龄、部门、职称、手机号码、住址):\n";
    while (true) {
        std::cin >> id_ >> name_ >> gender_ >> age_ >> department_
                 >> occupation_ >> phone_ >> address_;
        if (id_.size() == 18) break;
        std::cerr << "身份证号码格式错误,请重新输入:\n";
    }
    password_ = id_.substr(12);
    wage_ = ++n;
}

void Staff::Print() const {
    std::cout << "工资卡号:" << wage_
              << " 身份证号:" << id_
              << " 姓名:" << name_
              << " 性别:" << gender_
              << " 年龄:" << age_
              << " 部门:" << department_
              << " 职称:" << occupation_
              << " 手机号码:" << phone_
              << " 住址:" << address_
              << std::endl;
}


void Staff::Change() {
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
        std::cout << "请确认新密码:";
        std::cin >> p;
        if (k == p) {
            std::cout << "密码修改成功\n";
            password_ = p;
            return;
        }
        std::cerr << "密码输入错误,请重新输入:\n";
    }
}

void Staff::Modify() {
    int t;
    std::cout << "请输入你需要修改的信息（1.电话,2.住址）\n";
    std::cin >> t;
    switch (t) {
    case 1:
        std::cout << "请输入新的电话号码:";
        std::cin >> phone_;
        break;
    case 2:
        std::cout << "请输入新的住址:";
        std::cin >> address_;
        break;
    default:
        std::cout << "输入错误，修改失败\n";
    }
}
