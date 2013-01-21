#include "../Source/katabankocr.h"
#include "../gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <string>

static const string RESOURCES_PATH = "../KataBankOCR/Resources/";

TEST(BankAccountReader, TestOpenFile) {
    bool expected = true;

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.IsFileOpen());
}

TEST(BankAccountReader, TestReadFile) {
    string expected = string("    _  _     _  _  _  _  _ ")
                           + "  | _| _||_||_ |_   ||_||_|"
                           + "  ||_  _|  | _||_|  ||_| _|";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.GetAccountNumber());
}

TEST(BankAccountReader, TestReadAllAccounts) {
    string expected = string("000000000\n") +
                        "111111111\n" +
                        "222222222\n" +
                        "333333333\n" +
                        "444444444\n" +
                        "555555555\n" +
                        "666666666\n" +
                        "777777777\n" +
                        "888888888\n" +
                        "999999999\n" +
                        "123456789\n";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "useCase1.txt");

    ASSERT_EQ(expected, bankAccountReader.ReadAllAccounts());
}

TEST(BankAccountReader, TestAccountNumberConversion) {
    string expected = "123456789";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    string accountNumber = bankAccountReader.GetAccountNumber();
    string convertedAccountNumber = bankAccountReader.ConvertAccountNumber(accountNumber);

    ASSERT_EQ(expected, convertedAccountNumber);
}

TEST(BankAccountReader, TestConvertZero) {
    string digit = string(" _ ") +
                          "| |" +
                          "|_|";

    string expected = "0";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertOne) {
    string digit = string("   ") +
                          "  |" +
                          "  |";

    string expected = "1";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertTwo) {
    string digit = string(" _ ") +
                          " _|" +
                          "|_ ";

    string expected = "2";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertThree) {
    string digit = string(" _ ") +
                          " _|" +
                          " _|";

    string expected = "3";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertFour) {
    string digit = string("   ") +
                          "|_|" +
                          "  |";

    string expected = "4";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertFive) {
    string digit = string(" _ ") +
                          "|_ " +
                          " _|";

    string expected = "5";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertSix) {
    string digit = string(" _ ") +
                          "|_ " +
                          "|_|";

    string expected = "6";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertSeven) {
    string digit = string(" _ ") +
                          "  |" +
                          "  |";

    string expected = "7";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertEight) {
    string digit = string(" _ ") +
                          "|_|" +
                          "|_|";

    string expected = "8";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertNine) {
    string digit = string(" _ ") +
                          "|_|" +
                          " _|";

    string expected = "9";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestConvertUnknownNumber) {
    string digit = string(" _ ") +
                          "| |" +
                          " _|";

    string expected = "?";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "123456789.txt");

    ASSERT_EQ(expected, bankAccountReader.ConvertSingleDigit(digit));
}

TEST(BankAccountReader, TestValidChecksum) {
    bool expected = true;

    BankAccountReader bankAccountReader(RESOURCES_PATH + "000000051.txt");

    string accountNumber = bankAccountReader.GetAccountNumber();
    string convertedAccountNumber = bankAccountReader.ConvertAccountNumber(accountNumber);

    ASSERT_EQ(expected, bankAccountReader.IsChecksumValid(convertedAccountNumber));
}

TEST(BankAccountReader, TestInvalidChecksum) {
    bool expected = false;

    BankAccountReader bankAccountReader(RESOURCES_PATH + "000000001.txt");

    string accountNumber = bankAccountReader.GetAccountNumber();
    string convertedAccountNumber = bankAccountReader.ConvertAccountNumber(accountNumber);

    ASSERT_EQ(expected, bankAccountReader.IsChecksumValid(convertedAccountNumber));
}

TEST(BankAccountReader, TestWritingOutputFile) {
    string expected = string("000000051") +
                        "49006771? ILL" +
                        "1234?678? ILL";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "useCase3.txt");

    bankAccountReader.WriteOutputFile();

    BankAccountReader bankAccountReaderOutput(RESOURCES_PATH + "output.txt");

    ASSERT_EQ(expected, bankAccountReaderOutput.ReadEntireFile());
}

TEST(BankAccountReader, TestLegibleDigits) {
    string expected = " ILL";

    BankAccountReader bankAccountReader(RESOURCES_PATH + "broken.txt");

    string accountNumber = bankAccountReader.GetAccountNumber();
    string convertedAccountNumber = bankAccountReader.ConvertAccountNumber(accountNumber);

    ASSERT_EQ(expected, bankAccountReader.Legible(convertedAccountNumber));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
