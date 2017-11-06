#include "database.h"

#include <iostream>

using namespace std;

namespace project {

DataBase::DataBase()
{
    conn = QSqlDatabase::addDatabase("QPSQL");
    conn.setDatabaseName("engenharia");
    conn.setHostName("localhost");
    conn.setUserName("postgres");
    conn.setPassword("senha");
    conn.setPort(5432);

    if (conn.open())
        createTables();

    userMapper = new UserMapper(conn);
    walletMapper = new WalletMapper(conn);
    bankAccountMapper = new BankAccountMapper(conn);
    releaseTypeMapper = new ReleaseTypeMapper(conn);
    releaseMapper = new ReleaseMapper(conn, walletMapper, bankAccountMapper, releaseTypeMapper);
}

DataBase::~DataBase()
{

}

void DataBase::createTables()
{
    QSqlQuery query(conn);
    query.prepare("CREATE TABLE IF NOT EXISTS USR ("
                    "ID 	  SERIAL    PRIMARY KEY,"
                    "NAME 	  CHAR(255) UNIQUE NOT NULL,"
                    "CODE 	  CHAR(255) NOT NULL,"
                    "PASSWORD CHAR(255) NOT NULL"
                    ");"
                    "CREATE TABLE IF NOT EXISTS ACCOUNT ("
                    "ID 	 	SERIAL 	    PRIMARY KEY,"
                    "NAME 	 	CHAR(255)   NOT NULL,"
                    "TYPE 	 	CHAR(1)     NOT NULL,"
                    "BALANCE 	FLOAT       NOT NULL,"
                    "ACC_NUMBER CHAR(255),"
                    "AGENCY     CHAR(255),"
                    "BANK	 	CHAR(255),"
                    "USER_ID 	INT         NOT NULL,"
                    "FOREIGN KEY (USER_ID)  REFERENCES USR(ID)"
                    "); "
                    "CREATE TABLE IF NOT EXISTS RELEASE_TYPE ("
                    "ID 	 SERIAL        PRIMARY KEY,"
                    "NAME 	 CHAR(255)     NOT NULL,"
                    "USER_ID INT  	   	   NOT NULL,"
                    "FOREIGN KEY (USER_ID) REFERENCES USR(ID)"
                    ");"
                    "CREATE TABLE  IF NOT EXISTS RLS ("
                    "ID 	  SERIAL	PRIMARY KEY,"
                    "VALUE    FLOAT		NOT NULL,"
                    "ACC_ID   INT	 	NOT NULL,"
                    "REL_TYPE INT 		NOT NULL,"
                    "PAY_TYPE CHAR(255) NOT NULL,"
                    "OP       CHAR(3)	NOT NULL,"
                    "DATE	  CHAR(10) 	NOT NULL,"
                    "DESCP    CHAR(255),"
                    "USER_ID  int       NOT NULL,"
                    "FOREIGN KEY (ACC_ID) 	REFERENCES ACCOUNT(ID),"
                    "FOREIGN KEY (REL_TYPE) REFERENCES RELEASE_TYPE(ID),"
                    "FOREIGN KEY (USER_ID)  REFERENCES USR(ID)"
                    ");");
    query.exec();

    query.prepare("INSERT INTO USR (NAME, CODE, PASSWORD) VALUES('name', 'code', 'pass')");
    query.exec();
    query.prepare("SELECT * FROM USR");
    query.exec();

    while (query.next())
        cout << query.value(1).toString().toStdString() << endl << flush;
}

User * DataBase::getUser(int _id)
{
    return userMapper->getById(_id);
}

User * DataBase::getUserByName(string _name)
{
    return userMapper->getByName(_name);
}

User * DataBase::getUserByNameAndPass(string _name, string _password)
{
    User * user = userMapper->getByName(_name);

    if (user->verifyUser(_name, _password))
        return user;

    return nullptr;
}

User * DataBase::getUserByCodeAndPass(string _code, string _password)
{
    list<User*> users = userMapper->getAllUsers();

    for (auto & u : users)
        if (u->verifyCodePass(_code, _password))
            return u;

    return nullptr;
}


User * DataBase::getUserByNameAndCode(string _name, string _code)
{
    list<User*> users = userMapper->getAllUsers();

    for (auto & u : users)
        if (u->verifyNameCode(_name, _code))
            return u;

    return nullptr;
}

void DataBase::put(User * _user)
{
    userMapper->put(_user);
}

Account * DataBase::getAccount(string _accName, int _userId)
{
    Account * account = walletMapper->getByName(_accName, _userId);

    if (account == nullptr)
        account = bankAccountMapper->getByName(_accName, _userId);

    return account;
}

list<Wallet*> DataBase::getWallets(int _userId)
{
    list<Wallet*> wallets;
    for (auto acc : walletMapper->getAllWallets(_userId))
        if (!acc->getType())
            wallets.push_back(static_cast<Wallet*>(acc));

    return wallets;
}

list<Account*> DataBase::getAccounts(int _userId)
{
    list<Account*> accounts;
    for (auto & wallet: getWallets(_userId))
        accounts.push_front(wallet);

    for (auto & bank: getBankAccounts(_userId))
        accounts.push_front(bank);

    return accounts;
}

list<BankAccount*> DataBase::getBankAccounts(int _userId)
{
    return bankAccountMapper->getAllBankAccounts(_userId);
}

list<Release*> DataBase::getReleases(int _userId)
{
    return releaseMapper->getAllReleases(_userId);
}

list<ReleaseType*> DataBase::getReleaseTypes(int _userId)
{
    return releaseTypeMapper->getAllReleasesTypes(_userId);
}

void DataBase::put(ReleaseType * _type)
{
    releaseTypeMapper->put(_type);
}

void DataBase::removeReleaseType(int _typeId, int _userId)
{
    removeReleasesByType(_typeId, _userId);
    releaseTypeMapper->remove(_typeId);
}

void DataBase::removeReleasesByType(int _typeId, int _userId)
{
    for (auto & rel: releaseMapper->getAllReleases(_userId)) {
        if (rel->getReleaseType()->getId() == _typeId)
            releaseMapper->remove(rel->getId());

        delete rel;
    }
}

void DataBase::removeReleasesByAccount(int _accId, int _userId)
{
    for (auto & rel: releaseMapper->getAllReleases(_userId)) {
        if (rel->getAccount()->getId() == _accId)
            releaseMapper->remove(rel->getId());

        delete rel;
    }
}

void DataBase::removeRelease(int _relId)
{
    releaseMapper->remove(_relId);
}

void DataBase::put(Wallet * _account)
{
    walletMapper->put(_account);
}

void DataBase::removeAccount(int _accId, int _userId)
{
    removeReleasesByAccount(_accId, _userId);
    walletMapper->remove(_accId);
}

void DataBase::put(BankAccount * _account)
{
    bankAccountMapper->put(_account);
}

void DataBase::put(Release * _release)
{
    releaseMapper->put(_release);
}

}
