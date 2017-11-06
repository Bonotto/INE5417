#include "Facade.h"
#include <iostream>

using namespace std;

namespace project {

Facade::Facade() :
    currentUser(nullptr),
    bd(new DataBase())
{
    paymentTypes.push_front("Dinheiro");
    paymentTypes.push_front("Crédito");
    paymentTypes.push_front("Débito");
    paymentTypes.push_front("Cheque");
    paymentTypes.push_front("Outros");
}

Facade::~Facade()
{

}

int Facade::getCurrentId()
{
    return currentUser->getId();
}

bool Facade::registerUser(std::string _name, std::string _code, std::string _password, std::string _confirm)
{
    User * _user = bd->getUserByName(_name);
    if (_user != nullptr) {
        delete _user;
        return false;
    }

    UserBuilder builder(-1, _name, _code, _password, _confirm);

    if (!builder.isValid())
        return false;

    bd->put(builder.build());
    return true;
}

bool Facade::login(std::string _name, std::string _password)
{
    User * _user = bd->getUserByNameAndPass(_name, _password);

    return (currentUser = _user) != nullptr;
}

bool Facade::refreshName(std::string _code, std::string _password, std::string _newName, std::string _confirm) {

    User * _user = bd->getUserByCodeAndPass(_code, _password);

    if (_user == nullptr)
        return false;

    if (_confirm.compare(_newName))
        return false;

    bd->put(new User(_user->getId(), _newName, _password, _code));
    delete currentUser;
    currentUser = _user;

    return true;
}

bool Facade::refreshPass(std::string _name, std::string _code, std::string _newPass, std::string _confirm) {

    User * _user = bd->getUserByNameAndCode(_name, _code);

    if (_user == nullptr)
        return false;

    if (_confirm.compare(_newPass))
        return false;

    bd->put(new User(_user->getId(), _name, _newPass, _code));
    delete currentUser;
    currentUser = _user;

    return true;
}

list<Account*> Facade::userAccounts()
{
    return bd->getAccounts(currentUser->getId());
}

list<Wallet*> Facade::userWallets()
{
    return bd->getWallets(currentUser->getId());
}

list<BankAccount*> Facade::userBankAccounts()
{
    return bd->getBankAccounts(currentUser->getId());
}

list<Release*> Facade::userReleases()
{
    return bd->getReleases(currentUser->getId());
}

list<ReleaseType*> Facade::userReleaseTypes()
{
    return bd->getReleaseTypes(currentUser->getId());
}

list<string> Facade::userPaymentTypes()
{
    return paymentTypes;
}

bool Facade::registerReleaseType(std::string _name, int _typeId)
{
    bool exist = false;
    for (auto & it : bd->getReleaseTypes(currentUser->getId())) {
        if (it->getName() == _name)
            exist = true;

        delete it;
    }

    if (exist)
        return false;

    ReleaseTypeBuilder builder(_name, _typeId, currentUser->getId());

    if (!builder.isValid())
        return false;

    bd->put(builder.build());
    return true;
}

void Facade::deleteReleaseType(int _typeId)
{
    bd->removeReleaseType(_typeId, currentUser->getId());
}

bool Facade::registerWallet(std::string _name, double _balance, int _accId)
{
    Account * account = bd->getAccount(_name, currentUser->getId());

    if (account != nullptr) {
        delete account;
        return false;
    }

    WalletBuilder builder(_accId, _name, _balance);

    if (!builder.isValid())
        return false;

    bd->put(builder.build());
    return true;
}

void Facade::deleteAccount(int _accId)
{
    bd->removeAccount(_accId);
}

bool Facade::registerBankAccount(int _accId, std::string _name, double _balance, std::string _accountNumber, std::string _agency, std::string _bank)
{
    Account * account = bd->getAccount(_name, currentUser->getId());

    if (account != nullptr) {
        delete account;
        return false;
    }
    BankAccountBuilder builder(_accId, _name, _balance, _accountNumber, _agency, _bank);

    if (!builder.isValid())
        return false;

    bd->put(builder.build());
    return true;
}

bool Facade::registerRelease(int _relId, double _value, std::string _accountName, std::string _releaseT, std::string _paymentT,
                     std::string _description, std::string _op, std::string _date)
{
    Account * account = nullptr;
    for (auto & acc : bd->getAccounts(currentUser->getId()))
        if (acc->getName() == _accountName) {
            account = acc;
            break;
        }

    ReleaseType * releaseT = nullptr;
    for (auto rel : bd->getReleaseTypes(currentUser->getId()))
        if (rel->getName() == _releaseT) {
            releaseT = rel;
            break;
        }

    if (_op == "out")
        _value = - _value;

    ReleaseBuilder builder(_relId, _value, account, releaseT, _paymentT, _description, _op, _date);

    if (!builder.isValid())
        return false;

    bd->put(builder.build());
    return true;
}

void Facade::deleteRelease(int _id)
{
    bd->removeRelease(_id);
}

Report * Facade::createReport(list<int> accountIds, list<int> releaseTypeIds, list<string> paymentTypes,
                      string begin, string end, double lower, double upper, bool in, bool out)
{
    list<Account*> accounts;
    for (auto & acc : bd->getAccounts(currentUser->getId()))
        for (auto & accId : accountIds)
            if (acc->getId() == accId) {
                accounts.push_back(acc);
                break;
            }

    list<ReleaseType*> releaseTypes;
    for (auto & relT : bd->getReleaseTypes(currentUser->getId()))
        for (auto & relTId : releaseTypeIds)
            if (relT->getId() == relTId) {
                releaseTypes.push_back(relT);
                break;
            }

    ReportBuilder builder(accounts, releaseTypes, paymentTypes, begin, end, lower, upper, in, out);

    if (!builder.isValid())
        return nullptr;

    return builder.build();
}

double Facade::accountsBalance()
{
    double totalBalance = 0.0;

    for (auto i : userAccounts())
        totalBalance += i->getBalance();

    return totalBalance;
}

std::string Facade::getUserName()
{
    return bd->getUser(currentUser->getId())->getName();
}

}
