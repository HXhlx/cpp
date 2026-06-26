#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include "Salary.h"

// ── 构造函数测试 ──

TEST(SalaryTest, DefaultConstructor) {
    Salary s;
    EXPECT_EQ(s.basic_, 0.0);
    EXPECT_EQ(s.duty_, 0.0);
    EXPECT_EQ(s.bonus_, 0.0);
    EXPECT_EQ(s.salarysum_, 0.0);
    EXPECT_EQ(s.wage_, 0u);
}

TEST(SalaryTest, ParameterizedConstructor) {
    Salary s(10001, "110101199001011234", "张三", 3000, 2000, 500);
    EXPECT_DOUBLE_EQ(s.basic_, 3000.0);
    EXPECT_DOUBLE_EQ(s.duty_, 2000.0);
    EXPECT_DOUBLE_EQ(s.bonus_, 500.0);
    EXPECT_DOUBLE_EQ(s.salarysum_, 5500.0);
    EXPECT_EQ(s.wage_, 10001u);
    EXPECT_EQ(s.name_, "张三");
}

// ── Print 测试 ──

TEST(SalaryTest, PrintShowsSalaryInfo) {
    Salary s(10001, "110101199001011234", "张三", 3000, 2000, 500);

    testing::internal::CaptureStdout();
    s.Print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("基本工资:3000"), std::string::npos);
    EXPECT_NE(output.find("职务工资:2000"), std::string::npos);
    EXPECT_NE(output.find("奖金补贴:500"), std::string::npos);
    EXPECT_NE(output.find("应发工资:5500"), std::string::npos);
}

// ── Find 测试（需要 mock stdin） ──

TEST(SalaryTest, FindByBasicSalary) {
    std::vector<Salary> staff;
    staff.emplace_back(10001, "110101199001011234", "张三", 3000, 2000, 500);
    staff.emplace_back(10002, "110101199001011235", "李四", 4000, 2000, 500);

    std::istringstream input("1\n3000\n");
    std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    Salary::Find(staff);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("张三"), std::string::npos);
    EXPECT_EQ(output.find("李四"), std::string::npos);

    std::cin.rdbuf(nullptr);
}
