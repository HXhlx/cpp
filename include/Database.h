#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "Staff.h"
#include "Salary.h"
#include "Charge.h"
#include "Administrator.h"

// SQLite 前向声明
struct sqlite3;

class Database {
    sqlite3* db_ = nullptr;

public:
    explicit Database(const std::string& path = ":memory:");
    ~Database();

    // 禁止拷贝
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // ── 表初始化 ──
    void InitTables();

    // ── 员工 CRUD ──
    void                  AddStaff(const Charge& s);
    std::vector<Charge>   LoadAllStaff();
    void                  UpdateStaff(const Charge& s);
    void                  DeleteStaff(const std::string& id);
    int                   StaffCount();

    // ── 管理员 CRUD ──
    void                         AddAdmin(const Administrator& a);
    std::list<Administrator>     LoadAllAdmins();
    void                         DeleteAdmin(const std::string& name);

    // ── 持久化兼容接口 ──
    void SaveAll(const std::list<Administrator>& adm,
                 const std::vector<Charge>& staff);
    void LoadAll(std::list<Administrator>& adm,
                 std::vector<Charge>& staff);
};

#endif // DATABASE_H
