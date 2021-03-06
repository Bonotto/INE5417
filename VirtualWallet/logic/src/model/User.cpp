//! Copyright [2017] Bruno Bonotto and João Vicente Souto
#include "User.h"

namespace project {

User::User(string _name, string _password, string _code) :
    name(_name),
    password(_password),
    code(_code),
    manager(),
    accounts()
{

}

User::~User() {
    //while (!accounts.empty()) {
    //    delete accounts.front();
    //    accounts.pop_front();
    //}
}

size_t User::getId() {
    return id;
}

string User::getCode() {
    return code;
}

string User::getName() {
    return name;
}

string User::getPassword() {
    return password;
}

Account * User::getAccount(string _accountName) {
    for (Account * account : accounts) {
        if (_accountName == account->getName())
            return account;
    }
    return nullptr;
}

list<Account*> User::getAccounts() {
    return accounts;
}

list<string> User::getReleaseTypesNames() {
    return manager.getReleaseTypes();
}

list<string> User::getPaymentTypesNames() {
    return manager.getPaymentTypes();
}

bool User::verifyUser(std::string _name, std::string _password) {
    return (name == _name && password == _password);
}

void User::changeName(string _newName) {
    name = _newName;
}

void User::changePassword(string _newPassword) {
    password = _newPassword;
}

bool User::insertAccount(Account& _account) {
    if (accountExist(_account.getName()))
        return false;

    accounts.push_front(&_account);
    return true;
}

void User::removeAccount(Account& _account) {
    accounts.remove(&_account);
}

void User::removeAccount(std::string _name) {
    for (list<Account*>::iterator it = accounts.begin(); it != accounts.end(); ++it)
        if (!(*it)->getName().compare(_name)) {
            accounts.remove(*it);
            break;
        }
}

void User::changeAccount(std::string _old, std::string _new)
{
    for (list<Account*>::iterator it = accounts.begin(); it != accounts.end(); ++it)
        if (!(*it)->getName().compare(_old)) {
            (*it)->changeName(_new);
            break;
        }
}

bool User::accountExist(string _name) {
    for (list<Account*>::iterator it = accounts.begin(); it != accounts.end(); it++)
        if (!(*it)->getName().compare(_name))
            return true;

    return false;
}

bool User::insertReleaseType(std::string _type) {
    return manager.addReleaseType(_type);
}

void User::removeReleaseType(std::string _type) {
    manager.deleteReleaseType(_type);
}

bool User::changeReleaseType(std::string _old, std::string _new) {
    return manager.changeReleaseType(_old, _new);
}

}  // namespace project
