#include "releasemapper.h"

namespace project {

ReleaseMapper::ReleaseMapper(QSqlDatabase & _conn) :
    conn(_conn),

{

}

ReleaseMapper::~ReleaseMapper()
{

}

Release * ReleaseMapper::getById(int id)
{
    QSqlQuery query(conn);
    query.prepare("SELECT * FROM RLS WHERE ID = " + QString::number(id));
    query.exec();

    if(query.size() == 0)
        return nullptr;

    double value = query.value(1).toString().toStdString();
    Account * acc = accountMapper->get= query.value(2).toString().toStdString();
    string pass = query.value(3).toString().toStdString();
    string pass = query.value(3).toString().toStdString();
    string pass = query.value(3).toString().toStdString();
    string pass = query.value(3).toString().toStdString();
    string pass = query.value(3).toString().toStdString();

    return new User(id, name, pass, code);
}

list<Release*> ReleaseMapper::getAllReleases()
{
    return list<Release*>();
}

void ReleaseMapper::put(Release * release)
{

}

void ReleaseMapper::remove(int id)
{

}

} // namespace
