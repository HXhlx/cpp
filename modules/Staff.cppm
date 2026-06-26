module;
#include <string>
#include <vector>
export module Staff;

export class Staff {
    export friend class Administrator;
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
    virtual ~Staff() = default;

    static void Find(const std::vector<Staff>& staff);
    void BasicIn();
    void Input(const Staff& prev);
    void Print() const;
    void Change();
    void Modify();

    const std::string& GetId() const { return id_; }
};
