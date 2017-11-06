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

    ReleaseType * getById(int _id);
    ReleaseType * getByName(string _typeName, int _userId);
    list<ReleaseType*> getAllReleasesTypes(int _userId);

    void put(ReleaseType * _releaseType);
    void remove(int _id);

private:
    QSqlDatabase & conn;
};

} // namespace

#endif // RELEASETYPEMAPPER_H
