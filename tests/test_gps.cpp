#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/graph.h"

// Vertices of the graph used in this file:
// 0   1  2  3
// 4   5  6  7
// 8   9 10 11
// 12 13 14 15

class GpsTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        // Vertices per column
        gps.v_col = 4;

        // Number of vertices in the graph
        gps.v_cnt = 16;
    }

    ks::Gps gps;
};

TEST_F(GpsTest, gps_basic_operations)
{
    EXPECT_TRUE(gps.is_top_row(0));
    EXPECT_TRUE(gps.is_top_row(1));
    EXPECT_TRUE(gps.is_top_row(2));
    EXPECT_TRUE(gps.is_top_row(3));
    EXPECT_FALSE(gps.is_top_row(4));
    EXPECT_FALSE(gps.is_top_row(5));
    EXPECT_FALSE(gps.is_top_row(6));
    EXPECT_FALSE(gps.is_top_row(7));
    EXPECT_FALSE(gps.is_top_row(8));
    EXPECT_FALSE(gps.is_top_row(9));
    EXPECT_FALSE(gps.is_top_row(10));
    EXPECT_FALSE(gps.is_top_row(11));
    EXPECT_FALSE(gps.is_top_row(12));
    EXPECT_FALSE(gps.is_top_row(13));
    EXPECT_FALSE(gps.is_top_row(14));
    EXPECT_FALSE(gps.is_top_row(15));

    EXPECT_FALSE(gps.is_bottom_row(0));
    EXPECT_FALSE(gps.is_bottom_row(1));
    EXPECT_FALSE(gps.is_bottom_row(2));
    EXPECT_FALSE(gps.is_bottom_row(3));
    EXPECT_FALSE(gps.is_bottom_row(4));
    EXPECT_FALSE(gps.is_bottom_row(5));
    EXPECT_FALSE(gps.is_bottom_row(6));
    EXPECT_FALSE(gps.is_bottom_row(7));
    EXPECT_FALSE(gps.is_bottom_row(8));
    EXPECT_FALSE(gps.is_bottom_row(9));
    EXPECT_FALSE(gps.is_bottom_row(10));
    EXPECT_FALSE(gps.is_bottom_row(11));
    EXPECT_TRUE(gps.is_bottom_row(12));
    EXPECT_TRUE(gps.is_bottom_row(13));
    EXPECT_TRUE(gps.is_bottom_row(14));
    EXPECT_TRUE(gps.is_bottom_row(15));

    EXPECT_TRUE(gps.is_left_col(0));
    EXPECT_FALSE(gps.is_left_col(1));
    EXPECT_FALSE(gps.is_left_col(2));
    EXPECT_FALSE(gps.is_left_col(3));
    EXPECT_TRUE(gps.is_left_col(4));
    EXPECT_FALSE(gps.is_left_col(5));
    EXPECT_FALSE(gps.is_left_col(6));
    EXPECT_FALSE(gps.is_left_col(7));
    EXPECT_TRUE(gps.is_left_col(8));
    EXPECT_FALSE(gps.is_left_col(9));
    EXPECT_FALSE(gps.is_left_col(10));
    EXPECT_FALSE(gps.is_left_col(11));
    EXPECT_TRUE(gps.is_left_col(12));
    EXPECT_FALSE(gps.is_left_col(13));
    EXPECT_FALSE(gps.is_left_col(14));
    EXPECT_FALSE(gps.is_left_col(15));

    EXPECT_FALSE(gps.is_right_col(0));
    EXPECT_FALSE(gps.is_right_col(1));
    EXPECT_FALSE(gps.is_right_col(2));
    EXPECT_TRUE(gps.is_right_col(3));
    EXPECT_FALSE(gps.is_right_col(4));
    EXPECT_FALSE(gps.is_right_col(5));
    EXPECT_FALSE(gps.is_right_col(6));
    EXPECT_TRUE(gps.is_right_col(7));
    EXPECT_FALSE(gps.is_right_col(8));
    EXPECT_FALSE(gps.is_right_col(9));
    EXPECT_FALSE(gps.is_right_col(10));
    EXPECT_TRUE(gps.is_right_col(11));
    EXPECT_FALSE(gps.is_right_col(12));
    EXPECT_FALSE(gps.is_right_col(13));
    EXPECT_FALSE(gps.is_right_col(14));
    EXPECT_TRUE(gps.is_right_col(15));
}

TEST_F(GpsTest, get_e)
{
    EXPECT_EQ(gps.get_e(12), 13);
    EXPECT_EQ(gps.get_e(6), 7);
    EXPECT_EQ(gps.get_e(11), -1);
    EXPECT_EQ(gps.get_e(3), -1);
}

