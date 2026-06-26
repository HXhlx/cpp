#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include "Administrator.h"
#include "Charge.h"
#include "Salary.h"
#include "Staff.h"

// ── 跨平台清屏 ──
static void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

static void PrintMenu(int role) {
    std::cout << "\n按任意键继续...";
    std::cin.ignore();
    std::cin.get();
    ClearScreen();
    if (role == 1) {
        std::cout << "-----------*****公司(管理员专用)------------\n"
                  << "| 1.添加员工基本信息   2.员工工资数据录入  |\n"
                  << "| 3.员工费用数据录入   4.员工基本信息修改  |\n"
                  << "| 5.员工工资信息修改   6.员工费用信息修改  |\n"
                  << "| 7.按员工基本信息查询 8.按员工工资信息查询|\n"
                  << "| 9.按员工费用信息查询10.显示所有员工信息  |\n"
                  << "|11.统计总工资        12.删除员工数据      |\n"
                  << "|13.修改密码          14.添加管理员信息    |\n"
                  << "|15.删除管理员信息    16.保存更改并退出程序|\n";
    } else {
        std::cout << "----------*****公司(员工专用)------------\n"
                  << "|1.基本信息查询     2.应发工资查询      |\n"
                  << "|3.基本信息修改     4.打印工资单        |\n"
                  << "|5.修改密码         6.保存更改并退出程序|\n";
    }
    std::cout << "请选择操作:";
}

static bool AddEmployee(std::vector<Charge>& staff) {
    char c;
    Charge s;
    do {
        if (staff.empty())
            s.Staff::Input(Staff());
        else
            s.Staff::Input(staff.back());
        auto it = std::find(staff.begin(), staff.end(), s);
        if (it != staff.end()) {
            std::cerr << "姓名或者身份证号重复,添加员工失败\n";
            return false;
        }
        staff.push_back(s);
        std::cout << "是否继续添加员工?(y or n):";
        std::cin >> c;
    } while (c == 'y');
    return true;
}

static void ModifyEmployee(Administrator& administrator,
                           std::vector<Charge>& staff, int t) {
    char c;
    Charge s;
    do {
        s.BasicIn();
        auto it = std::find(staff.begin(), staff.end(), s);
        if (it == staff.end()) {
            std::cerr << "查无此人\n";
            break;
        }
        if (t == 4)
            administrator.ModifyStaff(*it);
        else if (t == 5)
            it->Salary::Modify();
        else if (t == 6)
            it->Modify();
        std::cout << "是否继续修改?(y or n):";
        std::cin >> c;
    } while (c == 'y');
}

static void SaveAndExit(std::fstream& ainout, std::fstream& uinout,
                        std::list<Administrator>& adm,
                        std::vector<Charge>& staff) {
    ainout.close();
    ainout.open("administrator.bin", std::fstream::out);
    uinout.close();
    uinout.open("staff.bin", std::fstream::out);
    if (ainout.fail() || uinout.fail()) {
        std::cerr << "文件打开失败,程序将异常退出";
        return;
    }
    Administrator::Save(ainout, adm);
    if (adm.empty()) {
        std::cout << "管理员为空,系统将清除所有用户信息!";
    } else {
        Charge::Save(uinout, staff);
        std::cout << "退出成功,信息已保存";
    }
}

