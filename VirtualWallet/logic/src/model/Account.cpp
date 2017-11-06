//! Copyright [2017] Bruno Bonotto and João Vicente Souto
#include "Account.h"

namespace project {

Account::Account(int _id, string _name, double _balance, bool _type, int _userId) :
    id(_id),
    balance(_balance),
    type(_type),
    name(_name),
    user_Id(_userId)
{
    
}

Account::~Account() {
    
}

int Account::getId() {
    return id;
}

bool Account::getType() {
    return type;
}

int Account::getUserId() {
    return user_Id;
}

string Account::getName() {
    return name;
}

double Account::getBalance() {
    return balance;
}

void Account::incrementBalance(double _value)
{
    balance += _value;
}

}  // namespace project
