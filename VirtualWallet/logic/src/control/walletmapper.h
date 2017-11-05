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

    Wallet * getById(int id);
    Wallet * getByName(string name);
    list<Wallet*> getAllWallets();

    void put(Wallet * wallet);
    void remove(int id);

private:

    QSqlDatabase & conn;
};

} // namespace

#endif // WALLETMAPPER_H
