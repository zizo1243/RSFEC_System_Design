#include <gtest/gtest.h>
#include "../include/Decoding//KeyequationEEA.h"  // Adjust path as needed

class test_KeyequationEEA : public ::testing::Test {
protected:
    int m = 4;
    int n = 7;
    int k = 3;
    GF2mAlpha gf = GF2mAlpha(m);
};

// Test that with zero syndrome, both polynomials are zero vectors
TEST_F(test_KeyequationEEA, ZeroSyndromeReturnsZeroPolynomials) {
    std::vector<int> zeroSyndrome(n - k, 0);
    KeyequationEEA keea(zeroSyndrome, m, n, k);

    auto errorLocator = keea.Geterrorlocatorpolynomial();
    auto errorEvaluator = keea.Geterrorevaluatorpolynomial();

    // Both polynomials should be {0}
    ASSERT_EQ(errorLocator.size(), 1);
    ASSERT_EQ(errorLocator[0],0);

    ASSERT_EQ(errorEvaluator.size(), 1);
    ASSERT_EQ(errorEvaluator[0], 0);
}

// Test that the class computes polynomials of expected sizes for a non-zero syndrome
TEST_F(test_KeyequationEEA, ComputesPolynomialsForNonZeroSyndrome) {
    // Example syndrome with some non-zero values
    std::vector<int> syndrome = {1, 0, 3, 5};

    KeyequationEEA keea(syndrome, m, n, k);

    auto errorLocator = keea.Geterrorlocatorpolynomial();
    auto errorEvaluator = keea.Geterrorevaluatorpolynomial();

    // Error locator polynomial degree <= t (where t = (n-k)/2)
    int t = (n - k) / 2;
    EXPECT_LE(static_cast<int>(errorLocator.size()), t + 1);
    EXPECT_LE(static_cast<int>(errorEvaluator.size()), t + 1);

    // Leading coefficient of error locator polynomial should be 1 (normalized)
    EXPECT_EQ(errorLocator.back(), 1);

    // Error evaluator polynomial should not be all zeros if syndrome non-zero
    bool nonZeroEvaluator = false;
    for (auto c : errorEvaluator) {
        if (c != 0) {
            nonZeroEvaluator = true;
            break;
        }
    }
    EXPECT_TRUE(nonZeroEvaluator);
}

// Test that invalid syndrome vector size throws an exception (optional based on your code)


// Test that polynomials are normalized (leading coefficient == 1)
TEST_F(test_KeyequationEEA, PolynomialsAreNormalized) {
    std::vector<int> syndrome = {3, 6, 0, 4};
    KeyequationEEA keea(syndrome, m, n, k);

    auto errorLocator = keea.Geterrorlocatorpolynomial();
    auto errorEvaluator = keea.Geterrorevaluatorpolynomial();

    // Leading coefficient of error locator polynomial should be 1
    EXPECT_EQ(errorLocator.back(), 1);

    // Leading coefficient of error evaluator polynomial should be normalized as well
    // You can check division by substitute at 0 in your code normalizes properly
    int leadingEvaluator = errorEvaluator.back();
    EXPECT_NE(leadingEvaluator, 0);
}

// You can add more tests for corner cases, large polynomials, or randomized input

