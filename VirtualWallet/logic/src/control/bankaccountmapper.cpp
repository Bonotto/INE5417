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
    QSqlQuery query(conn);
    query.exec("SELECT * FROM ACCOUNT WHERE ID = " + QString::number(_id) + " AND TYPE = '1'");

    if(query.size() == 0)
        return nullptr;

    query.next();

    string name = query.value(1).toString().toStdString();
    double balance = query.value(3).toDouble();
    string number = query.value(4).toString().toStdString();
    string agency = query.value(5).toString().toStdString();
    string bank = query.value(6).toString().toStdString();
    int userId = query.value(7).toInt();

    return new BankAccount(_id, name, balance, number, agency, bank, userId);
}

BankAccount * BankAccountMapper::getByName(string name, int _userId)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM ACCOUNT WHERE NAME = '" +
                        QString::fromStdString(name) + "' AND USER_ID = " + QString::number(_userId));

    if(query.size() == 0)
        return nullptr;

    query.next();

    int id = query.value(0).toInt();
    double balance = query.value(3).toDouble();
    string number = query.value(4).toString().toStdString();
    string agency = query.value(5).toString().toStdString();
    string bank = query.value(6).toString().toStdString();

    return new BankAccount(id, name, balance, number, agency, bank, _userId);
}

list<BankAccount*> BankAccountMapper::getAllBankAccounts(int _userId)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM ACCOUNT WHERE USER_ID = " + QString::number(_userId) + " AND TYPE = '1'");

    list<BankAccount*> bankAccounts;

    while (query.next()) {
        int id = query.value(0).toInt();
        string name = query.value(1).toString().toStdString();
        double balance = query.value(3).toDouble();
        string number = query.value(4).toString().toStdString();
        string agency = query.value(5).toString().toStdString();
        string bank = query.value(6).toString().toStdString();

        bankAccounts.push_front(new BankAccount(id, name, balance, number, agency, bank, _userId));
    }

    return bankAccounts;
}

void BankAccountMapper::put(BankAccount * _bankAccount)
{
    BankAccount * bankAccount = getById(_bankAccount->getId());
    QSqlQuery query(conn);

    if (bankAccount != nullptr)
        query.exec("UPDATE ACCOUNT SET NAME = '" + QString::fromStdString(_bankAccount->getName()) +
                            "', BALANCE = " + QString::number(_bankAccount->getBalance()) +
                            ", ACC_NUMBER = '" + QString::fromStdString(_bankAccount->getAccountNumber()) +
                            "', AGENCY = '" + QString::fromStdString(_bankAccount->getAgency()) +
                            "', BANK = '" + QString::fromStdString(_bankAccount->getBank()) +
                            "', USER_ID = " + QString::number(_bankAccount->getUserId()) +
                            " WHERE ID = " + QString::number(bankAccount->getId()));
    else
        query.exec("INSERT INTO ACCOUNT (NAME, TYPE, BALANCE, ACC_NUMBER, AGENCY, BANK, USER_ID) VALUES('" +
                            QString::fromStdString(_bankAccount->getName()) + "', " +
                            QString::fromStdString((_bankAccount->getType()) ? "'1'" : "'0'") + ", " +
                            QString::number(_bankAccount->getBalance()) + ", '" +
                            QString::fromStdString(_bankAccount->getAccountNumber()) + "', '" +
                            QString::fromStdString(_bankAccount->getAgency()) + "', '" +
                            QString::fromStdString(_bankAccount->getBank()) + "', " +
                            QString::number(_bankAccount->getUserId()) + ");");

        delete bankAccount;
}

void BankAccountMapper::remove(int _id)
{
    QSqlQuery query(conn);
    query.exec("DELETE FROM ACCOUNT WHERE ID = " + QString::number(_id));
}

} // namespace
