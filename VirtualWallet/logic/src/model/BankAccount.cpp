//! Copyright [2017] Bruno Bonotto and João Vicente Souto
#include "BankAccount.h"

namespace project {

BankAccount::BankAccount(int _id, string _name, double _balance, int _userId) :
    Account::Account(_id, _name, _balance, true, _userId)
{
    
}

BankAccount::BankAccount(int _id, string _name, double _balance, string _number, string _agency, string _bank, int _userId) :
    Account::Account(_id, _name, _balance, true, _userId)
{
    agency = _agency;
    accountNumber = _number;
    bank = _bank;
}

BankAccount::~BankAccount()
{
    
}

string BankAccount::getAccountNumber() {
    return accountNumber;
}

string BankAccount::getAgency() {
    return agency;
}

string BankAccount::getBank() {
    return bank;
}

void BankAccount::changeAccountNumber(string _newNumber) {
    accountNumber = _newNumber;
}

void BankAccount::changeAgency(string _newAgency) {
    agency = _newAgency;
}

void BankAccount::changeBank(string _newBank) {
    bank = _newBank;
}

}  // namespace project
