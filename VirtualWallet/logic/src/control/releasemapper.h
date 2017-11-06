#ifndef RELEASEMAPPER_H
#define RELEASEMAPPER_H

#include <QDebug>
#include <QDir>
#include <QtSql>
#include <QSqlDriver>
#include <qsqldatabase.h>
#include <QSqlError>
#include <QPluginLoader>

#include <string>
#include <list>

#include "src/model/Release.h"
#include "src/control/walletmapper.h"
#include "src/control/bankaccountmapper.h"
#include "src/control/releasetypemapper.h"

namespace project {

class ReleaseMapper
{
public:
    ReleaseMapper(QSqlDatabase & _conn, WalletMapper * _walletMapper,
                  BankAccountMapper * _bankAccountMapper, ReleaseTypeMapper * _releaseTypeMapper);
    ~ReleaseMapper();

    Release * getById(int id);
    list<Release*> getAllReleases(int _accId);

    void put(Release * release);
    void remove(int id);

private:
    QSqlDatabase & conn;
    WalletMapper * walletMapper;
    BankAccountMapper * bankAccountMapper;
    ReleaseTypeMapper * releaseTypeMapper;
};

} // namespace

#endif // RELEASEMAPPER_H
