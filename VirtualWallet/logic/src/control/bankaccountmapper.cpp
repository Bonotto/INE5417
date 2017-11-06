#include "bankaccountmapper.h"

namespace project {

BankAccountMapper::BankAccountMapper(QSqlDatabase & _conn) :
    conn(_conn)
{

}

BankAccountMapper::~BankAccountMapper()
{

}

BankAccount * BankAccountMapper::getById(int _id)
{
    return nullptr;
}

BankAccount * BankAccountMapper::getByName(string name, int _userId)
{
    return nullptr;
}

list<BankAccount*> BankAccountMapper::getAllBankAccounts(int _userId)
{
    return list<BankAccount*>();
}

void BankAccountMapper::put(BankAccount * _bankAccount)
{

}

void BankAccountMapper::remove(int _id)
{

}

} // namespace
