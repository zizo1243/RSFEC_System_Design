//
// Created by ziadf on 5/26/2025.
//
#include <gtest/gtest.h>
#include "../include/Decoding/Syndrome.h"  // Adjust path as needed

class test_Syndrome : public ::testing::Test {
protected:
    int m = 4;       // GF(2^4)
    int n = 7;       // Codeword length
    int k = 3;       // Message length (k < n)
    GF2mAlpha gf = GF2mAlpha(m);
};

// Test that syndrome is correctly calculated for a valid received codeword
TEST_F(test_Syndrome, CalculatesSyndromeCorrectly) {
    // Example received codeword of size n with elements in GF(2^m)
    std::vector<int> received = {1, 2, 3, 4, 5, 6, 7};

    Syndrome syndrome(received, m, n, k);
    std::vector<int> calculated = syndrome.Getsyndrome();

    // Syndrome size should be n - k
    ASSERT_EQ(calculated.size(), n - k);

    // Test values against direct computation for verification (manual or via gf)
    for (int i = 0; i < n - k; ++i) {
        int expected = 0;
        int power = gf.Alphapower(i);
        expected = gf.Subsituteinequation(received, power);
        EXPECT_EQ(calculated[i], expected);
    }
}

// Test that constructor throws if received codeword size is not equal to n
TEST_F(test_Syndrome, ThrowsIfReceivedSizeNotN) {
    std::vector<int> badSize = {1, 2, 3};  // Smaller than n
    EXPECT_THROW(Syndrome syndrome(badSize, m, n, k), std::invalid_argument);
}

// Test that constructor throws if n < k
TEST_F(test_Syndrome, ThrowsIfNLessThanK) {
    std::vector<int> received(n, 1);
    EXPECT_THROW(Syndrome syndrome(received, m, 3, 4), std::invalid_argument);  // n=3, k=4 invalid
}

// Test syndrome vector is properly set and retrieved
TEST_F(test_Syndrome, SetsAndGetsSyndromeVector) {
    std::vector<int> received = {1, 0, 0, 0, 0, 0, 0};
    Syndrome syndrome(received, m, n, k);
    std::vector<int> s = syndrome.Getsyndrome();

    syndrome.Setsyndrome({9, 8, 7, 6});
    EXPECT_EQ(syndrome.Getsyndrome(), (std::vector<int>{9,8,7,6}));
}