TEST_F(GpsTest, get_s)
{
    EXPECT_EQ(gps.get_s(12), -1);
    EXPECT_EQ(gps.get_s(6), 10);
    EXPECT_EQ(gps.get_s(11), 15);
    EXPECT_EQ(gps.get_s(3), 7);
}

TEST_F(GpsTest, get_n)
{
    EXPECT_EQ(gps.get_n(4), 0);
    EXPECT_EQ(gps.get_n(10), 6);
    EXPECT_EQ(gps.get_n(0), -1);
    EXPECT_EQ(gps.get_n(3), -1);
}

TEST_F(GpsTest, get_w)
{
    EXPECT_EQ(gps.get_w(4), -1);
    EXPECT_EQ(gps.get_w(10), 9);
    EXPECT_EQ(gps.get_w(0), -1);
    EXPECT_EQ(gps.get_w(3), 2);
}

TEST_F(GpsTest, get_nw)
{
    EXPECT_EQ(gps.get_nw(4), -1);
    EXPECT_EQ(gps.get_nw(9), 4);
    EXPECT_EQ(gps.get_nw(0), -1);
    EXPECT_EQ(gps.get_nw(1), -1);
    EXPECT_EQ(gps.get_nw(2), -1);
    EXPECT_EQ(gps.get_nw(3), -1);
    EXPECT_EQ(gps.get_nw(7), 2);
    EXPECT_EQ(gps.get_nw(11), 6);
    EXPECT_EQ(gps.get_nw(15), 10);
}

TEST_F(GpsTest, get_ne)
{
    EXPECT_EQ(gps.get_ne(5), 2);
    EXPECT_EQ(gps.get_ne(14), 11);
    EXPECT_EQ(gps.get_ne(0), -1);
    EXPECT_EQ(gps.get_ne(1), -1);
    EXPECT_EQ(gps.get_ne(2), -1);
    EXPECT_EQ(gps.get_ne(3), -1);
    EXPECT_EQ(gps.get_ne(4), 1);
    EXPECT_EQ(gps.get_ne(8), 5);
    EXPECT_EQ(gps.get_ne(12), 9);
    EXPECT_EQ(gps.get_ne(15), -1);
}

TEST_F(GpsTest, get_se)
{
    EXPECT_EQ(gps.get_se(5), 10);
    EXPECT_EQ(gps.get_se(14), -1);
    EXPECT_EQ(gps.get_se(0), 5);
    EXPECT_EQ(gps.get_se(1), 6);
    EXPECT_EQ(gps.get_se(2), 7);
    EXPECT_EQ(gps.get_se(3), -1);
    EXPECT_EQ(gps.get_se(4), 9);
    EXPECT_EQ(gps.get_se(8), 13);
    EXPECT_EQ(gps.get_se(12), -1);
    EXPECT_EQ(gps.get_se(15), -1);
}

TEST_F(GpsTest, get_sw)
{
    EXPECT_EQ(gps.get_sw(5), 8);
    EXPECT_EQ(gps.get_sw(14), -1);
    EXPECT_EQ(gps.get_sw(0), -1);
    EXPECT_EQ(gps.get_sw(1), 4);
    EXPECT_EQ(gps.get_sw(2), 5);
    EXPECT_EQ(gps.get_sw(3), 6);
    EXPECT_EQ(gps.get_sw(4), -1);
    EXPECT_EQ(gps.get_sw(8), -1);
    EXPECT_EQ(gps.get_sw(12), -1);
    EXPECT_EQ(gps.get_sw(15), -1);
}

TEST_F(GpsTest, get_direction)
{
    EXPECT_EQ(gps.get_direction(5, 6), 1);
    EXPECT_EQ(gps.get_direction(15, 14), 3);
    EXPECT_EQ(gps.get_direction(13, 9), 0);
    EXPECT_EQ(gps.get_direction(13, 9), 0);
    EXPECT_EQ(gps.get_direction(3, 7), 2);

    // Doesn't exist (se)
    EXPECT_EQ(gps.get_direction(2, 7), -1);

    // Or some random numbers
    EXPECT_EQ(gps.get_direction(35, 88), -1);

    // Don't allow to move from rightmost column to leftmost etc.
    EXPECT_EQ(gps.get_direction(3, 4), -1);
    EXPECT_EQ(gps.get_direction(4, 3), -1);
    EXPECT_EQ(gps.get_direction(0, 12), -1);
    EXPECT_EQ(gps.get_direction(12, 0), -1);
}

TEST(Other, get_object_graph_ids)
{
    std::vector<int> a;
    EXPECT_THAT(a, ::testing::ContainerEq(ks::get_object_graph_ids(0, 0, 0, 0, 0)));
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
