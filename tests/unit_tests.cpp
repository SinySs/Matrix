#include <gtest/gtest.h>
#include <iostream>
#include "../include/matrix.h"



TEST(Matrix, check_constructor)
{
    double a[] = {1, 2, 3, 4};
    matrix<double> m(2, 2, a);

    ASSERT_EQ(m[1][1], 1);
}

TEST(Matrix, check_equals)
{
    double a[] = {1, 2, 3, 4};
    matrix<double> m(2, 2, a);
    matrix<double> mm(2, 2, a);

    matrix<double> mmm = mm;

    ASSERT_EQ(m, mm);
    ASSERT_EQ(mmm, mm);
}


TEST(Matrix, check_no_equals)
{
    double a[] = {1, 2, 3, 4};
    matrix<double> m(2, 2, a);
    matrix<double> mm(2, 2, a);

    mm[1][1] = 1.1;

    ASSERT_FALSE(m == mm);
}

TEST(Matrix, check_mult)
{
    double a[] = {1, 1, 1, 1};
    double aa[] = {2, 2, 2, 2};

    matrix<double> m(2, 2, a);
    matrix<double> mm(2, 2, aa);

    m *= 2;

    ASSERT_EQ(m, mm);
}

TEST(Matrix, check_sum)
{
    double a[] = {1, 1, 1, 1};
    double aa[] = {2, 2, 2, 2};

    matrix<double> m(2, 2, a);
    matrix<double> mm(2, 2, aa);

    mm += m;
    m *= 3;

    ASSERT_EQ(m, mm);
}

TEST(Matrix, check_dif)
{
    double a[] = {1, 1, 1, 1};
    double aa[] = {2, 2, 2, 2};

    matrix<double> m(2, 2, a);
    matrix<double> mm(2, 2, aa);

    mm -= m;

    ASSERT_EQ(m, mm);
}

TEST(Matrix, transpose)
{
    double a[] = {1, 5, 100, 1};
    double aa[] = {1, 100, 5, 1};

    matrix<double> m(2, 2, a);
    matrix<double> mm(2, 2, aa);

    mm.transpose();

    ASSERT_EQ(m, mm);
}


int main(int argc, char **argv)
{

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}