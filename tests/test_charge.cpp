#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "Charge.h"

// ── 构造函数测试 ──

TEST(ChargeTest, DefaultConstructor) {
    Charge c;
    EXPECT_EQ(c.wage_, 0u);
    EXPECT_DOUBLE_EQ(c.basic_, 0.0);
    EXPECT_DOUBLE_EQ(c.duty_, 0.0);
    EXPECT_DOUBLE_EQ(c.bonus_, 0.0);
    EXPECT_DOUBLE_EQ(c.salarysum_, 0.0);
}

TEST(ChargeTest, ParameterizedConstructor) {
    Charge c(10001, "110101199001011234", "张三",
             3000, 2000, 500, 100, 200, 50);
    EXPECT_EQ(c.wage_, 10001u);
    EXPECT_DOUBLE_EQ(c.basic_, 3000.0);
    EXPECT_DOUBLE_EQ(c.duty_, 2000.0);
    EXPECT_DOUBLE_EQ(c.bonus_, 500.0);
}

// ── Calculate（税金计算）测试 ──

TEST(ChargeTest, CalculateNoTax) {
    Charge c(10001, "id", "name", 500, 200, 50, 10, 20, 5);
    c.Calculate();
    EXPECT_DOUBLE_EQ(c.salarysum_, 750.0);
    EXPECT_DOUBLE_EQ(c.rax_, 0.0);
    EXPECT_DOUBLE_EQ(c.realsalary_, 750.0 - 5.0 - 10.0 - 20.0);
}

TEST(ChargeTest, CalculateFivePercentTax) {
    Charge c(10001, "id", "name", 600, 400, 200, 10, 20, 5);
    c.Calculate();
    EXPECT_DOUBLE_EQ(c.salarysum_, 1200.0);
    EXPECT_DOUBLE_EQ(c.rax_, 20.0);
    EXPECT_DOUBLE_EQ(c.realsalary_, 1200.0 - 20.0 - 5.0 - 10.0 - 20.0);
}

TEST(ChargeTest, CalculateTenPercentTax) {
    Charge c(10001, "id", "name", 1000, 500, 800, 10, 20, 5);
    c.Calculate();
    EXPECT_DOUBLE_EQ(c.salarysum_, 2300.0);
    EXPECT_DOUBLE_EQ(c.rax_, 80.0);
    EXPECT_DOUBLE_EQ(c.realsalary_, 2300.0 - 80.0 - 5.0 - 10.0 - 20.0);
}

TEST(ChargeTest, CalculateBoundary800) {
    Charge c(10001, "id", "name", 400, 300, 100, 0, 0, 0);
    c.Calculate();
    EXPECT_DOUBLE_EQ(c.salarysum_, 800.0);
    EXPECT_DOUBLE_EQ(c.rax_, 0.0);
}

TEST(ChargeTest, CalculateBoundary1500) {
    Charge c(10001, "id", "name", 800, 500, 200, 0, 0, 0);
    c.Calculate();
    EXPECT_DOUBLE_EQ(c.salarysum_, 1500.0);
    EXPECT_DOUBLE_EQ(c.rax_, 35.0);
}

// ── Save/In 往返测试 ──

TEST(ChargeTest, SaveAndInRoundTrip) {
    std::vector<Charge> original;
    original.emplace_back(10001, "110101199001011234", "张三",
                          3000, 2000, 500, 100, 200, 50);
    original.emplace_back(10002, "110101199001011235", "李四",
                          4000, 3000, 800, 150, 300, 80);

    const char* path = "/tmp/test_staff_save.bin";
    {
        std::fstream out(path, std::fstream::out);
        ASSERT_TRUE(out.is_open());
        Charge::Save(out, original);
        out.flush();
        out.close();
    }

    std::vector<Charge> loaded;
    {
        std::fstream in(path, std::fstream::in);
        ASSERT_TRUE(in.is_open());
        Charge::In(in, loaded);
        in.close();
    }

    ASSERT_EQ(loaded.size(), 2u);
    EXPECT_EQ(loaded[0].wage_, 10001u);
    EXPECT_EQ(loaded[0].name_, "张三");
    EXPECT_EQ(loaded[1].wage_, 10002u);
    EXPECT_EQ(loaded[1].name_, "李四");
    EXPECT_DOUBLE_EQ(loaded[0].basic_, 3000.0);
    EXPECT_DOUBLE_EQ(loaded[1].basic_, 4000.0);
    EXPECT_DOUBLE_EQ(loaded[0].salarysum_, 5500.0);
    EXPECT_DOUBLE_EQ(loaded[1].salarysum_, 7800.0);

    std::remove(path);
}

