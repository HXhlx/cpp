#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <fstream>
#include <list>
#include <string>
#include "Staff.h"

class Administrator {
    friend bool operator==(const Administrator& a, const Administrator& b);

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
};

#endif // ADMINISTRATOR_H
