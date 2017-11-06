#include "releasetypemapper.h"

namespace project {

ReleaseTypeMapper::ReleaseTypeMapper(QSqlDatabase & _conn) :
    conn(_conn)
{

}

ReleaseTypeMapper::~ReleaseTypeMapper()
{

}

ReleaseType * ReleaseTypeMapper::getById(int id)
{
    QSqlQuery query(conn);
    query.prepare("SELECT * FROM RELEASE_TYPE WHERE ID = " + QString::number(id));
    query.exec();

    if(query.size() == 0)
        return nullptr;

    string name = query.value(1).toString().toStdString();
    int userId = query.value(2).toInt();

    return new ReleaseType(name, id, userId);
}

ReleaseType * ReleaseTypeMapper::getByName(string name)
{
    QSqlQuery query(conn);
    query.prepare("SELECT * FROM RELEASE_TYPE WHERE NAME = " + QString::fromStdString(name));
    query.exec();

    if(query.size() == 0)
        return nullptr;

    int id = query.value(0).toInt();
    int userId = query.value(2).toInt();

    return new ReleaseType(name, id, userId);
}

list<ReleaseType*> ReleaseTypeMapper::getAllReleasesTypes(int _userId)
{
    QSqlQuery query(conn);
    query.prepare("SELECT * FROM RELEASE_TYPE WHERE USER_ID = " + QString::number(_userId));
    query.exec();

    list<ReleaseType*> types;

    while (query.next()) {
        int id = query.value(0).toInt();
        string name = query.value(1).toString().toStdString();
        int userId = query.value(2).toInt();
        types.push_front(new ReleaseType(name, id, userId));
    }

    return types;
}

void ReleaseTypeMapper::put(ReleaseType * releaseType)
{
    ReleaseType * _releaseType = getById(releaseType->getId());
    QSqlQuery query(conn);

    if (_releaseType != nullptr)
        query.prepare("UPDATE RELEASE_TYPE SET NAME = " + QString::fromStdString(releaseType->getName()) +
                            " WHERE ID = " + QString::number(_releaseType->getId()));
    else
        query.prepare("INSERT INTO RELEASE_TYPE (ID, NAME, USER_ID) VALUES(" +
                            QString::number(releaseType->getId()) + ", " +
                            QString::fromStdString(releaseType->getName()) +
                            QString::number(releaseType->getUserId()) + ");");

        query.exec();

        delete _releaseType;
}

void ReleaseTypeMapper::remove(int id)
{
    QSqlQuery query(conn);
    query.prepare("DELETE * FROM RELEASE_TYPE WHERE ID = " + QString::number(id));
    query.exec();
}

} // namespace
