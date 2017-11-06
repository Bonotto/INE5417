//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_CONTROL_WALLET_CREATOR_H
#define PROJECT_CONTROL_WALLET_CREATOR_H

#include <string>
#include <stdexcept>

#include "../model/Wallet.h"

namespace project {

class WalletBuilder {
public:
    WalletBuilder(int _id, std::string _name, double _balance, int _userId);
    ~WalletBuilder();

    bool isValid();
    Wallet * build();

private:
    int id, userId;
    double balance;
    std::string name;

};

}  // namespace project

#endif
