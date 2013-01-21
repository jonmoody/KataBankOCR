#include "katabankocr.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int WIDTH = 3;
const int MAX_DIGITS_IN_ACCOUNT_NUMBER = 9;
const int CHARACTERS_IN_ONE_LINE = 27;
static const string RESOURCES_PATH = "../KataBankOCR/Resources/";

BankAccountReader::BankAccountReader(string file){
    this->BankFile.open(file);
}

BankAccountReader::~BankAccountReader(){
    this->BankFile.close();
}

bool BankAccountReader::IsFileOpen() {
    return this->BankFile.is_open();
}

string BankAccountReader::GetAccountNumber() {
    string line, accountNumber = "";

    for (int x = 1; x <= WIDTH; x++) {
        getline(this->BankFile, line);
        accountNumber += line;
    }

    getline(this->BankFile, line);

    return accountNumber;
}

string BankAccountReader::ReadAllAccounts() {
    string accountsList, accountNumber = "";

    while (this->BankFile.good()) {
        accountNumber = ConvertAccountNumber(GetAccountNumber());
        accountsList += accountNumber + Legible(accountNumber) + '\n';
    }

    return accountsList;
}

string BankAccountReader::ReadEntireFile() {
    string outputText, line = "";

    while (!this->BankFile.eof()) {
        getline(this->BankFile, line);
        outputText += line;
    }

    return outputText;
}

string BankAccountReader::ConvertAccountNumber(string accountNumber) {
    string convertedAccountNumber, digit = "";

    for (int x = 0; x < MAX_DIGITS_IN_ACCOUNT_NUMBER; x++) {
        string top = accountNumber.substr((x * WIDTH), WIDTH);
        string middle = accountNumber.substr((x * WIDTH) + CHARACTERS_IN_ONE_LINE, WIDTH);
        string bottom = accountNumber.substr((x * WIDTH) + (CHARACTERS_IN_ONE_LINE * 2), WIDTH);

        digit = top + middle + bottom;

        convertedAccountNumber += ConvertSingleDigit(digit);
    }
    return convertedAccountNumber;
}

string BankAccountReader::ConvertSingleDigit(string digit) {
    if (digit == string(" _ ") +
                        "| |" +
                        "|_|")
        return "0";
    if (digit == string("   ") +
                        "  |" +
                        "  |")
        return "1";
    if (digit == string(" _ ") +
                        " _|" +
                        "|_ ")
        return "2";
    if (digit == string(" _ ") +
                        " _|" +
                        " _|")
        return "3";
    if (digit == string("   ") +
                        "|_|" +
                        "  |")
        return "4";
    if (digit == string(" _ ") +
                        "|_ " +
                        " _|")
        return "5";
    if (digit == string(" _ ") +
                        "|_ " +
                        "|_|")
        return "6";
    if (digit == string(" _ ") +
                        "  |" +
                        "  |")
        return "7";
    if (digit == string(" _ ") +
                        "|_|" +
                        "|_|")
        return "8";
    if (digit == string(" _ ") +
                        "|_|" +
                        " _|")
        return "9";
    else
        return "?";
}

bool BankAccountReader::IsChecksumValid(string accountNumber) {
    int checksum = 0;
    int max = 9;

    for (int x = 1; x <= max; x++) {
        checksum += x * atoi(accountNumber.substr(max - x, 1).c_str());
    }

    return checksum % 11 == 0;
}

string BankAccountReader::Legible(string accountNumber) {
    int illegibleDigit = accountNumber.find('?');
    if (illegibleDigit != string::npos) {
        return " ILL";
    }
    return "";
}

void BankAccountReader::WriteOutputFile() {
    ofstream outputFile(RESOURCES_PATH + "output.txt");
    string outputText = ReadAllAccounts();

    outputFile << outputText;
    outputFile.close();
}
