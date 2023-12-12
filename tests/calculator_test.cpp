#include "gtest/gtest.h"
#include "calculator.hpp"

TEST(CalcTest, Add)
{
    Calculator::Calculator calculator;

    // Test for Integer
    auto res_int = calculator.Add(3, 3, 4);
    EXPECT_EQ(res_int, 10);

    // Test for Float
    auto res_float = calculator.Add(3.2, 3.3, 4.1);
    EXPECT_EQ(res_float, 10.6);
}

TEST(CalcTest, Subtract)
{
    Calculator::Calculator calculator;

    // Test for Integer
    auto res_int = calculator.Subtract(3, 3, 4);
    EXPECT_EQ(res_int, -4);

    // Test for Float
    auto res_float = calculator.Subtract(3.2, 3.3, 4.1);
    EXPECT_EQ(res_float, -4.2);
}
TEST(CalcTest, Divide)
{
    Calculator::Calculator calculator;

    // Test for Integer
    auto res_int = calculator.Divide(3, 3, 4.0);
    EXPECT_EQ(res_int, 0.25);

    // Test for Float
    auto res_float = calculator.Divide(3.2, 3.3, 4.1);
    EXPECT_EQ(res_float, 0.236511);
}
TEST(CalcTest, Multiply)
{
    Calculator::Calculator calculator;

    // Test for Integer
    auto res_int = calculator.Multiply(3, 3, 4);
    EXPECT_EQ(res_int, 36);

    // Test for Float
    auto res_float = calculator.Multiply(3.2, 3.3, 4.1);
    EXPECT_EQ(res_float, 42.296);
}