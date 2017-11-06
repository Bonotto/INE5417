#include "releasemapper.h"

namespace project {

ReleaseMapper::ReleaseMapper(QSqlDatabase & _conn, WalletMapper * _walletMapper,
                             BankAccountMapper * _bankAccountMapper, ReleaseTypeMapper * _releaseTypeMapper) :
    conn(_conn),
    walletMapper(_walletMapper),
    bankAccountMapper(_bankAccountMapper),
    releaseTypeMapper(_releaseTypeMapper)
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

    double value = query.value(1).toDouble();
    string payment = query.value(4).toString().toStdString();
    string op = query.value(5).toString().toStdString();
    string date = query.value(6).toString().toStdString();
    string desc = query.value(7).toString().toStdString();

    ReleaseType * type = releaseTypeMapper->getById(query.value(3).toInt());
    Account * acc = walletMapper->getById(query.value(2).toInt());

    if (acc == nullptr)
        acc = bankAccountMapper->getById(query.value(2).toInt());

    return new Release(id, value, acc, type, payment, desc, op, date, acc->getUserId());
}

list<Release*> ReleaseMapper::getAllReleases(int _userId)
{
    QSqlQuery query(conn);
    query.prepare("SELECT * FROM RLS WHERE USER_ID = " + QString::number(_userId));
    query.exec();

    list<Release*> releases;

    while (query.next()) {
        int id = query.value(0).toInt();
        double value = query.value(1).toDouble();
        string payment = query.value(4).toString().toStdString();
        string op = query.value(5).toString().toStdString();
        string date = query.value(6).toString().toStdString();
        string desc = query.value(7).toString().toStdString();

        ReleaseType * type = releaseTypeMapper->getById(query.value(3).toInt());
        Account * acc = walletMapper->getById(query.value(2).toInt());

        if (acc == nullptr)
            acc = bankAccountMapper->getById(query.value(2).toInt());

        releases.push_front(new Release(id, value, acc, type, payment, desc, op, date, acc->getUserId()));
    }

    return releases;
}

void ReleaseMapper::put(Release * release)
{
    Release * _release = getById(release->getId());
    QSqlQuery query(conn);

    if (_release != nullptr)
        query.prepare("UPDATE RELEASE_TYPE SET VALUE = " + QString::number(release->getValue()) +
                            ", ACC_ID = " + QString::number(release->getAccount()->getId()) +
                            ", REL_TYPE = " + QString::number(release->getReleaseType()->getId()) +
                            ", PAY_TYPE = '" + QString::fromStdString(release->getPaymentType()) +
                            "', OP = '" + QString::fromStdString(release->getOperation()) +
                            "', DATE = '" + QString::fromStdString(release->getDate()) +
                            "', DESCP = '" + QString::fromStdString(release->getDescription()) +
                            "', USER_ID = " + QString::number(release->getUserId()) +
                            "' WHERE ID = " + QString::number(_release->getId()));
    else
        query.prepare("INSERT INTO RLS (VALUE, ACC_ID, REL_TYPE, PAY_TYPE, OP, DATE, DESCP, USER_ID) VALUES(" +
                            QString::number(release->getValue()) + ", " +
                            QString::number(release->getAccount()->getId()) + ", " +
                            QString::number(release->getReleaseType()->getId()) + ", " +
                            QString::fromStdString(release->getPaymentType()) + ", " +
                            QString::fromStdString(release->getOperation()) + ", " +
                            QString::fromStdString(release->getDate()) + ", " +
                            QString::fromStdString(release->getDescription()) + ", " +
                            QString::number(release->getUserId()) + ");");

        query.exec();

        delete _release;
}

void ReleaseMapper::remove(int id)
{
    QSqlQuery query(conn);
    query.prepare("DELETE * FROM RLS WHERE ID = " + QString::number(id));
    query.exec();
}

} // namespace
