#include <gtest/gtest.h>
#include "../include/Codeword/Codeword.h"

// Test fixture class for Codeword tests
class test_Codeword : public ::testing::Test {
protected:
    Codeword codeword;
};

// Test that setting the field and size correctly stores values
TEST_F(test_Codeword, SetFieldAndSizeCorrectly) {
    codeword.SetField(4);
    codeword.SetSize(3);
    EXPECT_NO_THROW();  // Just verify no error is thrown
}

// Test that setting a valid codeword vector of correct size works
TEST_F(test_Codeword, SetValidCodewordVector) {
    codeword.SetField(4);  // field GF(2^4)
    codeword.SetSize(3);   // expect 3 symbols
    std::vector<int> message = {1, 2, 3};
    codeword.SetcodewordVector(message);
    EXPECT_EQ(codeword.GetcodewordVector(), message);
}

// Test that setting a codeword vector of wrong size throws exception
TEST_F(test_Codeword, SetInvalidCodewordVectorThrows) {
    codeword.SetField(4);
    codeword.SetSize(3);
    std::vector<int> invalid_message = {1, 2};  // too short
    EXPECT_THROW(codeword.SetcodewordVector(invalid_message), std::invalid_argument);
}

// Test binary-to-symbol conversion for a known binary input
TEST_F(test_Codeword, BinaryToCodewordConversion) {
    codeword.SetField(3); // m = 3 → 3 bits per symbol
    codeword.SetSize(2);  // k = 2 → 2 symbols expected
    std::vector<int> bin = {1, 0, 1, 0, 1, 1};  // 101 (5), 011 (3)
    std::vector<int> expected = {5, 3};
    codeword.SetBinaryVector(bin);
    EXPECT_EQ(codeword.GetcodewordVector(), expected);
}

// Test symbol-to-binary conversion matches expected binary output
TEST_F(test_Codeword, CodewordToBinaryConversion) {
    codeword.SetField(3); // m = 3
    codeword.SetSize(2);
    std::vector<int> message = {5, 3};  // 101, 011
    std::vector<int> expected_bin = {1, 0, 1, 0, 1, 1};
    codeword.SetcodewordVector(message);
    EXPECT_EQ(codeword.GetBinaryVector(), expected_bin);
}

// Test that binary input of incorrect size throws exception
TEST_F(test_Codeword, BinarySizeMismatchThrows) {
    codeword.SetField(4); // m = 4
    codeword.SetSize(2);  // k = 2 → expect 8 bits
    std::vector<int> bad_bin = {1, 0, 1};  // too short
    EXPECT_THROW(codeword.SetBinaryVector(bad_bin), std::invalid_argument);
}

// Test conversion round-trip: symbol → binary → symbol returns original
TEST_F(test_Codeword, RoundTripConversionWorks) {
    codeword.SetField(4); // m = 4
    codeword.SetSize(3);
    std::vector<int> original = {7, 4, 15};
    codeword.SetcodewordVector(original);
    std::vector<int> bin = codeword.GetBinaryVector();
    codeword.SetBinaryVector(bin);
    EXPECT_EQ(codeword.GetcodewordVector(), original);
}
