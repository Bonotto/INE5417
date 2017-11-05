#ifndef USERMAPPER_H
#define USERMAPPER_H

#include "src/model/User.h"

#include <QDebug>
#include <QDir>
#include <QtSql>
#include <QSqlDriver>
#include <qsqldatabase.h>
#include <QSqlError>
#include <QPluginLoader>

#include <string>
#include <list>

namespace project {

class UserMapper
{
public:
    UserMapper(QSqlDatabase & _conn);
    ~UserMapper();

    User * getById(int id);
    User * getByName(string name);
    list<User*> getAllUsers();

    void put(User * user);
    void remove(int id);

private:

    QSqlDatabase & conn;
};

} // namespace

#endif // USERMAPPER_H
