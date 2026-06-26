module;
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include "sqlite3.h"
export module WageSystem;

// ═══════════════════════════════════════════
//  Staff
// ═══════════════════════════════════════════
export class Staff;
export bool operator==(const Staff& a, const Staff& b);

export class Staff {
    friend class Administrator;
    friend class Database;
    friend bool operator==(const Staff& a, const Staff& b);

#ifdef ENABLE_TEST_ACCESS
public:
#else
protected:
#endif
    std::string id_, name_, gender_, department_, occupation_, phone_, address_, password_;
    unsigned wage_ = 0;
    unsigned age_  = 0;

public:
    Staff() = default;
    Staff(unsigned w, const std::string& i, const std::string& n);

    static void Find(const std::vector<Staff>& staff);
    void BasicIn();
    void Input(const Staff& prev);
    void Print() const;
    void Change();
    void Modify();
    const std::string& GetId() const;
    
};

inline bool operator==(const Staff& a, const Staff& b) { return a.id_ == b.id_; }

inline const std::string& Staff::GetId() const { return id_; }

// ═══════════════════════════════════════════
//  Salary
// ═══════════════════════════════════════════
export class Salary : public Staff {
    friend class Database;

#ifdef ENABLE_TEST_ACCESS
public:
#else
protected:
#endif
    double basic_     = 0.0;
    double duty_      = 0.0;
    double bonus_     = 0.0;
    double salarysum_ = 0.0;

public:
    Salary() = default;
    Salary(unsigned w, const std::string& i, const std::string& n,
           double ba, double d, double bo);

    static void Find(const std::vector<Salary>& staff);
    void Input();
    void Modify();
    void Print() const;
};

// ═══════════════════════════════════════════
//  Charge
// ═══════════════════════════════════════════
export class Charge : public Salary {
    friend class Database;

#ifdef ENABLE_TEST_ACCESS
public:
#else
#endif
    double water_       = 0.0;
    double electricity_ = 0.0;
    double medicare_    = 0.0;
    double rax_         = 0.0;
    double realsalary_  = 0.0;

public:
    Charge() = default;
    Charge(unsigned w, const std::string& i, const std::string& n,
           double ba, double d, double bo,
           double wa, double e, double m);

    static void Find(const std::vector<Charge>& staff);
    static int  Login(std::vector<Charge>& staff);
    static void Statistics(const std::vector<Charge>& staff);
    void Delete(std::vector<Charge>& staff);
    void Calculate();
    void Input();
    void Modify();
    void Print() const;
};

// ═══════════════════════════════════════════
//  Administrator
// ═══════════════════════════════════════════
export class Administrator;
export bool operator==(const Administrator& a, const Administrator& b);

export class Administrator {
    friend bool operator==(const Administrator& a, const Administrator& b);
    friend class Database;

#ifdef ENABLE_TEST_ACCESS
public:
#else
#endif
    std::string name_;
    std::string password_;

public:
    Administrator() = default;
    Administrator(const std::string& n, const std::string& p);

    static void          In(std::fstream& is, std::list<Administrator>& adm);
    static Administrator Login(const std::list<Administrator>& adm);
    static void          Save(std::fstream& os, const std::list<Administrator>& adm);
    void Change(std::list<Administrator>& adm);
    bool Delete(std::list<Administrator>& adm);
    void Input(std::list<Administrator>& adm);
    void ModifyStaff(Staff& s) const;
    const std::string& GetName() const;
    const std::string& GetPassword() const;
    
    
};
inline bool operator==(const Administrator& a, const Administrator& b) {
    return a.name_ == b.name_ && a.password_ == b.password_;
}
inline const std::string& Administrator::GetName() const { return name_; }
inline const std::string& Administrator::GetPassword() const { return password_; }
// ═══════════════════════════════════════════
//  Database
// ═══════════════════════════════════════════
export class Database {
    sqlite3* db_ = nullptr;

public:
    explicit Database(const std::string& path = ":memory:");
    ~Database();
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    void InitTables();
    void                  AddStaff(const Charge& s);
    std::vector<Charge>   LoadAllStaff();
    void                  UpdateStaff(const Charge& s);
    void                  DeleteStaff(const std::string& id);
    int                   StaffCount();
    void                         AddAdmin(const Administrator& a);
    std::list<Administrator>     LoadAllAdmins();
    void                         DeleteAdmin(const std::string& name);
    void SaveAll(const std::list<Administrator>& adm, const std::vector<Charge>& staff);
    void LoadAll(std::list<Administrator>& adm, std::vector<Charge>& staff);
};

// ═══════════════════════════════════════════
//  Implementations
// ═══════════════════════════════════════════

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

// ── 序列化辅助（保留兼容旧格式） ──
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

Database::Database(const std::string& path) {
    if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK) {
        throw std::runtime_error(std::string("无法打开数据库: ") + sqlite3_errmsg(db_));
    }
    char* err = nullptr;
    sqlite3_exec(db_, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &err);
    if (err) sqlite3_free(err);
    InitTables();
}

Database::~Database() { if (db_) sqlite3_close(db_); }

