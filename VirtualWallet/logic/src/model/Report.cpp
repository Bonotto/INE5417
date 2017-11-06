//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#include "Report.h"

namespace project {

Report::Report(list<Account*> &_accounts, list<ReleaseType*> &_releasesTypes, list<string> &_paymentTypes,
               string _begin, string _end, double _lowerValue, double _upperValue, bool _in, bool _out, list<Release*> &_releases) :
    accounts(_accounts),
    releasesTypes(_releasesTypes),
    begin(_begin),
    paymentTypes(_paymentTypes),
    end(_end),
    lowerValue(_lowerValue),
    upperValue(_upperValue),
    in(_in),
    out(_out),
    releases(_releases)
{
    searchByReleasesType();
    searchByPaymentType();
    searchByDate();
    searchByValue();
}

Report::~Report() {

}

list<Release*> Report::getReleases()
{
    return releases;
}

void Report::searchByReleasesType()
{
    list<Release*> aux = releases;

    for (auto & rel : aux) {
        bool removeR = true;
        for (auto & type : releasesTypes)
            if (rel->getReleaseType()->getName() == type->getName())
                removeR = false;
        if (removeR)
            releases.remove(rel);
    }
}

void Report::searchByPaymentType() {
    list<Release*> aux = releases;

    for (auto & rel : aux) {
        bool removeR = true;
        for (std::string type : paymentTypes)
            if (rel->getPaymentType() == type)
                removeR = false;
        if (removeR)
            releases.remove(rel);
    }
}

void Report::searchByDate() {
    list<Release*> aux = releases;
    QDate _beg = QDate::fromString(QString::fromStdString(begin), "dd/MM/yyyy");
    QDate _end = QDate::fromString(QString::fromStdString(end), "dd/MM/yyyy");

    for (auto & rel : aux) {
        QDate relDate = QDate::fromString(QString::fromStdString(rel->getDate()), "dd/MM/yyyy");
        if (relDate < _beg || relDate > _end)
            releases.remove(rel);
    }
}

void Report::searchByValue() {
    list<Release*> aux = releases;

    for (auto & rel : aux) {
        double value = in && out ? abs(rel->getValue()) : in ? rel->getValue() : -rel->getValue();

        if (value < lowerValue || value > upperValue)
            releases.remove(rel);
    }
}

int Report::amount()
{
    int amount = 0;
    for (auto & rel : releases)
        amount += rel->getValue();
    return amount;
}

size_t Report::amountInReleases()
{
    size_t amount = 0;
    for (auto & rel : releases)
        if (rel->getValue() >= 0)
            amount++;
    return amount;
}

size_t Report::amountOutReleases()
{
    size_t amount = 0;
    for (auto & rel : releases)
        if (rel->getValue() < 0)
            amount++;
    return amount;
}

}  // namespace project
