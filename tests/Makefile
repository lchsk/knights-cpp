GTEST_DIR = ../thirdparty/googletest/googletest
USER_DIR = .
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra
CPP_TEST_FLAGS = -pthread

##############################
#                            #
#	 List of tests	     #
#                            #
##############################

TEST_UTIL = test_util

##############################

TESTS = $(TEST_UTIL)

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
		$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

all: gtest.a $(TESTS)

clean:
	rm -f $(TESTS) gtest.a gtest_main.a *.o

check:
	$(foreach var, $(TESTS), ./$(var);)

gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	    $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	    $(GTEST_DIR)/src/gtest_main.cc

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

test_util:
	$(CXX) -I $(GTEST_DIR)/include/ \
	test_util.cpp gtest.a $(CPP_TEST_FLAGS) -o $(TEST_UTIL)
