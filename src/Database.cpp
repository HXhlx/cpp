#include <stdexcept>
#include <iostream>
#include "Database.h"
#include "sqlite3.h"

Database::Database(const std::string& path) {
    if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK) {
        throw std::runtime_error(
            std::string("无法打开数据库: ") + sqlite3_errmsg(db_));
    }
    // 启用外键约束
    char* err = nullptr;
    sqlite3_exec(db_, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &err);
    if (err) sqlite3_free(err);
    InitTables();
}

Database::~Database() {
    if (db_) sqlite3_close(db_);
}

void Database::InitTables() {
    const char* sql = R"SQL(
        CREATE TABLE IF NOT EXISTS staff (
            id          TEXT PRIMARY KEY,
            wage        INTEGER NOT NULL,
            name        TEXT NOT NULL,
            gender      TEXT DEFAULT '',
            age         INTEGER DEFAULT 0,
            department  TEXT DEFAULT '',
            occupation  TEXT DEFAULT '',
            phone       TEXT DEFAULT '',
            address     TEXT DEFAULT '',
            password    TEXT DEFAULT '',
            basic       REAL DEFAULT 0,
            duty        REAL DEFAULT 0,
            bonus       REAL DEFAULT 0,
            salarysum   REAL DEFAULT 0,
            water       REAL DEFAULT 0,
            electricity REAL DEFAULT 0,
            medicare    REAL DEFAULT 0,
            rax         REAL DEFAULT 0,
            realsalary  REAL DEFAULT 0
        );

        CREATE TABLE IF NOT EXISTS admin (
            name     TEXT PRIMARY KEY,
            password TEXT NOT NULL
        );
    )SQL";

    char* err = nullptr;
    if (sqlite3_exec(db_, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        std::string msg = err ? err : "unknown error";
        sqlite3_free(err);
        throw std::runtime_error("建表失败: " + msg);
    }
}

// ── 员工 CRUD ──

void Database::AddStaff(const Charge& s) {
    const char* sql = R"SQL(
        INSERT OR REPLACE INTO staff
        (id, wage, name, gender, age, department, occupation, phone, address,
         password, basic, duty, bonus, salarysum, water, electricity, medicare,
         rax, realsalary)
        VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)
    )SQL";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error(std::string("Prepare failed: ") + sqlite3_errmsg(db_));

    sqlite3_bind_text(stmt,  1, s.id_.c_str(),         -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,   2, static_cast<int>(s.wage_));
    sqlite3_bind_text(stmt,  3, s.name_.c_str(),       -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,  4, s.gender_.c_str(),     -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,   5, static_cast<int>(s.age_));
    sqlite3_bind_text(stmt,  6, s.department_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,  7, s.occupation_.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,  8, s.phone_.c_str(),      -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,  9, s.address_.c_str(),    -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 10, s.password_.c_str(),   -1, SQLITE_TRANSIENT);
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
    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error(std::string("Prepare failed: ") + sqlite3_errmsg(db_));

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Charge c;
        c.id_          = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        c.wage_        = static_cast<unsigned>(sqlite3_column_int(stmt, 1));
        c.name_        = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        c.gender_      = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        c.age_         = static_cast<unsigned>(sqlite3_column_int(stmt, 4));
        c.department_  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        c.occupation_  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        c.phone_       = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        c.address_     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        c.password_    = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        c.basic_       = sqlite3_column_double(stmt, 10);
        c.duty_        = sqlite3_column_double(stmt, 11);
        c.bonus_       = sqlite3_column_double(stmt, 12);
        c.salarysum_   = sqlite3_column_double(stmt, 13);
        c.water_       = sqlite3_column_double(stmt, 14);
        c.electricity_ = sqlite3_column_double(stmt, 15);
        c.medicare_    = sqlite3_column_double(stmt, 16);
        c.rax_         = sqlite3_column_double(stmt, 17);
        c.realsalary_  = sqlite3_column_double(stmt, 18);
        result.push_back(c);
    }
    sqlite3_finalize(stmt);
    return result;
}

void Database::UpdateStaff(const Charge& s) {
    // AddStaff 使用 INSERT OR REPLACE，等价于 upsert
    AddStaff(s);
}

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
    if (sqlite3_step(stmt) == SQLITE_ROW)
        count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

// ── 管理员 CRUD ──

void Database::AddAdmin(const Administrator& a) {
    const char* sql = "INSERT OR REPLACE INTO admin (name, password) VALUES (?,?)";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, a.GetName().c_str(),    -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, a.GetPassword().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

std::list<Administrator> Database::LoadAllAdmins() {
    std::list<Administrator> result;
    const char* sql = "SELECT name, password FROM admin";
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

// ── 持久化兼容接口 ──

void Database::SaveAll(const std::list<Administrator>& adm,
                       const std::vector<Charge>& staff) {
    // 清空后重新写入
    char* err = nullptr;
    sqlite3_exec(db_, "DELETE FROM staff; DELETE FROM admin;", nullptr, nullptr, &err);
    if (err) sqlite3_free(err);

    for (const auto& a : adm) AddAdmin(a);
    for (const auto& s : staff) {
        Charge copy = s;
        copy.Calculate();
        AddStaff(copy);
    }
}

void Database::LoadAll(std::list<Administrator>& adm,
                       std::vector<Charge>& staff) {
    adm   = LoadAllAdmins();
    staff = LoadAllStaff();
}
