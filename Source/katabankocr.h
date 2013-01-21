#ifndef KATABANKOCR_H
#define KATABANKOCR_H

#include <string>
#include <fstream>
using namespace std;

class BankAccountReader
{
    private:
        ifstream BankFile;
    public:
        BankAccountReader(string file);
        ~BankAccountReader();
        bool IsFileOpen();
        string GetAccountNumber();
        string ReadAllAccounts();
        string ReadEntireFile();
        string ConvertAccountNumber(string accountNumber);
        string ConvertSingleDigit(string digit);
        bool IsChecksumValid(string accountNumber);
        string Legible(string accountNumber);
        void WriteOutputFile();
};

#endif // KATABANKOCR_H
