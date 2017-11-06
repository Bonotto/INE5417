#include "ReportBuilder.h"

namespace project {

ReportBuilder::ReportBuilder(list<Account*> &_accounts, list<ReleaseType*> &_releasesTypes, list<string> &_paymentTypes,
              string _begin, string _end, double _lowerValue, double _upperValue, bool _in, bool _out, list<Release*> _releases) :
    accounts(_accounts),
    releasesTypes(_releasesTypes),
    paymentTypes(_paymentTypes),
    begin(_begin),
    end(_end),
    lowerValue(_lowerValue),
    upperValue(_upperValue),
    in(_in),
    out(_out),
    releases(_releases)
{

}

ReportBuilder::~ReportBuilder()
{

}

bool ReportBuilder::isValid()
{
    return accounts.size() && releasesTypes.size() && paymentTypes.size() && begin != "" && end != "" &&
           lowerValue >= 0 && upperValue >= 0 && lowerValue <= upperValue && (in || out);
}

Report * ReportBuilder::build()
{
    if (!isValid())
        throw std::out_of_range("Impossivel construir o relatorio!");
    return new Report(accounts, releasesTypes, paymentTypes, begin, end, lowerValue, upperValue, in, out, releases);
}

}
