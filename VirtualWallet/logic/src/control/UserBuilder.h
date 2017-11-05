//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_CONTROL_USER_CREATOR_H
#define PROJECT_CONTROL_USER_CREATOR_H

#include <string>
#include <stdexcept>
#include "../model/User.h"

namespace project {

class UserBuilder {
public:
    UserBuilder(int _id, std::string _name, std::string _code, std::string _password, std::string _confirm);
    ~UserBuilder();

    bool isValid();
    User* build();

private:
    int id;
    std::string name, code, password, confirm;

};

}  // namespace project

#endif
