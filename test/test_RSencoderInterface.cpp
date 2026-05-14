//
// Created by ziadf on 5/25/2025.
//
#include<gtest/gtest.h>
#include "../include/Encoding/RSencoderInterface.h"
#include "../include/Codeword/Generatorpolynomial.h"
#include"../include/Galios Field operations/GF2mAlpha.h"
// Sample test fixture to reuse common setup
class test_RSencoderInterface : public ::testing::Test {
protected:
    int m = 4;
    int n = 15;
    int k = 11;
    Generatorpolynomial gp = Generatorpolynomial({1, 2, 4, 8, 3}, m, n, k);

};

// ✅ Test 1: Valid encoding
TEST_F(test_RSencoderInterface, EncodesSingleCodewordCorrectly) {

    std::vector<int> message = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 1};
    RSencoderInterface encoder(m, n, k, message, gp);
    EncodedMessage encoded = encoder.Getencodedmessage();
    EXPECT_EQ(encoded.GetcodewordVector().size(), n);
}

// ✅ Test 2: Invalid message size throws
TEST_F(test_RSencoderInterface, MessageSizeNotMultipleOfKThrows) {
    std::vector<int> message = {1, 2, 3}; // Invalid size
    EXPECT_THROW({
        RSencoderInterface encoder(m, n, k, message, gp);
    }, std::invalid_argument);
}

// ✅ Test 3: Field correction applies to out-of-field symbols
TEST_F(test_RSencoderInterface, OutOfFieldSymbolsAreCorrected) {
    std::vector<int> message = {1, 2, 18, 19, 5, 6, 7, 8, 9, 10, 11}; // 18 and 19 > 15 (GF(2^4))
    RSencoderInterface encoder(m, n, k, message, gp);
    EncodedMessage encoded = encoder.Getencodedmessage();
    GF2mAlpha field(m);
    for (int symbol : encoded.GetcodewordVector()) {
        EXPECT_GE(symbol, 0);
        EXPECT_LT(symbol,field.Getfieldsize()); // GF(2^4)
    }
}

// ✅ Test 4: Multiple codewords
TEST_F(test_RSencoderInterface, EncodesMultipleCodewordsCorrectly) {
    std::vector<int> message;
    for (int i = 0; i < 2 * k; ++i) {
        message.push_back(i % 16);
    }
    RSencoderInterface encoder(m, n, k, message, gp);
    EncodedMessage encoded = encoder.Getencodedmessage();
    EXPECT_EQ(encoded.GetcodewordVector().size(), 2 * n);
}
