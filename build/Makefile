# ==========================================================
# global variables:
# ==========================================================

# Points to the root of Google Test, relative to where this file is.
GTEST_DIR = ../dependencies/googletest

# Where to find user code.
USER_DIR = ..

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -O3 -std=c++14

# All Google Test headers. CONSTANT
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

# source data for gtest
GTEST_SRCS = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# libs to use
LIBS =


# ==========================================================
# gtest compilation
# ==========================================================

gtest-all.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o 
	$(AR) $(ARFLAGS) $@ $^


# ==========================================================
# preparation files:
# ==========================================================

# add here .cpp of classes to test
big_uint.o : $(USER_DIR)/scr/big_uint.cpp $(USER_DIR)/scr/big_uint.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/scr/big_uint.cpp

# add here tests to run
test_big_uint.o : $(USER_DIR)/tests/test_big_uint.cc $(USER_DIR)/scr/big_uint.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(USER_DIR) -c $(USER_DIR)/tests/test_big_uint.cc


# ==========================================================
# Make run setup:
# ==========================================================

# do not forget to list all .o files here
utests : big_uint.o test_big_uint.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


.PHONY: clean
clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o utests

