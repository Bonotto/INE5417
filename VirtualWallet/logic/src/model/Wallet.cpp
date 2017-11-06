//! Copyright [2017] Bruno Bonotto and João Vicente Souto
#include "Wallet.h"

namespace project {

Wallet::Wallet(int _id, string _name, double _balance, int _userId) :
    Account::Account(_id, _name, _balance, false, _userId)
{
    
}

Wallet::~Wallet()
{
    
}

}  // namespace project
