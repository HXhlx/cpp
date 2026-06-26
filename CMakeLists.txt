cmake_minimum_required(VERSION 3.28)
project(WageManagement LANGUAGES CXX C)

# ── 启用 C++ 模块实验性支持 ──
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "c0834f14-82f9-4077-b514-251c56cc2e0d")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── SQLite3（从源码编译） ──
add_library(sqlite3 STATIC third_party/sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC third_party/sqlite)
target_link_libraries(sqlite3 PRIVATE dl pthread)

# ── C++ 模块编译选项 ──
add_library(wage_modules STATIC
    modules/Staff.cppm
    modules/Salary.cppm
    modules/Charge.cppm
    modules/Administrator.cppm
    modules/Database.cppm
    src/Staff.cpp
    src/Salary.cpp
    src/Charge.cpp
    src/Administrator.cpp
    src/Database.cpp
)
target_include_directories(wage_modules PRIVATE include third_party/sqlite)
target_compile_features(wage_modules PUBLIC cxx_std_23)
target_link_libraries(wage_modules PUBLIC sqlite3)
set_target_properties(wage_modules PROPERTIES CXX_SCAN_FOR_MODULES ON)

# ── 主程序 ──
add_executable(wage_mgmt src/Main.cpp)
target_compile_features(wage_mgmt PRIVATE cxx_std_23)
target_link_libraries(wage_mgmt PRIVATE wage_modules)
set_target_properties(wage_mgmt PROPERTIES CXX_SCAN_FOR_MODULES ON)

# ── 测试 ──
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
)
target_compile_features(wage_tests PRIVATE cxx_std_23)
target_compile_definitions(wage_tests PRIVATE ENABLE_TEST_ACCESS)
target_link_libraries(wage_tests PRIVATE GTest::gtest_main wage_modules)
set_target_properties(wage_tests PROPERTIES CXX_SCAN_FOR_MODULES ON)

include(GoogleTest)
gtest_discover_tests(wage_tests)
