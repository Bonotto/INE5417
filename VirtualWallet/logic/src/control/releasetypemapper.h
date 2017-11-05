#ifndef RELEASETYPEMAPPER_H
#define RELEASETYPEMAPPER_H

#include <QDebug>
#include <QDir>
#include <QtSql>
#include <QSqlDriver>
#include <qsqldatabase.h>
#include <QSqlError>
#include <QPluginLoader>

#include <string>
#include <list>

#include "src/model/releasetype.h"

namespace project {

class ReleaseTypeMapper
{
public:
    ReleaseTypeMapper(QSqlDatabase & _conn);
    ~ReleaseTypeMapper();



    ReleaseType * getById(int id);
    ReleaseType * getByName(string name);
    list<ReleaseType*> getAllReleasesTypes();

    void put(ReleaseType * releaseType);
    void remove(int id);

private:
    void putExistUser(ReleaseType * releaseType);
    void putNewUser(ReleaseType * releaseType);

    QSqlDatabase & conn;
};

} // namespace

#endif // RELEASETYPEMAPPER_H
