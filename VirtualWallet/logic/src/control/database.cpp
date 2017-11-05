#include "database.h"

#include <iostream>

using namespace std;

namespace project {

DataBase::DataBase()
{
    conn = QSqlDatabase::addDatabase("QPSQL");
    conn.setUserName("postgres");
    conn.setPassword("senha");
    conn.setHostName("localhost");
    conn.setDatabaseName("engenharia");
    conn.setPort(5432);

    if (conn.open())
        createTables();

    userMapper = new UserMapper(conn);
    walletMapper = new WalletMapper(conn);
    bankAccountMapper = new BankAccountMapper(conn);
    releaseMapper = new ReleaseMapper(conn);
    releaseTypeMapper = new ReleaseTypeMapper(conn);
}

DataBase::~DataBase()
{

}

void DataBase::createTables()
{
    QSqlQuery query(conn);
    query.prepare("CREATE TABLE IF NOT EXISTS USR ("
                    "ID 	  SERIAL PRIMARY KEY,"
                    "NAME 	  CHAR(255) UNIQUE NOT NULL,"
                    "CODE 	  CHAR(255) NOT NULL,"
                    "PASSWORD  CHAR(255) NOT NULL"
                    ");"
                    "CREATE TABLE IF NOT EXISTS ACCOUNT ("
                    "ID 	 	SERIAL 	     PRIMARY KEY,"
                    "NAME 	 	CHAR(255)    UNIQUE NOT NULL,"
                    "TIPO 	 	CHARACTER(1) NOT NULL,"
                    "BALANCE 	FLOAT        NOT NULL,"
                    "ACCNUMBER 	CHAR(255),"
                    "AGENCY 		CHAR(255),"
                    "BANK	 	CHAR(255),"
                    "USER_ID 	INT	     NOT NULL,"
                    "FOREIGN KEY (USER_ID) 	     REFERENCES USR(ID)"
                    "); "
                    "CREATE TABLE IF NOT EXISTS RELEASE_TYPE ("
                    "ID 	 SERIAL    	PRIMARY KEY,"
                    "NAME 	 CHAR(255) 	UNIQUE NOT NULL,"
                    "USER_ID  INT  	   	NOT NULL,"
                    "FOREIGN KEY (USER_ID)   REFERENCES USR(ID)"
                    ");"
                    "CREATE TABLE  IF NOT EXISTS RLS ("
                    "ID 	 SERIAL		PRIMARY KEY,"
                    "VALUE    FLOAT		NOT NULL,"
                    "ACC_ID   INT	 	NOT NULL,"
                    "REL_TYPE INT 		NOT NULL,"
                    "PAY_TYPE CHAR(255) 	NOT NULL,"
                    "OP	 CHAR(3)	NOT NULL,"
                    "DATE	 CHAR(10) 	NOT NULL,"
                    "DESCP    CHAR(255),"
                    "FOREIGN KEY (ACC_ID) 	REFERENCES ACCOUNT(ID),"
                    "FOREIGN KEY (REL_TYPE)  REFERENCES RELEASE_TYPE(ID)"
                    ");");
    query.exec();
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

list<Wallet*> DataBase::getWallets(int _userId)
{
    list<Wallet*> wallets;
    for (auto acc : user->getAccounts())
        if (!acc->getType())
            wallets.push_back(static_cast<Wallet*>(acc));

    return wallets;
}

list<Account*> DataBase::getAccounts(int _userId)
{
    return user->getAccounts();
}

list<BankAccount*> DataBase::getBankAccounts(int _userId)
{
    list<BankAccount*> banksAcc;
    for (auto & acc : user->getAccounts())
        if (acc->getType())
            banksAcc.push_back(static_cast<BankAccount*>(acc));

    return banksAcc;
}

list<Release*> DataBase::getReleases(int _userId)
{
    list<Release*> releases;

    for (auto & acc : user->getAccounts())
        for (auto & rel : acc->getReleases())
            releases.push_front(rel);

    return releases;
}

list<ReleaseType*> DataBase::getReleaseTypes(int _userId)
{
    return releaseTypeMapper->getAllReleasesTypes(_userId);
}

Account * DataBase::getAccount(string _accName, int _userId)
{
    return user->getAccount(_accName);
}

bool DataBase::put(ReleaseType * _type, int _userId)
{
    bool exist = false;
    for (auto & it : releaseTypeMapper->getAllReleasesTypes()) {
        if (!it->getName().compare(_type->getName()))
            exist = true;

        delete it;
    }

    if (exist)
        return false;

    releaseTypeMapper->put(_type);
    return true;
}

void DataBase::removeReleaseType(int _typeId, int _userId)
{
    for (auto it: releaseMapper->getAllReleases(_userId))
        if (it->getId() == _typeId) {
            removeReleasesByType(it->getName(), _userId);
            user->removeReleaseType(it);
            break;
        }
}

void DataBase::removeReleasesByType(string _type, int _userId)
{
    user->removeReleases(_type);
}

void DataBase::removeRelease(int _relId, int _userId)
{
    for (auto & acc : user->getAccounts())
        for (auto & rel : acc->getReleases())
            if (rel->getId() == _relId) {
                acc->removeRelease(rel);
                break;
            }
}

bool DataBase::put(Wallet * _account, int _userId)
{
    for (auto & it: user->getAccounts()) {
        if (!it->getName().compare(_account->getName()))
            return false;

        if (it->getId() == _account->getId()) {
            user->removeAccount(it);
            break;
        }
    }

    if (_account->getId() == -1)
        _account->setId(counterAccounts++);

    return user->insertAccount(_account);
}

void DataBase::removeAccount(int _accId, int _userId)
{
    for (auto & it: user->getAccounts())
        if (it->getId() == _accId) {
            user->removeAccount(it->getName());
            break;
        }
}

bool DataBase::put(BankAccount * _account, int _userId)
{
    for (auto & it: user->getAccounts()) {
        if (!it->getName().compare(_account->getName()))
            return false;

        if (it->getId() == _account->getId()) {
            user->removeAccount(it);
            break;
        }
    }

    if (_account->getId() == -1)
        _account->setId(counterAccounts++);

    return user->insertAccount(_account);
}

bool DataBase::put(Release * _release, int _userId)
{
    for (auto & i : getAccounts(_userId))
        for (auto & j : i->getReleases())
            if (j->getId() == _release->getId()) {
                i->removeRelease(j);
                i->insertRelease(_release);
                return true;
            }

    if (_release->getId() == -1)
        _release->setId(counterReleases++);

    _release->getAccount()->insertRelease(_release);
    return true;
}

}
