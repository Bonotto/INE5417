#ifndef WALLETMAPPER_H
#define WALLETMAPPER_H

#include <QDebug>
#include <QDir>
#include <QtSql>
#include <QSqlDriver>
#include <qsqldatabase.h>
#include <QSqlError>
#include <QPluginLoader>

#include <string>
#include <list>

#include "src/model/Wallet.h"

namespace project {

class WalletMapper
{
public:
    WalletMapper(QSqlDatabase & _conn);
    ~WalletMapper();

    Wallet * getById(int _id);
    Wallet * getByName(string _name, int _userId);
    list<Wallet*> getAllWallets(int _userId);

    void put(Wallet * _wallet);
    void remove(int _id);

private:
    QSqlDatabase & conn;
};

} // namespace

#endif // WALLETMAPPER_H
