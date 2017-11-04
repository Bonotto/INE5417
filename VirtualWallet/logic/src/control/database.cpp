#include "database.h"

using namespace std;

namespace project {

DataBase::DataBase()
{

}

DataBase::~DataBase()
{

}

User * DataBase::getUserByNameAndPass(string _name, string _password)
{
    if (!_name.compare(user->getName()) && !_password.compare(user->getPassword()))
        return user;

    return nullptr;
}

User * DataBase::getUserByCodeAndPass(string _code, string _password)
{
    if (!_code.compare(user->getCode()) && !_password.compare(user->getPassword()))
        return user;

    return nullptr;
}

User * DataBase::getUserByNameAndCode(string _name, string _code)
{
    if (!_code.compare(user->getCode()) && !_name.compare(user->getName()))
        return user;

    return nullptr;
}

void DataBase::put(User * _user)
{
    user = _user;
}

list<Account*> DataBase::getAccounts(int _userId)
{
    return user->getAccounts();
}

list<Wallet*> DataBase::getWallets(int _userId)
{
    list<Wallet*> wallets;
    for (auto & acc : user->getAccounts())
        if (!acc->getType())
            wallets.push_back(static_cast<Wallet*>(acc));
    return wallets;
}

list<BankAccount*> DataBase::getAccounts(int _userId)
{
    list<BankAccount*> banksAcc;
    for (auto & acc : user->getAccounts())
        if (acc->getType())
            banksAcc.push_back(static_cast<BankAccount*>(acc));
    return banksAcc;
}

list<Release*> DataBase::getReleases(int _userId)
{
    list<Release*> releases;
    list<Account*> accounts = user->getAccounts();

    for (auto & acc : accounts)
        for (auto & rel : acc->getReleases())
            releases->push_front(rel);

    return releases;
}

list<ReleaseType*> DataBase::getReleaseTypes(int _userId)
{
    return user->getReleaseTypes();
}

list<string> DataBase::getPaymentTypes(int _userId)
{
    return user->getPaymentTypes();
}

Account * DataBase::getAccount(int _accName, int _userId)
{
    return user->getAccount(_accName);
}

bool DataBase::put(ReleaseType * _type, int _userId)
{
    list<ReleaseType*> types = user->getReleaseTypes();
    for (auto & it: types) {
        if (!it->getName().compare(_type->getName()))
            return false;

        if (it->getId() == _type->getId()) {
            user->removeReleaseType(it);
            break;
        }
    }

    return user->insertReleaseType(_type);
}

void DataBase::removeReleaseType(int _typeId, int _userId)
{
    list<ReleaseType*> types = user->getReleaseTypes();
    for (auto & it: types)
        if (it->getId() == _typeId) {
            removeReleasesByType(it->getName(), _userId);
            user->removeReleaseType(it);
            break;
        }
}

void DataBase::removeReleasesByType(string _type, int _userId)
{
    user->removeReleases(_type);
}

void DataBase::removeRelease(int _relId, in _userId)
{
    list<Account*> accounts = user->getAccounts();
    for (auto & acc : accounts)
        for (auto & rel : acc->getReleases())
            if (rel->getId() == _relId) {
                acc->removeRelease(rel);
                break;
            }
}

bool DataBase::put(Wallet * _account, int _userId)
{
    return user->insertAccount(_account);
}

void DataBase::removeAccount(int _accId, int _userId)
{
    list<Account*> accounts = user->getAccounts();
    for (auto & it: accounts)
        if (it->getId() == _accId) {
            user->removeAccount(it->getName());
            break;
        }
}

bool DataBase::put(BankAccount * _account, int _userId)
{
    return user->insertAccount(_account);
}










}