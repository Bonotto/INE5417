#ifndef RELEASETYPE_H
#define RELEASETYPE_H

#include <string>

using namespace std;

namespace project {

class ReleaseType
{
public:
    explicit ReleaseType(string _name, int _id, int _userId);
    ReleaseType();
    ~ReleaseType();

    int getId();
    int getUserId();
    string getName();

    void setId(int _id);
    void setUserId(int _userId);
    void setTypeName(string _typeName);

private:
    int id{-1}, userId{-1};
    string typeName;
};

}  // namespace

#endif // RELEASETYPE_H
