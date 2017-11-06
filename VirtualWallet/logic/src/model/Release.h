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
            string _paymentType, string _description, string _operation, string _date, int _user_id);
    ~Release();

    int getId();
    int getUserId();
    double getValue();
    Account * getAccount();
    ReleaseType * getReleaseType();
    string getPaymentType();
    string getDescription();
    string getOperation();
    string getDate();
    
private:
    int id, user_id;
    double value;
    Account * account;
    ReleaseType * releaseType;
    string paymentType, description, operation, date;
    
};

}  // namespace project

#endif
