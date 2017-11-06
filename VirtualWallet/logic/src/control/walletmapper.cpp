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
    QSqlQuery query(conn);
    QString cmd("SELECT * FROM ACCOUNT WHERE ID = " + QString::number(_id));
    query.exec(cmd);

    if(query.size() == 0)
        return nullptr;

    query.next();

    string name = query.value(1).toString().toStdString();
    double balance = query.value(3).toDouble();
    int userId = query.value(7).toInt();

    return new Wallet(_id, name, balance, userId);
}

Wallet * WalletMapper::getByName(string _name, int _userId)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM ACCOUNT WHERE NAME = '" +
                        QString::fromStdString(_name) + "' AND USER_ID = " + QString::number(_userId));

    if(query.size() == 0)
        return nullptr;

    query.next();

    int id = query.value(0).toInt();
    double balance = query.value(3).toDouble();

    return new Wallet(id, _name, balance, _userId);
}

list<Wallet*> WalletMapper::getAllWallets(int _userId)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM ACCOUNT WHERE USER_ID = " + QString::number(_userId) + " AND TYPE = '0'");

    list<Wallet*> wallets;

    while (query.next()) {
        int id = query.value(0).toInt();
        string name = query.value(1).toString().toStdString();
        double balance = query.value(3).toDouble();

        wallets.push_front(new Wallet(id, name, balance, _userId));
    }

    return wallets;
}

void WalletMapper::put(Wallet * _wallet)
{
    Wallet * wallet = getById(_wallet->getId());
    QSqlQuery query(conn);

    if (wallet != nullptr) {
        query.exec("UPDATE ACCOUNT SET NAME = '" + QString::fromStdString(_wallet->getName()) +
                   "', BALANCE = " + QString::number(_wallet->getBalance()) +
                   ", USER_ID = " + QString::number(_wallet->getUserId()) +
                   " WHERE ID = " + QString::number(wallet->getId()));
    } else {
        QString cmd("INSERT INTO ACCOUNT (NAME, TYPE, BALANCE, USER_ID) VALUES('" +
                    QString::fromStdString(_wallet->getName()) + "', " +
                    QString::fromStdString((_wallet->getType()) ? "'1'" : "'0'") + ", " +
                    QString::number(_wallet->getBalance()) + ", " +
                    QString::number(_wallet->getUserId()) + ");");
        query.exec(cmd);
    }

        delete wallet;
}

void WalletMapper::remove(int _id)
{
    QSqlQuery query(conn);
    query.exec("DELETE FROM ACCOUNT WHERE ID = " + QString::number(_id));
}

} // namespace
