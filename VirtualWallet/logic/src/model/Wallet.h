//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_WALLET_H
#define PROJECT_WALLET_H

#include "Account.h"

using namespace std;

namespace project {

class Wallet : public Account  {
public:
    Wallet(int _Id, string _name, double _balance, int _userId);
    ~Wallet();
    
};
    
}  // namespace project

#endif
