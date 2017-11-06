//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_ACCOUNT_H
#define PROJECT_ACCOUNT_H

#include <string>
#include <list>
#include "Release.h"

using namespace std;

namespace project {

class Account {
public:
    Account(int _id, string _name, double _balance, bool _type, int _user_Id);
    virtual ~Account();

    int getId();
    bool getType();
    int getUserId();
    string getName();
    double getBalance();

    void incrementBalance(double _value);
    
private:
    int id, user_Id;
    bool type;
    double balance{0.0};
    string name;
    
};
    
}  // namespace project

#endif
