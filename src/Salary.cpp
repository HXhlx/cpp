#include <algorithm>
#include <iostream>
#include <vector>
#include "Salary.h"

Salary::Salary(unsigned w, const std::string& i, const std::string& n,
               double ba, double d, double bo)
    : Staff(w, i, n), basic_(ba), duty_(d), bonus_(bo) {
    salarysum_ = basic_ + duty_ + bonus_;
}

void Salary::Find(const std::vector<Salary>& staff) {
    size_t t;
    Salary salary;
    std::cout << "\n请选择查询项目\n"
              << "1.基本工资  2.职务工资  3.奖金补贴  4.应发工资\n";
    std::cin >> t;
    switch (t) {
    case 1:
        std::cout << "请输入基本工资:";
        std::cin >> salary.basic_;
        for (const auto& s : staff)
            if (s.basic_ == salary.basic_) s.Print();
        break;
    case 2:
        std::cout << "请输入职务工资:";
        std::cin >> salary.duty_;
        for (const auto& s : staff)
            if (s.duty_ == salary.duty_) s.Print();
        break;
    case 3:
        std::cout << "请输入奖金补贴:";
        std::cin >> salary.bonus_;
        for (const auto& s : staff)
            if (s.bonus_ == salary.bonus_) s.Print();
        break;
    case 4:
        std::cout << "请输入应发工资:";
        std::cin >> salary.salarysum_;
        for (const auto& s : staff) {
            double sum = s.basic_ + s.duty_ + s.bonus_;
            if (sum == salary.salarysum_) s.Print();
        }
        break;
    }
}

void Salary::Input() {
    if (basic_ == 0.0 && duty_ == 0.0 && bonus_ == 0.0) {
        Staff::Print();
        std::cout << "请输入基本工资、职务工资、奖金补贴:";
        std::cin >> basic_ >> duty_ >> bonus_;
    }
}

void Salary::Print() const {
    Staff::Print();
    double sum = basic_ + duty_ + bonus_;
    std::cout << "基本工资:" << basic_
              << " 职务工资:" << duty_
              << " 奖金补贴:" << bonus_
              << " 应发工资:" << sum
              << std::endl;
}

void Salary::Modify() {
    std::cout << "请输入新的员工工资信息：基本工资，职务工资，特别奖励\n";
    std::cin >> basic_ >> duty_ >> bonus_;
    std::cout << "成功修改员工工资信息\n";
}