// ── Save/In 空字符串往返测试 ──

TEST(ChargeTest, SaveAndInEmptyFields) {
    std::vector<Charge> original;
    // 空 gender, department, phone, address
    original.emplace_back(10003, "id3", "王五",
                          1000, 500, 300, 50, 60, 10);

    const char* path = "/tmp/test_empty_fields.bin";
    {
        std::fstream out(path, std::fstream::out);
        Charge::Save(out, original);
        out.flush();
        out.close();
    }

    std::vector<Charge> loaded;
    {
        std::fstream in(path, std::fstream::in);
        Charge::In(in, loaded);
        in.close();
    }

    ASSERT_EQ(loaded.size(), 1u);
    EXPECT_EQ(loaded[0].name_, "王五");
    EXPECT_TRUE(loaded[0].gender_.empty());
    EXPECT_TRUE(loaded[0].department_.empty());

    std::remove(path);
}

// ── Delete 测试 ──
// 注意: BasicIn 将输入同时设为 wage_/id_/name_，
// operator== 按 id_ 匹配，所以测试用简单 id

TEST(ChargeTest, DeleteExistingEmployee) {
    std::vector<Charge> staff;
    // id 设为简单数字字符串，BasicIn 输入 "10001" 后 id_ 也为 "10001"
    staff.emplace_back(10001, "10001", "张三", 3000, 2000, 500, 100, 200, 50);
    staff.emplace_back(10002, "10002", "李四", 4000, 3000, 800, 150, 300, 80);

    std::istringstream input("10001\ny\n");
    std::cin.rdbuf(input.rdbuf());

    Charge().Delete(staff);
    EXPECT_EQ(staff.size(), 1u);
    EXPECT_EQ(staff[0].name_, "李四");

    std::cin.rdbuf(nullptr);
}

TEST(ChargeTest, DeleteNonexistentEmployee) {
    std::vector<Charge> staff;
    staff.emplace_back(10001, "10001", "张三", 3000, 2000, 500, 100, 200, 50);

    std::istringstream input("99999\n");
    std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStderr();
    Charge().Delete(staff);
    std::string err = testing::internal::GetCapturedStderr();

    EXPECT_NE(err.find("删除失败"), std::string::npos);
    EXPECT_EQ(staff.size(), 1u);

    std::cin.rdbuf(nullptr);
}

// ── Statistics 测试 ──

TEST(ChargeTest, StatisticsAggregates) {
    std::vector<Charge> staff;
    staff.emplace_back(10001, "id1", "A", 1000, 500, 300, 10, 20, 5);
    staff.emplace_back(10002, "id2", "B", 2000, 1000, 500, 30, 40, 10);

    testing::internal::CaptureStdout();
    Charge::Statistics(staff);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("总基本工资:3000"), std::string::npos);
    EXPECT_NE(output.find("总职务工资:1500"), std::string::npos);
}

// ── Print 不修改数据测试 ──

TEST(ChargeTest, PrintDoesNotModifyData) {
    Charge c(10001, "id", "name", 1000, 500, 300, 10, 20, 5);
    double orig_basic = c.basic_;

    testing::internal::CaptureStdout();
    c.Print();
    c.Print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_DOUBLE_EQ(c.basic_, orig_basic);
}
