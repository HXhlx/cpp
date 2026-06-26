# 工资管理系统

C++ 课程大作业 — 公司工资管理控制台应用

## 项目结构

```
├── CMakeLists.txt              # 构建配置
├── include/                    # 头文件
│   ├── Staff.h                 # 员工基类
│   ├── Salary.h                # 工资类（继承 Staff）
│   ├── Charge.h                # 费用类（继承 Salary）
│   ├── Administrator.h         # 管理员类
│   └── Database.h              # SQLite 数据库封装
├── src/                        # 源文件
│   ├── Main.cpp                # 主程序入口
│   ├── Staff.cpp
│   ├── Salary.cpp
│   ├── Charge.cpp
│   ├── Administrator.cpp
│   └── Database.cpp            # SQLite CRUD 实现
├── tests/                      # 单元测试（Google Test）
│   ├── test_staff.cpp
│   ├── test_salary.cpp
│   ├── test_charge.cpp
│   ├── test_administrator.cpp
│   └── test_database.cpp
└── third_party/
    └── sqlite/                 # SQLite 源码（amalgamation）
```

## 构建

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## 初始化数据库

首次运行需要创建管理员账号：

```bash
sqlite3 wage.db "INSERT INTO admin VALUES('admin','123456');"
```

## 运行

```bash
./build/wage_mgmt
```

## 运行测试

```bash
cd build
ctest --output-on-failure
```

## 功能

**管理员模式（16 项操作）：**
- 员工信息的增删改查
- 工资/费用数据录入与修改
- 按多维度查询、统计
- 管理员账号管理

**员工模式（6 项操作）：**
- 查看个人信息和工资
- 修改联系方式
- 打印工资单
- 修改密码

## 税金计算规则

| 应发工资 | 税率 |
|----------|------|
| ≤ 800    | 0%   |
| 800 ~ 1500 | (应发-800) × 5% |
| > 1500   | (应发-1500) × 10% |
