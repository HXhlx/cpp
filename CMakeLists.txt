cmake_minimum_required(VERSION 3.14)
project(WageManagement LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── 主程序 ──
add_executable(wage_mgmt
    src/Main.cpp
    src/Staff.cpp
    src/Salary.cpp
    src/Charge.cpp
    src/Administrator.cpp
)
target_include_directories(wage_mgmt PRIVATE include)

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
    src/Staff.cpp
    src/Salary.cpp
    src/Charge.cpp
    src/Administrator.cpp
)
target_include_directories(wage_tests PRIVATE include)
target_compile_definitions(wage_tests PRIVATE ENABLE_TEST_ACCESS)
target_link_libraries(wage_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(wage_tests)
