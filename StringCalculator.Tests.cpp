#include <gtest/gtest.h>
#include "StringCalculator.h" 

TEST(StringCalculatorTests, ExpectZeroForEmptyInput) {
    int expectedResult = 0;
    const char* input = "";
    int result = AddNumbers(input);
    ASSERT_EQ(result, expectedResult);
}

TEST(StringCalculatorTests, ExpectZeroForSingleZero) {
    int expectedResult = 0;
    const char* input = "0";
    int result = AddNumbers(input);
    ASSERT_EQ(result, expectedResult);
}


TEST(StringCalculatorTests, ExpectSumForTwoNumbers) {
    int expectedResult = 3;
    const char* input = "1,2";
    int result = AddNumbers(input);
    ASSERT_EQ(result, expectedResult);
}


TEST(StringCalculatorTests, ExpectSumWithNewlineDelimiter) {
    int expectedResult = 6;
    const char* input = "1\n2,3";
    int result = AddNumbers(input);
    ASSERT_EQ(result, expectedResult);
}


TEST(StringCalculatorTests, IgnoreNumbersGreaterThan1000) {
    int expectedResult = 1;
    const char* input = "1,1001";
    int result = AddNumbers(input);
    ASSERT_EQ(result, expectedResult);
}


TEST(StringCalculatorTests, ExpectSumWithCustomDelimiter) {
    int expectedResult = 3;
    const char* input = "//;\n1;2";
    int result = AddNumbers(input);
    ASSERT_EQ(result, expectedResult);
}


TEST(StringCalculatorTests, ExpectErrorForNegativeNumbers) {
    const char* input = "1,-2,3";
    ASSERT_DEATH(AddNumbers(input), "Error: Negative numbers are not allowed");
}

