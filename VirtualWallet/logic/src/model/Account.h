//! Copyright [2017] Bruno Bonotto and João Vicente Souto

#ifndef PROJECT_ACCOUNT_H
#define PROJECT_ACCOUNT_H

#include <string>
#include <list>
#include "Release.h"

using namespace std;

namespace project {

class Account {
public:
    Account(string _name, double _balance, bool _type);
    virtual ~Account();
    
    bool getType();
    size_t getId();
    string getName();
    double getBalance();
    list<Release*> getReleases();
    
    void changeName(string _newName);
    void insertRelease(Release& _release);
    void removeRelease(Release& _release);
    
private:
    size_t id{0};
    bool type;
    double balance{0.0};
    string name;
    list<Release*> releases;
    
};
    
}  // namespace project

#endif
