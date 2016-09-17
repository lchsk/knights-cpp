#include "gtest/gtest.h"

#include "../src/util.h"

TEST(Util, flatten_int)
{
    EXPECT_EQ(ks::flatten_int(0, 0, 0), 0);
    EXPECT_EQ(ks::flatten_int(1, 1, 4), 5);
    EXPECT_EQ(ks::flatten_int(2, 3, 4), 11);
    EXPECT_EQ(ks::flatten_int(5, 0, 2), 10);
    EXPECT_EQ(ks::flatten_int(1, 4, 6), 10);
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
