module;
#include <fstream>
#include <string>
#include <vector>
export module Charge;

import Staff;
import Salary;

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
    ~Charge() override = default;

    static void Find(const std::vector<Charge>& staff);
    static int  Login(std::vector<Charge>& staff);
    static void Statistics(const std::vector<Charge>& staff);

    void Delete(std::vector<Charge>& staff);
    void Calculate();
    void Input();
    void Modify();
    void Print() const;
};
