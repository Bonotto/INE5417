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

namespace project {

class ReleaseMapper
{
public:
    ReleaseMapper(QSqlDatabase & _conn);
    ~ReleaseMapper();

    Release * getById(int id);
    list<Release*> getAllReleases(int _accId);

    void put(Release * release);
    void remove(int id);

private:
    QSqlDatabase & conn;
};

} // namespace

#endif // RELEASEMAPPER_H
