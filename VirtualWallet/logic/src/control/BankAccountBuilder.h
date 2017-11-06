//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_CONTROL_BANK_ACCOUNT_CREATOR_H
#define PROJECT_CONTROL_BANK_ACCOUNT_CREATOR_H

#include <string>
#include <stdexcept>

#include "../model/BankAccount.h"

namespace project {

class BankAccountBuilder {
public:
    BankAccountBuilder(int _id, std::string _name, double _balance, std::string _accountNumber, std::string _agency, std::string _bank, int _userId);
    ~BankAccountBuilder();

    bool isValid();
    BankAccount* build();

private:
    int id, userId;
    double balance;
    std::string name, accountNumber, agency, bank;

};

}  // namespace project

#endif
