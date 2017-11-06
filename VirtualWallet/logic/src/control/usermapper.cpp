#include "usermapper.h"

namespace project {

UserMapper::UserMapper(QSqlDatabase & _conn) :
    conn(_conn)
{

}

UserMapper::~UserMapper()
{

}

User * UserMapper::getById(int id)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM USR WHERE ID = " + QString::number(id));

    if(query.size() == 0)
        return nullptr;

    query.next();
    string name = query.value(1).toString().toStdString();
    string code = query.value(2).toString().toStdString();
    string pass = query.value(3).toString().toStdString();

    return new User(id, name, pass, code);
}

User * UserMapper::getByName(string name)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM USR WHERE NAME = '" + QString::fromStdString(name) + "'");

    if(query.size() == 0)
        return nullptr;

    query.next();
    int id = query.value(0).toInt();
    string code = query.value(2).toString().toStdString();
    string pass = query.value(3).toString().toStdString();

    return new User(id, name, pass, code);
}

list<User*> UserMapper::getAllUsers()
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM USR");

    list<User*> users;

    while (query.next()) {
        int id = query.value(0).toInt();
        string name = query.value(1).toString().toStdString();
        string code = query.value(2).toString().toStdString();
        string pass = query.value(3).toString().toStdString();
        users.push_front(new User(id, name, pass, code));
    }

    return users;
}

void UserMapper::put(User * user)
{
    User * _user = getById(user->getId());
    QSqlQuery query(conn);

    if (_user != nullptr)
        query.exec("UPDATE USR SET NAME = '" + QString::fromStdString(user->getName()) +
                            "', CODE = '" + QString::fromStdString(user->getCode()) +
                            "', PASSWORD = '" + QString::fromStdString(user->getPassword()) +
                            "' WHERE ID = " + QString::number(_user->getId()));
    else
        query.exec("INSERT INTO USR (NAME, CODE, PASSWORD) VALUES('" +
                            QString::fromStdString(user->getName()) + "', '" +
                            QString::fromStdString(user->getCode()) + "', '" +
                            QString::fromStdString(user->getPassword()) + "');");

        delete _user;

        _user = getByName(user->getName());
        user->setId(_user->getId());
        delete _user;
}

void UserMapper::remove(int id)
{
    QSqlQuery query(conn);
    query.exec("DELETE FROM USR WHERE ID = " + QString::number(id));
}

} // namespace
