#ifndef REPORTBUILDER_H
#define REPORTBUILDER_H

#include "./src/model/Report.h"

namespace project {

using namespace std;

class ReportBuilder
{
public:
    ReportBuilder(list<Account*> &_accounts, list<ReleaseType*> &_releasesTypes, list<string> &_paymentTypes,
                  string _begin, string _end, double _lowerValue, double _upperValue, bool _in, bool _out, list<Release*> _releases);
    ~ReportBuilder();

    bool isValid();
    Report * build();

private:
    list<Release*> releases;
    list<Account*> accounts;
    list<ReleaseType*> releasesTypes;
    list<string> paymentTypes;
    string begin, end;
    double lowerValue, upperValue;
    bool in, out;
};

} // namespace project


#endif // REPORTBUILDER_H
