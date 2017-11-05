//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_USER_H
#define PROJECT_USER_H

#include <string>
#include <list>
#include "Account.h"
#include "releasetype.h"

using namespace std;

namespace project {

class User {
public:
    User(int _id, string _name, string _password, string _code);
    ~User();

    int getId();
    string getCode();
    string getName();
    string getPassword();

    void setId(int _id);

    bool verifyUser(std::string _name, std::string _password);
    bool verifyCodePass(std::string _code, std::string _password);
    bool verifyNameCode(std::string _name, std::string _code);

    void changeName(string _newName);
    void changePassword(string _newPassword);

private:
    int id;
    string name, password, code;
};

}  // namespace project

#endif
