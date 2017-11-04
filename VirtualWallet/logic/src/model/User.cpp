//! Copyright [2017] Bruno Bonotto and João Vicente Souto
#include "User.h"

namespace project {

User::User(string _name, string _password, string _code) :
    name(_name),
    password(_password),
    code(_code),
    accounts(),
    releaseTypes()
{
    paymentTypes.push_front("Dinheiro");
    paymentTypes.push_front("Crédito");
    paymentTypes.push_front("Débito");
    paymentTypes.push_front("Cheque");
    paymentTypes.push_front("Outros");

    releaseTypes.push_front(new ReleaseType("Água", 1));
    releaseTypes.push_front(new ReleaseType("Energia", 2));
    releaseTypes.push_front(new ReleaseType("Internet", 3));
    releaseTypes.push_front(new ReleaseType("Transporte", 4));
    releaseTypes.push_front(new ReleaseType("Alimentação", 5));
}

User::~User() {

}

int User::getId() {
    return id;
}

string User::getCode() {
    return code;
}

string User::getName() {
    return name;
}

string User::getPassword()
{
    return password;
}

Account * User::getAccount(string _accountName)
{
    for (Account * account : accounts) {
        if (_accountName == account->getName())
            return account;
    }
    return nullptr;
}

list<Account*> User::getAccounts()
{
    return accounts;
}

list<ReleaseType*> User::getReleaseTypes()
{
    return releaseTypes;
}

bool User::verifyUser(std::string _name, std::string _password)
{
    return (name == _name && password == _password);
}

void User::changeName(string _newName)
{
    name = _newName;
}

void User::changePassword(string _newPassword)
{
    password = _newPassword;
}

bool User::insertAccount(Account * _account)
{
    if (accountExist(_account->getName()))
        return false;

    accounts.push_front(_account);
    return true;
}

void User::removeAccount(Account * _account)
{
    accounts.remove(_account);
}

void User::removeAccount(std::string _name)
{
    for (auto & it : accounts)
        if (!it->getName().compare(_name)) {
            accounts.remove(it);
            break;
        }
}

void User::changeAccount(std::string _old, std::string _new)
{
    for (auto & it : accounts)
        if (!it->getName().compare(_old)) {
            it->changeName(_new);
            break;
        }
}

bool User::accountExist(string _name)
{
    for (auto & it : accounts)
        if (!it->getName().compare(_name))
            return true;

    return false;
}

bool User::insertReleaseType(ReleaseType * _type)
{
    return releaseTypes.push_front(_type);
}

void User::removeReleaseType(ReleaseType * _type)
{
    releaseTypes.remove(_type);
}

void User::removeReleases(ReleaseType * _type)
{
    for (auto & i: accounts)
        for (auto & j : i->getReleases())
            if (!j->getReleaseType().compare(_type->getName())) {
                i->removeRelease(j);
                delete j;
            }
}

}  // namespace project
