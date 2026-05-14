//
// Created by ziadf on 5/26/2025.
//
#include "../include/Galios Field operations/GF2mAlpha.h"
#include <gtest/gtest.h>
#include <stdexcept>

class test_GF2mAlpha : public ::testing::Test {
protected:
    // You can add common setup here if needed
    void SetUp() override {
        // Optional setup before each test
    }

    void TearDown() override {
        // Optional cleanup after each test
    }
};

TEST_F(test_GF2mAlpha, GetPrimitivePolynomialKnownValues) {
    GF2mAlpha gf2(2);
    EXPECT_EQ(gf2.Getprimitivepolynomial(2), 0b111);
    EXPECT_EQ(gf2.Getprimitivepolynomial(3), 0b1011);
    EXPECT_EQ(gf2.Getprimitivepolynomial(10), 0b10000001001);
}

TEST_F(test_GF2mAlpha, ConstructorAndTables) {
    GF2mAlpha gf(4);
    EXPECT_EQ(gf.Getfieldsize(), 16);
    EXPECT_NE(gf.Logalpha(1), -1);
    EXPECT_EQ(gf.Alphapower(0), 1);
}

TEST_F(test_GF2mAlpha, AddOperation) {
    GF2mAlpha gf(4);
    EXPECT_EQ(gf.Add(3, 5), 3 ^ 5);
    EXPECT_EQ(gf.Add(0, 7), 7);
}

TEST_F(test_GF2mAlpha, MultiplyDivide) {
    GF2mAlpha gf(4);
    int a = 3, b = 5;
    int prod = gf.Multiply(a, b);
    int div = gf.Divide(prod, b);
    EXPECT_EQ(div, a);
}

TEST_F(test_GF2mAlpha, MultiplyIdentityAndZero) {
    GF2mAlpha gf(5);
    EXPECT_EQ(gf.Multiply(0, 7), 0);
    EXPECT_EQ(gf.Multiply(1, 7), 7);
}

TEST_F(test_GF2mAlpha, DivideByZeroThrows) {
    GF2mAlpha gf(3);
    EXPECT_THROW(gf.Divide(5, 0), std::invalid_argument);
}

TEST_F(test_GF2mAlpha, LogAlphaZeroThrows) {
    GF2mAlpha gf(3);
    EXPECT_THROW(gf.Logalpha(0), std::invalid_argument);
}

TEST_F(test_GF2mAlpha, InverseProperty) {
    GF2mAlpha gf(10);

    for (int a = 1; a < gf.Getfieldsize(); ++a) {
        int inv = gf.Inverse(a);
        int prod = gf.Multiply(a, inv);
        EXPECT_EQ(prod, 1) << "Failed for a = " << a;
    }
}

TEST_F(test_GF2mAlpha, ModolusOperation) {
    GF2mAlpha gf(3);
    EXPECT_LT(gf.Modolus(15), gf.Getfieldsize());
    EXPECT_EQ(gf.Modolus(5), 5);
    EXPECT_EQ(gf.Modolus(8), 0);
}

TEST_F(test_GF2mAlpha, Polyadd) {
    GF2mAlpha gf(4);
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{3, 2, 1};
    std::vector<int> expected{gf.Add(1, 3), gf.Add(2, 2), gf.Add(3, 1)};
    auto result = gf.Polyadd(a, b);
    EXPECT_EQ(result, expected);
}

TEST_F(test_GF2mAlpha, PolymulSimple) {
    GF2mAlpha gf(4);
    std::vector<int> a{1, 0};
    std::vector<int> b{1, 1};
    auto result = gf.Polymul(a, b);
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1);
    // more detailed checks can be added
}

TEST_F(test_GF2mAlpha, SubstituteEquation) {
    GF2mAlpha gf(4);
    std::vector<int> poly{1, 1};
    int val = 2;
    int expected = gf.Add(gf.Multiply(1, val), 1);
    EXPECT_EQ(gf.Subsituteinequation(poly, val), expected);
}




TEST_F(test_GF2mAlpha, Polydivide) {
    GF2mAlpha gf(4);
    std::vector<int> numerator{1, 0, 1};
    std::vector<int> denominator{1, 1};
    std::vector<int> quotient;
    auto remainder = gf.Polydivide(numerator, denominator, quotient);
    EXPECT_EQ(quotient.size(), 2);
    EXPECT_EQ(remainder.size(), 0);
}
