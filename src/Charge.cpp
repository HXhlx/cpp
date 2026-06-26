#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Charge.h"

// ── 序列化辅助：空字符串用 "-" 占位 ──
static std::string SafeStr(const std::string& s) {
    return s.empty() ? "-" : s;
}
static std::string LoadStr(const std::string& s) {
    return (s == "-") ? "" : s;
}

Charge::Charge(unsigned w, const std::string& i, const std::string& n,
               double ba, double d, double bo,
               double wa, double e, double m)
    : Salary(w, i, n, ba, d, bo),
      water_(wa), electricity_(e), medicare_(m) {}

int Charge::Login(std::vector<Charge>& staff) {
    Charge s;
    s.BasicIn();
    std::cout << "请输入密码(默认身份证后6位):";
    std::cin >> s.password_;
    for (size_t i = 0; i < staff.size(); ++i) {
        if (staff[i] == s && staff[i].password_ == s.password_)
            return static_cast<int>(i);
    }
    return EOF;
}

void Charge::In(std::fstream& is, std::vector<Charge>& staff) {
    Charge s;
    while (is >> s.wage_ >> s.id_ >> s.name_ >> s.gender_ >> s.age_
              >> s.department_ >> s.occupation_ >> s.phone_ >> s.address_
              >> s.basic_ >> s.duty_ >> s.bonus_ >> s.salarysum_
              >> s.water_ >> s.electricity_ >> s.medicare_
              >> s.rax_ >> s.realsalary_ >> s.password_) {
        s.id_          = LoadStr(s.id_);
        s.name_        = LoadStr(s.name_);
        s.gender_      = LoadStr(s.gender_);
        s.department_  = LoadStr(s.department_);
        s.occupation_  = LoadStr(s.occupation_);
        s.phone_       = LoadStr(s.phone_);
        s.address_     = LoadStr(s.address_);
        s.password_    = LoadStr(s.password_);
        s.Calculate();
        staff.push_back(s);
    }
}

void Charge::Save(std::fstream& os, std::vector<Charge>& staff) {
    for (auto& s : staff) {
        s.Calculate();
        os << s.wage_ << " " << SafeStr(s.id_) << " " << SafeStr(s.name_) << " "
           << SafeStr(s.gender_) << " " << s.age_ << " " << SafeStr(s.department_) << " "
           << SafeStr(s.occupation_) << " " << SafeStr(s.phone_) << " " << SafeStr(s.address_) << " "
           << s.basic_ << " " << s.duty_ << " " << s.bonus_ << " "
           << s.salarysum_ << " " << s.water_ << " " << s.electricity_ << " "
           << s.medicare_ << " " << s.rax_ << " " << s.realsalary_ << " "
           << SafeStr(s.password_) << "\n";
    }
}

void Charge::Calculate() {
    salarysum_ = basic_ + duty_ + bonus_;
    if (salarysum_ <= 800)
        rax_ = 0;
    else if (salarysum_ <= 1500)
        rax_ = (salarysum_ - 800) * 0.05;
    else
        rax_ = (salarysum_ - 1500) * 0.1;
    realsalary_ = salarysum_ - rax_ - medicare_ - water_ - electricity_;
}

void Charge::Input() {
    if (water_ == 0.0 && electricity_ == 0.0 && medicare_ == 0.0) {
        Salary::Print();
        std::cout << "请输入水费、电费、医疗保险:";
        std::cin >> water_ >> electricity_ >> medicare_;
    }
}

void Charge::Print() const {
    Salary::Print();
    double sum = basic_ + duty_ + bonus_;
    double rax;
    if (sum <= 800)
        rax = 0;
    else if (sum <= 1500)
        rax = (sum - 800) * 0.05;
    else
        rax = (sum - 1500) * 0.1;
    double real = sum - rax - medicare_ - water_ - electricity_;
    std::cout << "水费:" << water_
              << " 电费:" << electricity_
              << " 医疗保险:" << medicare_
              << " 税金:" << rax
              << " 实发工资:" << real
              << "\n\n";
}

