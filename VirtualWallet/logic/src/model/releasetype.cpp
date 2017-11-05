#include "releasetype.h"

namespace project {

ReleaseType::ReleaseType()
{

}
ReleaseType::ReleaseType(string _name, int _id, int _userId):
    typeName(_name),
    id(_id),
    userId(_userId)
{

}

ReleaseType::~ReleaseType()
{

}

void ReleaseType::setId(int _id)
{
    id = _id;
}


int ReleaseType::getId()
{
    return id;
}

int ReleaseType::getUserId()
{
    return userId;
}

void ReleaseType::setUserId(int _userId)
{
    userId = _userId;
}

void ReleaseType::setTypeName(string _typeName)
{
    typeName = _typeName;
}

string ReleaseType::getName()
{
    return typeName;
}

}  // namespace
