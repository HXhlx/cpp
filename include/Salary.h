#ifndef SALARY_H
#define SALARY_H

#include "Staff.h"

class Salary : public Staff {
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
    ~Salary() override = default;

    static void Find(const std::vector<Salary>& staff);
    void Input();
    void Modify();
    void Print() const;
};

#endif // SALARY_H
