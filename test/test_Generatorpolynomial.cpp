//
// Created by ziadf on 5/26/2025.
//
#include <gtest/gtest.h>
#include "../include/Codeword/Generatorpolynomial.h"

class test_Generatorpolynomial : public ::testing::Test {
protected:
    int m = 4;  // GF(2^4)
    int n = 15; // Typical RS(n, k) values over GF(2^4)
    int k = 11; // So generator polynomial size should be n - k + 1 = 5
};

// Test valid generator polynomial is constructed and stored correctly
TEST_F(test_Generatorpolynomial, ValidPolynomialStoresCorrectly) {
    std::vector<int> poly = {1, 2, 3, 4, 5};
    Generatorpolynomial gp(poly, m, n, k);
    EXPECT_EQ(gp.GetGeneratorpolynomial(), poly);
}

// Test that constructor throws if polynomial size is not n - k + 1
TEST_F(test_Generatorpolynomial, PolynomialSizeMismatchThrows) {
    std::vector<int> wrongSizePoly = {1, 2, 3}; // Too short
    EXPECT_THROW(Generatorpolynomial gp(wrongSizePoly, m, n, k), std::invalid_argument);
}

// Test that constructor throws if a coefficient is outside of GF(2^m)
TEST_F(test_Generatorpolynomial, InvalidCoefficientThrows) {
    int fieldSize = 1 << m; // 16
    std::vector<int> badPoly = {0, 1, 2, 3, fieldSize}; // Last coefficient invalid
    EXPECT_THROW(Generatorpolynomial gp(badPoly, m, n, k), std::invalid_argument);
}

// Test with all-zero generator polynomial (still valid if size is correct)
TEST_F(test_Generatorpolynomial, AllZeroPolynomialAcceptedIfValidSize) {
    std::vector<int> zeros(n - k + 1, 0); // size 5
    Generatorpolynomial gp(zeros, m, n, k);
    EXPECT_EQ(gp.GetGeneratorpolynomial(), zeros);
}
