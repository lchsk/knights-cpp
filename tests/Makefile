GTEST_DIR = ../thirdparty/googletest/googletest
GMOCK_DIR = ../thirdparty/googletest/googlemock
CPP_TEST_FLAGS = -pthread
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

GTEST_LIB = $(GTEST_DIR)/../googlemock/gtest/libgtest.a
GMOCK_LIB = $(GTEST_DIR)/../googlemock/libgmock.a

##############################
#                            #
#        List of tests       #
#                            #
##############################

TEST_UTIL = test_util
TEST_GPS = test_gps

##############################

TESTS = $(TEST_UTIL) $(TEST_GPS)

all: $(GTEST_LIB) $(TESTS) check

clean:
	rm -f $(TESTS) *.o

check:
	$(foreach var, $(TESTS), ./$(var);)

test_util:
	$(CXX) -I $(GTEST_DIR)/include/ \
	test_util.cpp $(GTEST_LIB) $(CPP_TEST_FLAGS) -o $(TEST_UTIL) $(SFML_LIBS)

test_gps:
	$(CXX) -I $(GMOCK_DIR)/include/ -I $(GTEST_DIR)/include/  \
	test_gps.cpp ../src/graph.cpp $(GTEST_LIB) $(GMOCK_LIB) $(CPP_TEST_FLAGS) -o $(TEST_GPS) $(SFML_LIBS)
