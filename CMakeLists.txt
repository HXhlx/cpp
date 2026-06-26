cmake_minimum_required(VERSION 3.14)
project(WageManagement LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── SQLite3（从源码编译） ──
add_library(sqlite3 STATIC third_party/sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC third_party/sqlite)
target_link_libraries(sqlite3 PRIVATE dl pthread)

# ── 主程序 ──
add_executable(wage_mgmt
    src/Main.cpp
    src/Staff.cpp
    src/Salary.cpp
    src/Charge.cpp
    src/Administrator.cpp
    src/Database.cpp
)
target_include_directories(wage_mgmt PRIVATE include)
target_link_libraries(wage_mgmt PRIVATE sqlite3)

# ── 测试（FetchContent 拉取 Google Test） ──
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(wage_tests
    tests/test_staff.cpp
    tests/test_salary.cpp
    tests/test_charge.cpp
    tests/test_administrator.cpp
    tests/test_database.cpp
    src/Staff.cpp
    src/Salary.cpp
    src/Charge.cpp
    src/Administrator.cpp
    src/Database.cpp
)
target_include_directories(wage_tests PRIVATE include)
target_compile_definitions(wage_tests PRIVATE ENABLE_TEST_ACCESS)
target_link_libraries(wage_tests PRIVATE GTest::gtest_main sqlite3)

include(GoogleTest)
gtest_discover_tests(wage_tests)
