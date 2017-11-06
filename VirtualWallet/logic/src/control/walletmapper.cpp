#include "walletmapper.h"

namespace project {

WalletMapper::WalletMapper(QSqlDatabase & _conn) :
    conn(_conn)
{

}

WalletMapper::~WalletMapper()
{

}

Wallet * WalletMapper::getById(int _id)
{
    return nullptr;
}

Wallet * WalletMapper::getByName(string _name, int _userId)
{
    return nullptr;
}

list<Wallet*> WalletMapper::getAllWallets(int _userId)
{
    return list<Wallet*>();
}

void WalletMapper::put(Wallet * _wallet)
{

}

void WalletMapper::remove(int _id)
{

}

} // namespace
