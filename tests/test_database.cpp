#include <gtest/gtest.h>
#include "Database.h"

class DatabaseTest : public ::testing::Test {
protected:
    Database* db;

    void SetUp() override {
        db = new Database(":memory:");
    }
    void TearDown() override {
        delete db;
    }
};

// ── 表创建 ──

TEST_F(DatabaseTest, InitTablesCreatesStaffAndAdmin) {
    // 表已由构造函数创建，验证可以正常插入
    db->AddAdmin(Administrator("test", "pass"));
    auto admins = db->LoadAllAdmins();
    EXPECT_EQ(admins.size(), 1u);
}

// ── 管理员 CRUD ──

TEST_F(DatabaseTest, AddAndLoadAdmin) {
    db->AddAdmin(Administrator("admin1", "pass1"));
    db->AddAdmin(Administrator("admin2", "pass2"));
    auto admins = db->LoadAllAdmins();
    EXPECT_EQ(admins.size(), 2u);
}

TEST_F(DatabaseTest, DeleteAdmin) {
    db->AddAdmin(Administrator("admin1", "pass1"));
    db->AddAdmin(Administrator("admin2", "pass2"));
    db->DeleteAdmin("admin1");
    auto admins = db->LoadAllAdmins();
    EXPECT_EQ(admins.size(), 1u);
    EXPECT_EQ(admins.front().GetName(), "admin2");
}

TEST_F(DatabaseTest, AddAdminUpsert) {
    db->AddAdmin(Administrator("admin", "old"));
    db->AddAdmin(Administrator("admin", "new"));
    auto admins = db->LoadAllAdmins();
    EXPECT_EQ(admins.size(), 1u);
    EXPECT_EQ(admins.front().GetPassword(), "new");
}

// ── 员工 CRUD ──

TEST_F(DatabaseTest, AddAndLoadStaff) {
    Charge c(10001, "110101199001011234", "张三", 3000, 2000, 500, 100, 200, 50);
    db->AddStaff(c);
    auto staff = db->LoadAllStaff();
    ASSERT_EQ(staff.size(), 1u);
    EXPECT_EQ(staff[0].id_, "110101199001011234");
    EXPECT_EQ(staff[0].name_, "张三");
    EXPECT_DOUBLE_EQ(staff[0].basic_, 3000.0);
}

TEST_F(DatabaseTest, AddMultipleStaff) {
    db->AddStaff(Charge(10001, "id1", "A", 1000, 500, 300, 10, 20, 5));
    db->AddStaff(Charge(10002, "id2", "B", 2000, 1000, 500, 30, 40, 10));
    EXPECT_EQ(db->StaffCount(), 2);
}

TEST_F(DatabaseTest, UpdateStaff) {
    Charge c(10001, "id1", "张三", 3000, 2000, 500, 100, 200, 50);
    db->AddStaff(c);
    c.name_ = "李四";
    db->UpdateStaff(c);
    auto staff = db->LoadAllStaff();
    ASSERT_EQ(staff.size(), 1u);
    EXPECT_EQ(staff[0].name_, "李四");
}

TEST_F(DatabaseTest, DeleteStaff) {
    db->AddStaff(Charge(10001, "id1", "A", 1000, 500, 300, 10, 20, 5));
    db->AddStaff(Charge(10002, "id2", "B", 2000, 1000, 500, 30, 40, 10));
    db->DeleteStaff("id1");
    EXPECT_EQ(db->StaffCount(), 1);
    auto staff = db->LoadAllStaff();
    EXPECT_EQ(staff[0].id_, "id2");
}

// ── SaveAll / LoadAll 往返测试 ──

TEST_F(DatabaseTest, SaveAllAndLoadAllRoundTrip) {
    std::list<Administrator> adm;
    adm.emplace_back("admin1", "pass1");
    adm.emplace_back("admin2", "pass2");

    std::vector<Charge> staff;
    staff.emplace_back(10001, "id1", "张三", 3000, 2000, 500, 100, 200, 50);
    staff.emplace_back(10002, "id2", "李四", 4000, 3000, 800, 150, 300, 80);

    db->SaveAll(adm, staff);

    std::list<Administrator> loaded_adm;
    std::vector<Charge> loaded_staff;
    db->LoadAll(loaded_adm, loaded_staff);

    EXPECT_EQ(loaded_adm.size(), 2u);
    EXPECT_EQ(loaded_staff.size(), 2u);
    EXPECT_EQ(loaded_staff[0].name_, "张三");
    EXPECT_EQ(loaded_staff[1].name_, "李四");
    EXPECT_DOUBLE_EQ(loaded_staff[0].salarysum_, 5500.0);
}

// ── 空字符串处理 ──

TEST_F(DatabaseTest, EmptyStringFieldsPersist) {
    Charge c(10001, "id1", "王五", 1000, 500, 300, 50, 60, 10);
    // gender, department 等为空
    db->AddStaff(c);
    auto staff = db->LoadAllStaff();
    ASSERT_EQ(staff.size(), 1u);
    EXPECT_TRUE(staff[0].gender_.empty());
    EXPECT_TRUE(staff[0].department_.empty());
}
