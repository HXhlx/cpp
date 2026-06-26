#include <gtest/gtest.h>
import WageSystem;
#include <sstream>
#include <vector>

// ── 构造函数测试 ──

TEST(StaffTest, DefaultConstructor) {
    Staff s;
    EXPECT_EQ(s.wage_, 0u);
    EXPECT_TRUE(s.id_.empty());
    EXPECT_TRUE(s.name_.empty());
    EXPECT_TRUE(s.gender_.empty());
    EXPECT_TRUE(s.department_.empty());
    EXPECT_TRUE(s.occupation_.empty());
    EXPECT_TRUE(s.phone_.empty());
    EXPECT_TRUE(s.address_.empty());
    EXPECT_TRUE(s.password_.empty());
    EXPECT_EQ(s.age_, 0u);
}

TEST(StaffTest, ParameterizedConstructor) {
    Staff s(10001, "110101199001011234", "张三");
    EXPECT_EQ(s.wage_, 10001u);
    EXPECT_EQ(s.id_, "110101199001011234");
    EXPECT_EQ(s.name_, "张三");
    EXPECT_EQ(s.age_, 0u);  // 未设置的字段保持默认值
}

// ── operator== 测试 ──

TEST(StaffTest, EqualityById) {
    Staff a(10001, "110101199001011234", "张三");
    Staff b(10002, "110101199001011234", "李四");
    EXPECT_TRUE(a == b);   // 同 id → 相等
}

TEST(StaffTest, InequalityDifferentId) {
    Staff a(10001, "110101199001011234", "张三");
    Staff b(10001, "110101199001011235", "张三");
    EXPECT_FALSE(a == b);  // 不同 id → 不等
}

TEST(StaffTest, SameNameDifferentIdNotEqual) {
    Staff a(10001, "110101199001011234", "张三");
    Staff b(10002, "110101199001011235", "张三");
    EXPECT_FALSE(a == b);  // 同名不同 id → 不等（修复了原来的 OR 逻辑）
}

TEST(StaffTest, SameWageDifferentIdNotEqual) {
    Staff a(10001, "110101199001011234", "张三");
    Staff b(10001, "110101199001011235", "李四");
    EXPECT_FALSE(a == b);  // 同卡号不同 id → 不等
}

// ── Print 测试 ──

TEST(StaffTest, PrintOutputsAllFields) {
    Staff s(10001, "110101199001011234", "张三");
    s.gender_     = "男";
    s.age_        = 30;
    s.department_ = "技术部";
    s.occupation_ = "工程师";
    s.phone_      = "13800138000";
    s.address_    = "北京市";

    testing::internal::CaptureStdout();
    s.Print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("10001"), std::string::npos);
    EXPECT_NE(output.find("张三"), std::string::npos);
    EXPECT_NE(output.find("男"), std::string::npos);
    EXPECT_NE(output.find("技术部"), std::string::npos);
}

// ── Modify 测试 ──

TEST(StaffTest, ModifyPhone) {
    Staff s;
    s.phone_ = "13800138000";

    std::istringstream input("1\n13900139000\n");
    std::cin.rdbuf(input.rdbuf());
    s.Modify();
    EXPECT_EQ(s.phone_, "13900139000");

    // 恢复 stdin
    std::cin.rdbuf(nullptr);
}

TEST(StaffTest, ModifyAddress) {
    Staff s;
    s.address_ = "北京市";

    std::istringstream input("2\n上海市\n");
    std::cin.rdbuf(input.rdbuf());
    s.Modify();
    EXPECT_EQ(s.address_, "上海市");

    std::cin.rdbuf(nullptr);
}
