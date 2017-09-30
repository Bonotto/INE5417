//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

#include <string>
#include <list>
#include "Account.h"
#include "TypeManager.h"

using namespace std;

namespace project {

class User {
public:
    User(string _name, string _password, string _code);
    ~User();

    size_t getId();
    string getCode();
    string getName();
    string getPassword();
    list<Account*> getAccounts();

    bool verifyUser(std::string _name, std::string _password);

    void changeName(string _newName);
    void changePassword(string _newPassword);
    void insertAccount(Account& _account);
    void removeAccount(Account& _account);

private:
    size_t id{0};
    string name, password, code;
    TypeManager manager;
    list<Account*> accounts;

};

}  // namespace project

#endif
