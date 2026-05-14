//
// Created by ziadf on 5/26/2025.
//
#include <gtest/gtest.h>
#include "../include/Decoding/Chiensearch.h" // Adjust path if needed

class test_Forneyalgorithm : public ::testing::Test {
protected:
    int m = 4;      // Field GF(2^4)
    int n = 15;     // Codeword length
    GF2mAlpha gf = GF2mAlpha(m);
};

// Test 1: Empty error locator polynomial should result in no error locations
TEST_F(test_Forneyalgorithm, EmptyLocatorPolynomialGivesNoErrors) {
    std::vector<int> locatorPoly = { 0 };
    Chiensearch cs(locatorPoly, m, n);

    std::vector<int> expected(n, 0);  // No error locations
    EXPECT_EQ(cs.Geterrorlocations(), expected);
}

// Test 2: Locator polynomial with single error at known position
// Example: error locator polynomial (x - α^i) → root at α^i⁻¹, position = n - log(α^i⁻¹) - 1
TEST_F(test_Forneyalgorithm, SingleErrorDetectedCorrectly) {
    int errorPosition = 5;
    int alpha_power = gf.Alphapower(n - errorPosition - 1);   // α^(n - pos - 1)
    std::vector<int> locatorPoly = {gf.Inverse(alpha_power), 1};  // (x - α^i)

    Chiensearch cs(locatorPoly, m, n);
    std::vector<int> locations = cs.Geterrorlocations();

    EXPECT_EQ(locations[errorPosition], 1);
    int count = std::count(locations.begin(), locations.end(), 1);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(cs.Geterrorlocationstring()[0], "symbol number " + std::to_string(errorPosition + 1));
}

// Test 3: Two error locations known
TEST_F(test_Forneyalgorithm, TwoErrorsAreDetected) {
    int pos1 = 3;
    int pos2 = 7;
    int alpha1 =gf.Inverse( gf.Alphapower(n - pos1-1 ));
    int alpha2 = gf.Inverse(gf.Alphapower(n - pos2-1 ));
    // error locator polynomial = (x - α1)(x - α2) = x^2 + (α1 + α2)x + α1*α2
    int sum = gf.Add(alpha1, alpha2);
    int prod = gf.Multiply(alpha1, alpha2);
    std::vector<int> locatorPoly = { prod, sum, 1 };  // degree-2 polynomial
    Chiensearch cs(locatorPoly, m, n);
    std::vector<int> locations = cs.Geterrorlocations();
    EXPECT_EQ(locations[pos1], 1);
   // EXPECT_EQ(locations[pos2], 1);
    int count = std::count(locations.begin(), locations.end(), 1);
    EXPECT_EQ(count, 2);
}

// Test 4: No errors detected with correct locator polynomial of 1 (no roots)
TEST_F(test_Forneyalgorithm, NoErrorsDetectedForAllOnePolynomial) {
    std::vector<int> locatorPoly = {1};
    Chiensearch cs(locatorPoly, m, n);

    std::vector<int> expected(n, 0);
    EXPECT_EQ(cs.Geterrorlocations(), expected);

}
