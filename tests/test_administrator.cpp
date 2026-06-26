#include <gtest/gtest.h>
import WageSystem;
#include <fstream>
#include <list>
#include <sstream>

// ── 构造函数测试 ──

TEST(AdminTest, DefaultConstructor) {
    Administrator a;
    // 默认构造后与空 Administrator 相等
    Administrator empty;
    EXPECT_TRUE(a == empty);
}

TEST(AdminTest, ParameterizedConstructor) {
    Administrator a("admin", "pass123");
    Administrator b("admin", "pass123");
    EXPECT_TRUE(a == b);
}

// ── operator== 测试 ──

TEST(AdminTest, EqualWhenSameCredentials) {
    Administrator a("admin", "pass123");
    Administrator b("admin", "pass123");
    EXPECT_TRUE(a == b);
}

TEST(AdminTest, NotEqualDifferentName) {
    Administrator a("admin1", "pass123");
    Administrator b("admin2", "pass123");
    EXPECT_FALSE(a == b);
}

TEST(AdminTest, NotEqualDifferentPassword) {
    Administrator a("admin", "pass123");
    Administrator b("admin", "pass456");
    EXPECT_FALSE(a == b);
}

TEST(AdminTest, NotEqualBothDifferent) {
    Administrator a("admin1", "pass123");
    Administrator b("admin2", "pass456");
    EXPECT_FALSE(a == b);
}

// ── Save/In 往返测试 ──

TEST(AdminTest, SaveAndInRoundTrip) {
    std::list<Administrator> original;
    original.emplace_back("admin1", "pass123");
    original.emplace_back("admin2", "pass456");

    // 写入临时文件
    {
        std::fstream out("/tmp/test_admin_save.bin", std::fstream::out);
        ASSERT_TRUE(out.is_open());
        Administrator::Save(out, original);
        out.close();
    }

    // 读回
    std::list<Administrator> loaded;
    {
        std::fstream in("/tmp/test_admin_save.bin", std::fstream::in);
        ASSERT_TRUE(in.is_open());
        Administrator::In(in, loaded);
        in.close();
    }

    ASSERT_EQ(loaded.size(), 2u);
    auto it = loaded.begin();
    EXPECT_EQ(it->name_, "admin1");
    EXPECT_EQ(it->password_, "pass123");
    ++it;
    EXPECT_EQ(it->name_, "admin2");
    EXPECT_EQ(it->password_, "pass456");
}

// ── Login 测试 ──

TEST(AdminTest, LoginSuccess) {
    std::list<Administrator> adm;
    adm.emplace_back("admin", "pass123");

    std::istringstream input("admin\npass123\n");
    std::cin.rdbuf(input.rdbuf());

    Administrator result = Administrator::Login(adm);
    EXPECT_FALSE(result == Administrator());  // 非空 = 登录成功

    std::cin.rdbuf(nullptr);
}

TEST(AdminTest, LoginFailure) {
    std::list<Administrator> adm;
    adm.emplace_back("admin", "pass123");

    std::istringstream input("admin\nwrongpass\n");
    std::cin.rdbuf(input.rdbuf());

    Administrator result = Administrator::Login(adm);
    EXPECT_TRUE(result == Administrator());  // 空 = 登录失败

    std::cin.rdbuf(nullptr);
}

// ── ModifyStaff 测试 ──

TEST(AdminTest, ModifyStaffId) {
    Staff s(10001, "110101199001011234", "张三");

    std::istringstream input("1\n110101199001011235\n");
    std::cin.rdbuf(input.rdbuf());

    Administrator a("admin", "pass");
    a.ModifyStaff(s);
    EXPECT_EQ(s.id_, "110101199001011235");

    std::cin.rdbuf(nullptr);
}

TEST(AdminTest, ModifyStaffName) {
    Staff s(10001, "110101199001011234", "张三");

    std::istringstream input("2\n李四\n");
    std::cin.rdbuf(input.rdbuf());

    Administrator a("admin", "pass");
    a.ModifyStaff(s);
    EXPECT_EQ(s.name_, "李四");

    std::cin.rdbuf(nullptr);
}