static bool RunAdminMenu(Administrator& administrator,
                         std::vector<Charge>& staff,
                         std::list<Administrator>& adm,
                         std::fstream& ainout,
                         std::fstream& uinout) {
    int t;
    PrintMenu(1);
    while (std::cin >> t) {
        std::cout << "\n";
        switch (t) {
        case 1:
            AddEmployee(staff);
            break;
        case 2:
            for (auto& s : staff) s.Salary::Input();
            break;
        case 3:
            for (auto& s : staff) s.Input();
            break;
        case 4:
        case 5:
        case 6:
            ModifyEmployee(administrator, staff, t);
            break;
        case 7: {
            std::vector<Staff> sta(staff.begin(), staff.end());
            Staff::Find(sta);
            break;
        }
        case 8: {
            std::vector<Salary> salary(staff.begin(), staff.end());
            Salary::Find(salary);
            break;
        }
        case 9:
            Charge::Find(staff);
            break;
        case 10:
            for (auto& s : staff) s.Print();
            break;
        case 11:
            Charge::Statistics(staff);
            break;
        case 12:
            Charge().Delete(staff);
            break;
        case 13:
            administrator.Change(adm);
            break;
        case 14:
            administrator.Input(adm);
            break;
        case 15: {
            bool self_deleted = administrator.Delete(adm);
            if (!self_deleted) break;
            // 删除了自己 → 保存退出
            SaveAndExit(ainout, uinout, adm, staff);
            return true;
        }
        case 16:
            SaveAndExit(ainout, uinout, adm, staff);
            return true;
        default:
            return false;
        }
        PrintMenu(1);
    }
    return false;
}

static bool RunStaffMenu(std::vector<Charge>& staff,
                         std::fstream& uinout, int n) {
    int t;
    PrintMenu(2);
    while (std::cin >> t) {
        std::cout << "\n";
        switch (t) {
        case 1:
            staff[n].Staff::Print();
            break;
        case 2:
            staff[n].Salary::Print();
            break;
        case 3:
            staff[n].Staff::Modify();
            break;
        case 4:
            staff[n].Print();
            break;
        case 5:
            staff[n].Change();
            break;
        case 6:
            uinout.close();
            uinout.open("staff.bin", std::fstream::out);
            Charge::Save(uinout, staff);
            std::cout << "退出成功,信息已保存";
            return true;
        default:
            return false;
        }
        PrintMenu(2);
    }
    return false;
}

int main() {
    std::string a, u;
    int i = 1;
    std::fstream ainout("administrator.bin"), uinout("staff.bin");
    std::list<Administrator> adm;
    std::vector<Charge> staff;

    if (ainout.fail() || uinout.fail()) {
        std::cerr << "公司已倒闭，数据已清空";
        return EXIT_FAILURE;
    }

    ainout >> a;
    uinout >> u;

    if (a.empty()) {
        std::cerr << "系统找不到管理员信息,程序无法使用";
        return EXIT_FAILURE;
    }

    if (!u.empty()) {
        std::cout << "请选择登录方式:(1.管理员登录\t2.用户登录)\n";
        std::cin >> i;
    }

    // staff 文件为空时直接进入添加流程
    if (u.empty()) {
        ainout.seekg(0);
        Administrator::In(ainout, adm);
        Administrator administrator = Administrator::Login(adm);
        if (administrator == Administrator()) {
            std::cerr << "登录名或密码错误\n";
            return EXIT_FAILURE;
        }
        AddEmployee(staff);
        RunAdminMenu(administrator, staff, adm, ainout, uinout);
        return EXIT_SUCCESS;
    }

    ainout.seekg(0);
    uinout.seekg(0);

    for (int attempt = 0; attempt < 3; ++attempt) {
        if (i == 1) {
            Administrator::In(ainout, adm);
            Administrator administrator = Administrator::Login(adm);
            if (!(administrator == Administrator())) {
                char c = 'n';
                std::cout << "检测到系统中已存在用户文件,是否需要打开文件进行操作?\n"
                          << "y:是,我想打开文件\tn:否,我想直接输入,并替换掉原有文件\n";
                std::cin >> c;
                if (c == 'y') Charge::In(uinout, staff);
                RunAdminMenu(administrator, staff, adm, ainout, uinout);
                return EXIT_SUCCESS;
            }
            std::cerr << "登录名或密码错误,请重新输入\n";
        } else if (i == 2) {
            Charge::In(uinout, staff);
            int n = Charge::Login(staff);
            if (n != EOF) {
                RunStaffMenu(staff, uinout, n);
                return EXIT_SUCCESS;
            }
            std::cerr << "工资卡号/姓名/身份证号或密码错误,请重新输入\n";
        }
    }

    std::cerr << "已连续输错三次,程序将异常退出";
    return EXIT_FAILURE;
}
