module;
#include <string>
#include <vector>
#include <list>
#include "sqlite3.h"
export module Database;

import Staff;
import Salary;
import Charge;
import Administrator;

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

    void SaveAll(const std::list<Administrator>& adm,
                 const std::vector<Charge>& staff);
    void LoadAll(std::list<Administrator>& adm,
                 std::vector<Charge>& staff);
};
