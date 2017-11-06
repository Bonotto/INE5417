#include "releasetypemapper.h"

namespace project {

ReleaseTypeMapper::ReleaseTypeMapper(QSqlDatabase & _conn) :
    conn(_conn)
{

}

ReleaseTypeMapper::~ReleaseTypeMapper()
{

}

ReleaseType * ReleaseTypeMapper::getById(int _id)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM RELEASE_TYPE WHERE ID = " + QString::number(_id));

    if(query.size() == 0)
        return nullptr;

    query.next();

    string name = query.value(1).toString().toStdString();
    int userId = query.value(2).toInt();

    return new ReleaseType(name, _id, userId);
}

ReleaseType * ReleaseTypeMapper::getByName(string _typeName, int _userId)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM RELEASE_TYPE WHERE NAME = '" + QString::fromStdString(_typeName) + "' AND USER_ID = " + QString::number(_userId));

    if(query.size() == 0)
        return nullptr;

    query.next();

    int id = query.value(0).toInt();

    return new ReleaseType(_typeName, id, _userId);
}

list<ReleaseType*> ReleaseTypeMapper::getAllReleasesTypes(int _userId)
{
    QSqlQuery query(conn);
    query.exec("SELECT * FROM RELEASE_TYPE WHERE USER_ID = " + QString::number(_userId));

    list<ReleaseType*> types;

    while (query.next()) {
        int id = query.value(0).toInt();
        string name = query.value(1).toString().toStdString();
        int userId = query.value(2).toInt();
        types.push_front(new ReleaseType(name, id, userId));
    }

    return types;
}

void ReleaseTypeMapper::put(ReleaseType * _releaseType)
{
    ReleaseType * releaseTypeAux = getById(_releaseType->getId());
    QSqlQuery query(conn);

    if (releaseTypeAux != nullptr)
        query.exec("UPDATE RELEASE_TYPE SET NAME = '" + QString::fromStdString(_releaseType->getName()) +
                            "' WHERE ID = " + QString::number(releaseTypeAux->getId()));
    else
        query.exec("INSERT INTO RELEASE_TYPE (NAME, USER_ID) VALUES('" +
                            QString::fromStdString(_releaseType->getName()) + "', " +
                            QString::number(_releaseType->getUserId()) + ");");

        delete releaseTypeAux;
}

void ReleaseTypeMapper::remove(int _id)
{
    QSqlQuery query(conn);
    query.exec("DELETE FROM RELEASE_TYPE WHERE ID = " + QString::number(_id));
}

} // namespace
