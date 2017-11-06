#ifndef RELEASEBUILDER_H
#define RELEASEBUILDER_H

#include <string>
#include <stdexcept>

#include "./src/model/Release.h"
#include "./src/model/Account.h"
#include "./src/model/releasetype.h"

using namespace std;

namespace project {

class ReleaseBuilder
{
public:
    ReleaseBuilder(int _id, double _value, Account * _account, ReleaseType * _releaseType,
                   string _paymentType, string _description, string operation, string _date, int _userId);
    ~ReleaseBuilder();

    bool isValid();
    Release * build();

private:
    int id, userId;
    double value;
    Account* account;
    ReleaseType * releaseType;
    string paymentType, description, operation, date;
};

}

#endif // RELEASEBUILDER_H