void Database::InitTables() {
    const char* sql = R"SQL(
        CREATE TABLE IF NOT EXISTS staff (
            id TEXT PRIMARY KEY, wage INTEGER NOT NULL, name TEXT NOT NULL,
            gender TEXT DEFAULT '', age INTEGER DEFAULT 0,
            department TEXT DEFAULT '', occupation TEXT DEFAULT '',
            phone TEXT DEFAULT '', address TEXT DEFAULT '',
            password TEXT DEFAULT '', basic REAL DEFAULT 0,
            duty REAL DEFAULT 0, bonus REAL DEFAULT 0, salarysum REAL DEFAULT 0,
            water REAL DEFAULT 0, electricity REAL DEFAULT 0,
            medicare REAL DEFAULT 0, rax REAL DEFAULT 0, realsalary REAL DEFAULT 0
        );
        CREATE TABLE IF NOT EXISTS admin (
            name TEXT PRIMARY KEY, password TEXT NOT NULL
        );
    )SQL";
    char* err = nullptr;
    if (sqlite3_exec(db_, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        std::string msg = err ? err : "unknown error";
        sqlite3_free(err);
        throw std::runtime_error("建表失败: " + msg);
    }
}

void Database::AddStaff(const Charge& s) {
    const char* sql = R"SQL(
        INSERT OR REPLACE INTO staff
        (id,wage,name,gender,age,department,occupation,phone,address,
         password,basic,duty,bonus,salarysum,water,electricity,medicare,rax,realsalary)
        VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)
    )SQL";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt,  1, s.id_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,   2, static_cast<int>(s.wage_));
    sqlite3_bind_text(stmt,  3, s.name_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,  4, s.gender_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,   5, static_cast<int>(s.age_));
    sqlite3_bind_text(stmt,  6, s.department_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,  7, s.occupation_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,  8, s.phone_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,  9, s.address_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 10, s.password_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 11, s.basic_);
    sqlite3_bind_double(stmt, 12, s.duty_);
    sqlite3_bind_double(stmt, 13, s.bonus_);
    sqlite3_bind_double(stmt, 14, s.salarysum_);
    sqlite3_bind_double(stmt, 15, s.water_);
    sqlite3_bind_double(stmt, 16, s.electricity_);
    sqlite3_bind_double(stmt, 17, s.medicare_);
    sqlite3_bind_double(stmt, 18, s.rax_);
    sqlite3_bind_double(stmt, 19, s.realsalary_);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        throw std::runtime_error(std::string("Insert failed: ") + sqlite3_errmsg(db_));
    sqlite3_finalize(stmt);
}

std::vector<Charge> Database::LoadAllStaff() {
    std::vector<Charge> result;
    const char* sql = "SELECT id,wage,name,gender,age,department,occupation,"
                      "phone,address,password,basic,duty,bonus,salarysum,"
                      "water,electricity,medicare,rax,realsalary FROM staff";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Charge c;
        c.id_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        c.wage_ = static_cast<unsigned>(sqlite3_column_int(stmt, 1));
        c.name_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        c.gender_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        c.age_ = static_cast<unsigned>(sqlite3_column_int(stmt, 4));
        c.department_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        c.occupation_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        c.phone_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        c.address_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        c.password_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        c.basic_ = sqlite3_column_double(stmt, 10);
        c.duty_ = sqlite3_column_double(stmt, 11);
        c.bonus_ = sqlite3_column_double(stmt, 12);
        c.salarysum_ = sqlite3_column_double(stmt, 13);
        c.water_ = sqlite3_column_double(stmt, 14);
        c.electricity_ = sqlite3_column_double(stmt, 15);
        c.medicare_ = sqlite3_column_double(stmt, 16);
        c.rax_ = sqlite3_column_double(stmt, 17);
        c.realsalary_ = sqlite3_column_double(stmt, 18);
        result.push_back(c);
    }
    sqlite3_finalize(stmt);
    return result;
}

void Database::UpdateStaff(const Charge& s) { AddStaff(s); }

void Database::DeleteStaff(const std::string& id) {
    const char* sql = "DELETE FROM staff WHERE id = ?";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

int Database::StaffCount() {
    const char* sql = "SELECT COUNT(*) FROM staff";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void Database::AddAdmin(const Administrator& a) {
    const char* sql = "INSERT OR REPLACE INTO admin (name,password) VALUES (?,?)";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, a.GetName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, a.GetPassword().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

std::list<Administrator> Database::LoadAllAdmins() {
    std::list<Administrator> result;
    const char* sql = "SELECT name,password FROM admin";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        result.emplace_back(name, pass);
    }
    sqlite3_finalize(stmt);
    return result;
}

void Database::DeleteAdmin(const std::string& name) {
    const char* sql = "DELETE FROM admin WHERE name = ?";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void Database::SaveAll(const std::list<Administrator>& adm,
                       const std::vector<Charge>& staff) {
    char* err = nullptr;
    sqlite3_exec(db_, "DELETE FROM staff; DELETE FROM admin;", nullptr, nullptr, &err);
    if (err) sqlite3_free(err);
    for (const auto& a : adm) AddAdmin(a);
    for (const auto& s : staff) { Charge copy = s; copy.Calculate(); AddStaff(copy); }
}

void Database::LoadAll(std::list<Administrator>& adm, std::vector<Charge>& staff) {
    adm = LoadAllAdmins();
    staff = LoadAllStaff();
}
