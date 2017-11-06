//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_RELEASE_H
#define PROJECT_RELEASE_H

#include <string>
#include <ctime>

using namespace std;

namespace project {

class Account;
class ReleaseType;

class Release {
public:
    Release(int _id, double _value, Account * _account, ReleaseType * _releaseType,
            string _paymentType, string _description, string _operation, string _date);
    ~Release();
    
    size_t getId();
    double getValue();
    Account * getAccount();
    ReleaseType * getReleaseType();
    string getPaymentType();
    string getDescription();
    string getOperation();
    string getDate();

    void setId(int _id);
    
private:
    int id;
    double value;
    Account * account;
    ReleaseType * releaseType;
    string paymentType, description, operation, date;
    
};

}  // namespace project

#endif
