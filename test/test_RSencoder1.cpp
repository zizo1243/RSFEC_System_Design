//
// Created by ziadf on 5/28/2025.
//
#include <gtest/gtest.h>
#include "../include/Encoding/RSencoder.h"
#include "../include/Codeword/Message.h"
#include "../include/Codeword/Generatorpolynomial.h"

// Sample fixture for RSencoder
class test_RSencoder1 : public ::testing::Test {
public:

};

// Test correct encoding
TEST_F(test_RSencoder1, EncodeWorksCorrectly) {
    int m = 4;
    int k = 5;
    int n = 7;
    vector<int> sample_message = {1, 2, 3, 4, 5};
    vector<int> generator = {1, 2, 3}; // Degree = n - k = 2
    Message message;
    message.SetField(m);
    message.SetSize(k);
    message.SetcodewordVector(sample_message);
    Generatorpolynomial gp = Generatorpolynomial(generator, m, n, k);

    Rsencoder encoder(m, n, k, message, gp);
    EncodedMessage encoded = encoder.GetEncodedMessage();

    EXPECT_EQ(encoded.GetcodewordVector().size(), n);

    vector<int> codeword = encoded.GetcodewordVector();
    EXPECT_EQ(codeword.size(), n);

    for (int i = 0; i < k; ++i) {
        EXPECT_EQ(codeword[i], sample_message[i]) << "Message symbol mismatch at index " << i;
    }
}

// Test error on incorrect message size
TEST_F(test_RSencoder1, ThrowsIfMessageWrongSize) {

        int m = 4;
        int k = 5;
        int n = 7;
        vector<int> sample_message = {1, 2, 3, 4, 5};
        vector<int> generator = {1, 2, 3}; // Degree = n - k = 2

        EXPECT_THROW({
            Message message;
            message.SetField(m);
            message.SetSize(k);
            message.SetcodewordVector({1, 2}); // shorter than k — will throw here

            Generatorpolynomial gp(generator, m, n, k);
            Rsencoder encoder(m, n, k, message, gp);  // this won't be reached
        }, std::invalid_argument);
    }



// Test error if n < k
TEST_F(test_RSencoder1, ThrowsIfNLessThanK) {
    int m = 4;
    int k = 5;
    int n = 7;
    vector<int> sample_message = {1, 2, 3, 4, 5};
    vector<int> generator = {1, 2, 3}; // Degree = n - k = 2
    Message message;
    message.SetField(m);
    message.SetSize(k);
    message.SetcodewordVector(sample_message);
    Generatorpolynomial gp = Generatorpolynomial(generator, m, n, k);

    EXPECT_THROW({
        Rsencoder encoder(m, 4, 5, message, gp); // n < k
    }, std::invalid_argument);
}

// Test if parity size = n - k
TEST_F(test_RSencoder1, ParitySizeIsCorrect) {
    int m = 4;
    int k = 5;
    int n = 7;
    vector<int> sample_message = {1, 2, 3, 4, 5};
    vector<int> generator = {1, 2, 3}; // Degree = n - k = 2
    Message message;
    message.SetField(m);
    message.SetSize(k);
    message.SetcodewordVector(sample_message);
    Generatorpolynomial gp = Generatorpolynomial(generator, m, n, k);

    Rsencoder encoder(m, n, k, message, gp);
    vector<int> parity = encoder.Getparity();
    EXPECT_EQ(parity.size(), n - k);
}
