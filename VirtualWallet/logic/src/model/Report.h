//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_REPORT_H
#define PROJECT_REPORT_H

#include <string>
#include <list>
#include <cmath>
#include <QDate>

#include "Account.h"
#include "Release.h"
#include "releasetype.h"

using namespace std;

namespace project {

class Report {
public:
    Report(list<Account*> &_accounts, list<ReleaseType*> &_releasesTypes, list<string> &_paymentTypes,
           string _begin, string _end, double _lowerValue, double _upperValue, bool _in, bool _out, list<Release*> & _releases);
    ~Report();
    
    list<Release*> getReleases();

    int amount();
    size_t amountInReleases();
    size_t amountOutReleases();
    
private:
    void searchByReleasesType();
    void searchByPaymentType();
    void searchByDate();
    void searchByValue();

    string begin, end;
    double lowerValue, upperValue;
    list<Account*> accounts;        //!< Immutables
    list<Release*> releases;
    list<ReleaseType*> releasesTypes;
    list<string> paymentTypes;
    bool in, out;
    
};

}  // namespace project

#endif
