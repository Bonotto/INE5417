//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_CONTROL_FACADE_H
#define PROJECT_CONTROL_FACADE_H

#include <list>
#include <string>
#include "database.h"
#include "../model/User.h"
#include "../model/Wallet.h"
#include "./src/model/Account.h"
#include "WalletBuilder.h"
#include "BankAccountBuilder.h"
#include "ReleaseTypeBuilder.h"
#include "UserBuilder.h"
#include "ReleaseBuilder.h"
#include "ReportBuilder.h"

namespace project {

class Facade {
public:
    Facade();
    ~Facade();

    bool existUser();

    bool registerUser(std::string _name,std::string _code, std::string _password, std::string _confirm);
    bool login(std::string _name, std::string _password);
    bool refreshName(std::string _code, std::string _password, std::string _newName, std::string _confirm);
    bool refreshPass(std::string _name, std::string _code, std::string _newPass, std::string _confirm);

    list<Account*> userAccounts();
    list<Wallet*> userWallets();
    list<BankAccount*> userBankAccounts();
    list<Release*> userReleases();
    list<ReleaseType*> userReleaseTypes();
    list<string> userPaymentTypes();

    bool registerReleaseType(std::string _name, int _typeId);
    void deleteReleaseType(int _typeId);

    bool registerWallet(std::string _name, double _balance, int _accId);
    void deleteAccount(int _accId);

    bool registerBankAccount(int _accId, std::string _name, double _balance, std::string _accountNumber, std::string _agency, std::string _bank);
    bool registerRelease(int _relId, double _value, std::string _accountName, std::string _releaseT, std::string _paymentT,
                         std::string _description, std::string _op, std::string _date);

    void deleteRelease(int _id);

    Report * createReport(list<int> accountIds, list<int> releaseTypeIds, list<string> paymentTypes,
                          string begin, string end, double lower, double upper, bool in, bool out);

    double accountsBalance();
    std::string getUserName();

private:
    list<string> paymentTypes;
    User * currentUser;
    DataBase * bd;
};
    
}  // namespace project

#endif
