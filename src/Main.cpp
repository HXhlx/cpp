import <algorithm>;
import <iostream>;
import <list>;
import <vector>;
import WageSystem;

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

static bool AddEmployee(Database& db, std::vector<Charge>& staff) {
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
        db.AddStaff(s);
        std::cout << "是否继续添加员工?(y or n):";
        std::cin >> c;
    } while (c == 'y');
    return true;
}

static void ModifyEmployee(Administrator& administrator,
                           Database& db,
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
        if (t == 4)      administrator.ModifyStaff(*it);
        else if (t == 5) it->Salary::Modify();
        else if (t == 6) it->Modify();
        db.UpdateStaff(*it);
        std::cout << "是否继续修改?(y or n):";
        std::cin >> c;
    } while (c == 'y');
}

static void SaveAndExit(Database& db,
                        std::list<Administrator>& adm,
                        std::vector<Charge>& staff) {
    db.SaveAll(adm, staff);
    std::cout << "退出成功,信息已保存";
}

static bool RunAdminMenu(Administrator& administrator,
                         Database& db,
                         std::vector<Charge>& staff,
                         std::list<Administrator>& adm) {
    int t;
    PrintMenu(1);
    while (std::cin >> t) {
        std::cout << "\n";
        switch (t) {
        case 1: AddEmployee(db, staff); break;
        case 2: for (auto& s : staff) s.Salary::Input(); break;
        case 3: for (auto& s : staff) s.Input(); break;
        case 4: case 5: case 6: ModifyEmployee(administrator, db, staff, t); break;
        case 7: { std::vector<Staff> sta(staff.begin(), staff.end()); Staff::Find(sta); break; }
        case 8: { std::vector<Salary> salary(staff.begin(), staff.end()); Salary::Find(salary); break; }
        case 9: Charge::Find(staff); break;
        case 10: for (auto& s : staff) s.Print(); break;
        case 11: Charge::Statistics(staff); break;
        case 12: {
            Charge to_del; to_del.BasicIn();
            auto it = std::find(staff.begin(), staff.end(), to_del);
            if (it == staff.end()) { std::cerr << "删除失败\n"; }
            else { std::cout << "你是否要删除该员工信息?y/n\n"; char c; std::cin >> c;
                   if (c == 'y') { db.DeleteStaff(it->GetId()); staff.erase(it); std::cout << "删除成功\n"; } }
            break;
        }
        case 13: administrator.Change(adm); break;
        case 14: administrator.Input(adm); break;
        case 15: { bool self = administrator.Delete(adm); if (!self) break; SaveAndExit(db, adm, staff); return true; }
        case 16: SaveAndExit(db, adm, staff); return true;
        default: return false;
        }
        PrintMenu(1);
    }
    return false;
}

static bool RunStaffMenu(std::vector<Charge>& staff, Database& db, int n) {
    int t;
    PrintMenu(2);
    while (std::cin >> t) {
        std::cout << "\n";
        switch (t) {
        case 1: staff[n].Staff::Print(); break;
        case 2: staff[n].Salary::Print(); break;
        case 3: staff[n].Staff::Modify(); break;
        case 4: staff[n].Print(); break;
        case 5: staff[n].Change(); break;
        case 6: db.SaveAll({}, staff); std::cout << "退出成功,信息已保存"; return true;
        default: return false;
        }
        PrintMenu(2);
    }
    return false;
}

int main() {
    int i = 1;
    Database db("wage.db");
    std::list<Administrator> adm = db.LoadAllAdmins();
    std::vector<Charge> staff = db.LoadAllStaff();

    if (adm.empty()) { std::cerr << "系统找不到管理员信息,程序无法使用"; return EXIT_FAILURE; }

    if (!staff.empty()) {
        std::cout << "请选择登录方式:(1.管理员登录\t2.用户登录)\n";
        std::cin >> i;
    }

    if (staff.empty()) {
        Administrator administrator = Administrator::Login(adm);
        if (administrator == Administrator()) { std::cerr << "登录名或密码错误\n"; return EXIT_FAILURE; }
        AddEmployee(db, staff);
        RunAdminMenu(administrator, db, staff, adm);
        return EXIT_SUCCESS;
    }

    for (int attempt = 0; attempt < 3; ++attempt) {
        if (i == 1) {
            Administrator administrator = Administrator::Login(adm);
            if (!(administrator == Administrator())) { RunAdminMenu(administrator, db, staff, adm); return EXIT_SUCCESS; }
            std::cerr << "登录名或密码错误,请重新输入\n";
        } else if (i == 2) {
            int n = Charge::Login(staff);
            if (n != EOF) { RunStaffMenu(staff, db, n); return EXIT_SUCCESS; }
            std::cerr << "工资卡号/姓名/身份证号或密码错误,请重新输入\n";
        }
    }
    std::cerr << "已连续输错三次,程序将异常退出";
    return EXIT_FAILURE;
}
