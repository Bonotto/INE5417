#ifndef DATABASE_H
#define DATABASE_H

#include "src/model/User.h"
#include "src/model/Wallet.h"
#include "src/model/Release.h"
#include "src/model/Account.h"
#include "src/model/BankAccount.h"
#include "src/model/releasetype.h"

#include "src/control/usermapper.h"
#include "src/control/walletmapper.h"
#include "src/control/bankaccountmapper.h"
#include "src/control/releasemapper.h"
#include "src/control/releasetypemapper.h"

#include <QDebug>
#include <QDir>
#include <QtSql>
#include <QSqlDriver>
#include <qsqldatabase.h>
#include <QSqlError>
#include <QPluginLoader>

#include <string>
#include <list>

using namespace std;

namespace project {

class DataBase
{
public:
    DataBase();
    ~DataBase();

    User * getUser(int _id);
    User * getUserByName(string _name);
    User * getUserByNameAndPass(string _name, string _password);
    User * getUserByCodeAndPass(string _code, string _password);
    User * getUserByNameAndCode(string _name, string _code);

    void put(User * _user);

    list<Wallet*> getWallets(int _userId);
    list<Account*> getAccounts(int _userId);
    list<BankAccount*> getBankAccounts(int _userId);

    list<Release*> getReleases(int _userId);
    list<ReleaseType*> getReleaseTypes(int _userId);

    Account * getAccount(string _accName, int _userId);

    bool put(ReleaseType * _type, int _userId);
    void removeReleaseType(int _typeId, int _userId);
    void removeReleasesByType(string _type, int _userId);
    void removeRelease(int _relId, int _userId);

    bool put(Wallet * _account, int _userId);
    void removeAccount(int _accId, int _userId);
    bool put(BankAccount * _account, int _userId);

    bool put(Release * _release, int _userId);
private:
    void createTables();

    int counterUser{0},
        counterAccounts{0},
        counterReleases{0},
        counterReleaseTypes{6};
    User * user;

    QSqlDatabase conn;
    UserMapper * userMapper;
    WalletMapper * walletMapper;
    BankAccountMapper * bankAccountMapper;
    ReleaseMapper * releaseMapper;
    ReleaseTypeMapper * releaseTypeMapper;

};

} // namespace

#endif // DATABASE_H