void Charge::Modify() {
    std::cout << "请输入新的员工费用信息(水费，电费，保险费):\n";
    std::cin >> water_ >> electricity_ >> medicare_;
    std::cout << "成功修改员工费用信息\n";
}

void Charge::Delete(std::vector<Charge>& staff) {
    Charge r;
    r.BasicIn();
    char c;
    auto it = std::find(staff.begin(), staff.end(), r);
    if (it == staff.end()) {
        std::cerr << "删除失败\n";
    } else {
        std::cout << "你是否要删除该员工信息?y/n\n";
        std::cin >> c;
        if (c == 'y') {
            staff.erase(it);
            std::cout << "删除成功\n";
        }
    }
}

void Charge::Find(const std::vector<Charge>& staff) {
    size_t t;
    Charge charge;
    std::cout << "\n请选择查询项目\n"
              << "1.水费  2.电费  3.医疗保险  4.税金  5.实发工资\n";
    std::cin >> t;
    switch (t) {
    case 1:
        std::cout << "请输入水费:";
        std::cin >> charge.water_;
        for (const auto& s : staff)
            if (s.water_ == charge.water_) s.Print();
        break;
    case 2:
        std::cout << "请输入电费:";
        std::cin >> charge.electricity_;
        for (const auto& s : staff)
            if (s.electricity_ == charge.electricity_) s.Print();
        break;
    case 3:
        std::cout << "请输入医疗保险:";
        std::cin >> charge.medicare_;
        for (const auto& s : staff)
            if (s.medicare_ == charge.medicare_) s.Print();
        break;
    case 4:
        std::cout << "请输入税金:";
        std::cin >> charge.rax_;
        for (const auto& s : staff) {
            double sum = s.basic_ + s.duty_ + s.bonus_;
            double rax;
            if (sum <= 800) rax = 0;
            else if (sum <= 1500) rax = (sum - 800) * 0.05;
            else rax = (sum - 1500) * 0.1;
            if (rax == charge.rax_) s.Print();
        }
        break;
    case 5:
        std::cout << "请输入实发工资:";
        std::cin >> charge.realsalary_;
        for (const auto& s : staff) {
            double sum = s.basic_ + s.duty_ + s.bonus_;
            double rax;
            if (sum <= 800) rax = 0;
            else if (sum <= 1500) rax = (sum - 800) * 0.05;
            else rax = (sum - 1500) * 0.1;
            double real = sum - rax - s.medicare_ - s.water_ - s.electricity_;
            if (real == charge.realsalary_) s.Print();
        }
        break;
    }
}

void Charge::Statistics(const std::vector<Charge>& staff) {
    double watersum = 0, electricitysum = 0, medicaresum = 0;
    double raxsum = 0, realsalarysum = 0, salarysumsum = 0;
    double basicsum = 0, bonussum = 0, dutysum = 0;
    for (const auto& s : staff) {
        basicsum += s.basic_;
        dutysum  += s.duty_;
        bonussum += s.bonus_;
        double sum = s.basic_ + s.duty_ + s.bonus_;
        salarysumsum += sum;
        watersum      += s.water_;
        electricitysum += s.electricity_;
        medicaresum   += s.medicare_;
        double rax;
        if (sum <= 800) rax = 0;
        else if (sum <= 1500) rax = (sum - 800) * 0.05;
        else rax = (sum - 1500) * 0.1;
        raxsum += rax;
        realsalarysum += sum - rax - s.medicare_ - s.water_ - s.electricity_;
    }
    std::cout << "总基本工资:" << basicsum
              << " 总职务工资:" << dutysum
              << " 总应发工资:" << salarysumsum
              << "\n总水费:" << watersum
              << " 总电费:" << electricitysum
              << " 总医疗保险:" << medicaresum
              << " 总税金:" << raxsum
              << " 总实际工资:" << realsalarysum
              << "\n";
}
