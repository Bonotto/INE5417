#ifndef BANKACCOUNTMAPPER_H
#define BANKACCOUNTMAPPER_H

#include <QDebug>
#include <QDir>
#include <QtSql>
#include <QSqlDriver>
#include <qsqldatabase.h>
#include <QSqlError>
#include <QPluginLoader>

#include <string>
#include <list>

#include "src/model/BankAccount.h"

namespace project {

class BankAccountMapper
{
public:
    BankAccountMapper(QSqlDatabase & _conn);
    ~BankAccountMapper();

    BankAccount * getById(int _id);
    BankAccount * getByName(string _name, int _userId);
    list<BankAccount*> getAllBankAccounts(int _userId);

    void put(BankAccount * _bankAccount);
    void remove(int _id);

private:
    QSqlDatabase & conn;
};

} // namespace

#endif // BANKACCOUNTMAPPER_H
