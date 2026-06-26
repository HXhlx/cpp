CXX      = g++
CXXFLAGS = -std=c++23 -fmodules-ts -Wall -Wextra -O2
CFLAGS   = -O2
SQLITE_INC = -Ithird_party/sqlite

.PHONY: all clean test

all: wage_mgmt

# ── 标准库头文件单元 ──
gcm.cache/algorithm.gcm:
	$(CXX) $(CXXFLAGS) -xc++-system-header algorithm

gcm.cache/fstream.gcm:
	$(CXX) $(CXXFLAGS) -xc++-system-header fstream

gcm.cache/iostream.gcm:
	$(CXX) $(CXXFLAGS) -xc++-system-header iostream

gcm.cache/list.gcm:
	$(CXX) $(CXXFLAGS) -xc++-system-header list

gcm.cache/sstream.gcm:
	$(CXX) $(CXXFLAGS) -xc++-system-header sstream

gcm.cache/string.gcm:
	$(CXX) $(CXXFLAGS) -xc++-system-header string

gcm.cache/vector.gcm:
	$(CXX) $(CXXFLAGS) -xc++-system-header vector

HEADER_GCMS = gcm.cache/algorithm.gcm gcm.cache/fstream.gcm gcm.cache/iostream.gcm \
              gcm.cache/list.gcm gcm.cache/sstream.gcm gcm.cache/string.gcm gcm.cache/vector.gcm

# ── SQLite ──
build/sqlite3.o: third_party/sqlite/sqlite3.c
	@mkdir -p build
	$(CC) $(CFLAGS) $(SQLITE_INC) -c $< -o $@

# ── 模块接口 ──
gcm.cache/WageSystem.gcm: modules/WageSystem.cppm $(HEADER_GCMS)
	$(CXX) $(CXXFLAGS) $(SQLITE_INC) -x c++ -c $< -o /dev/null

# ── 模块实现 ──
build/Staff.o: src/Staff.cpp gcm.cache/WageSystem.gcm
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Salary.o: src/Salary.cpp gcm.cache/WageSystem.gcm
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Charge.o: src/Charge.cpp gcm.cache/WageSystem.gcm
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Administrator.o: src/Administrator.cpp gcm.cache/WageSystem.gcm
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Database.o: src/Database.cpp gcm.cache/WageSystem.gcm
	$(CXX) $(CXXFLAGS) $(SQLITE_INC) -c $< -o $@

build/Main.o: src/Main.cpp gcm.cache/WageSystem.gcm $(HEADER_GCMS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ── 主程序 ──
wage_mgmt: build/Main.o build/Staff.o build/Salary.o build/Charge.o build/Administrator.o build/Database.o build/sqlite3.o
	$(CXX) $^ -ldl -lpthread -o $@

# ── 测试 ──
build/test_staff.o: tests/test_staff.cpp gcm.cache/WageSystem.gcm $(HEADER_GCMS)
	$(CXX) $(CXXFLAGS) -DENABLE_TEST_ACCESS -c $< -o $@

build/test_salary.o: tests/test_salary.cpp gcm.cache/WageSystem.gcm $(HEADER_GCMS)
	$(CXX) $(CXXFLAGS) -DENABLE_TEST_ACCESS -c $< -o $@

build/test_charge.o: tests/test_charge.cpp gcm.cache/WageSystem.gcm $(HEADER_GCMS)
	$(CXX) $(CXXFLAGS) -DENABLE_TEST_ACCESS -c $< -o $@

build/test_administrator.o: tests/test_administrator.cpp gcm.cache/WageSystem.gcm $(HEADER_GCMS)
	$(CXX) $(CXXFLAGS) -DENABLE_TEST_ACCESS -c $< -o $@

build/test_database.o: tests/test_database.cpp gcm.cache/WageSystem.gcm $(HEADER_GCMS)
	$(CXX) $(CXXFLAGS) -DENABLE_TEST_ACCESS -c $< -o $@

GTEST_DIR = build/gtest/lib

$(GTEST_DIR)/libgtest_main.a:
	@mkdir -p build/gtest/src && cd build/gtest/src && \
	 git clone --depth 1 --branch v1.14.0 https://github.com/google/googletest.git . 2>/dev/null || true && \
	 cd build && cmake .. -G "Unix Makefiles" 2>&1 | tail -1 && make -j$$(nproc) gtest gtest_main 2>&1 | tail -1 && \
	 mkdir -p $(GTEST_DIR) && cp lib/*.a $(GTEST_DIR)/ 2>/dev/null; \
	 echo "gtest built"

wage_tests: $(addprefix build/test_,staff.o salary.o charge.o administrator.o database.o) \
            build/Staff.o build/Salary.o build/Charge.o build/Administrator.o build/Database.o build/sqlite3.o \
            | $(GTEST_DIR)/libgtest_main.a
	$(CXX) $^ -L$(GTEST_DIR) -lgtest_main -lgtest -ldl -lpthread -o $@

test: wage_tests
	./wage_tests

clean:
	rm -rf build gcm.cache wage_mgmt wage_tests
