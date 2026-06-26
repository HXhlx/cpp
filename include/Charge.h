#ifndef CHARGE_H
#define CHARGE_H

#include <fstream>
#include "Salary.h"

class Charge : public Salary {

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
    ~Charge() override = default;

    static void Find(const std::vector<Charge>& staff);
    static void In(std::fstream& is, std::vector<Charge>& staff);
    static int  Login(std::vector<Charge>& staff);
    static void Save(std::fstream& os, std::vector<Charge>& staff);
    static void Statistics(const std::vector<Charge>& staff);

    void Delete(std::vector<Charge>& staff);
    void Calculate();
    void Input();
    void Modify();
    void Print() const;
};

#endif // CHARGE_H
