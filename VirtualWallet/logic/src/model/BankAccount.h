//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_BANK_ACCOUNT_H
#define PROJECT_BANK_ACCOUNT_H

#include "Account.h"

using namespace std;

namespace project {

class BankAccount : public Account {
public:
    BankAccount(int _id, string _name, double _balance, int _userId);
    BankAccount(int _id, string _name, double _balance, string _number, string _agency, string _bank, int _userId);
    ~BankAccount();
    
    string getAccountNumber();
    string getAgency();
    string getBank();
    
    void changeAccountNumber(string _newNumber);
    void changeAgency(string _newAgency);
    void changeBank(string _newBank);
    
private:
    string accountNumber, agency, bank;
};

}  // namespace project

#endif
