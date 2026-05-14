//
// Created by ziadf on 5/26/2025.
//
#include <gtest/gtest.h>
#include "../include/Decoding/RSdecoder.h"
#include "../include/Codeword/Encodedmessage.h"

// Fixture for RSdecoder tests
class test_RSdecoder : public ::testing::Test {
protected:
    int m = 4;
    int k = 5;
    int n = 7;
    EncodedMessage validEncoded;

    void SetUp() override {
        validEncoded.SetField(m);
        validEncoded.SetSize(n);
        validEncoded.SetcodewordVector({1, 2, 3, 4, 5, 6, 7});
    }
};

// Test 1: Check decoding extracts correct message symbols (first k symbols)
TEST_F(test_RSdecoder, DecodesCorrectMessage) {
    RSdecoder decoder(validEncoded, m, n, k);
    Message decoded = decoder.Getdecodedmessage();
    std::vector<int> expected = {1, 2, 3, 4, 5};  // first k symbols
    EXPECT_EQ(decoded.GetcodewordVector(), expected);
}

// Test 2: Check exception for invalid codeword length
TEST_F(test_RSdecoder, ThrowsIfCodewordWrongSize) {
      // shorter than n
    EXPECT_THROW({
        validEncoded.SetcodewordVector({1, 2, 3});
        RSdecoder decoder(validEncoded, m, n, k);
    }, std::invalid_argument);
}

// Test 3: Check exception when n <= k
TEST_F(test_RSdecoder, ThrowsIfNLessThanOrEqualK) {
    EXPECT_THROW({
        RSdecoder decoder(validEncoded, m, 5, 5);  // n == k
    }, std::invalid_argument);
}

// Test 4: Check exception for invalid m (too small)
TEST_F(test_RSdecoder, ThrowsIfMTooSmall) {
    EXPECT_THROW({
        RSdecoder decoder(validEncoded, 1, n, k);
    }, std::invalid_argument);
}

// Test 5: Check exception for invalid m (too large)
TEST_F(test_RSdecoder, ThrowsIfMTooLarge) {
    EXPECT_THROW({
        RSdecoder decoder(validEncoded, 11, n, k);
    }, std::invalid_argument);
}
