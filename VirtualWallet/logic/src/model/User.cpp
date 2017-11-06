//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#include "User.h"

namespace project {

User::User(int _id, string _name, string _password, string _code) :
    id(_id),
    name(_name),
    password(_password),
    code(_code)
{
   /*releaseTypes.push_front(new ReleaseType("Água", 1));
    releaseTypes.push_front(new ReleaseType("Energia", 2));
    releaseTypes.push_front(new ReleaseType("Internet", 3));
    releaseTypes.push_front(new ReleaseType("Transporte", 4));
    releaseTypes.push_front(new ReleaseType("Alimentação", 5));*/
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

void User::setId(int _id)
{
    id = _id;
}

bool User::verifyUser(std::string _name, std::string _password)
{
    return (name == _name && password == _password);
}

bool User::verifyCodePass(std::string _code, std::string _password)
{
    return (code == _code && password == _password);
}

bool User::verifyNameCode(std::string _name, std::string _code)
{
    return (name == _name && code == _code);
}

void User::changeName(string _newName)
{
    name = _newName;
}

void User::changePassword(string _newPassword)
{
    password = _newPassword;
}

}  // namespace project
