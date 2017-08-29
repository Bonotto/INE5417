//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_WALLET_H
#define PROJECT_WALLET_H

#include "account.h"

using namespace std;

namespace project {

class Wallet : public Account  {
public:
    Wallet(string _name, double _balance);
    ~Wallet();
    
};
    
}  // namespace project

#endif
