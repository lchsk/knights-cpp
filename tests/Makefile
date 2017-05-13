GTEST_DIR = ../thirdparty/googletest/googletest
CPP_TEST_FLAGS = -pthread
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
GTEST_LIB = $(GTEST_DIR)/../googlemock/gtest/libgtest.a

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
	$(CXX) -I $(GTEST_DIR)/include/ \
	test_gps.cpp $(GTEST_LIB) $(CPP_TEST_FLAGS) -o $(TEST_GPS)
