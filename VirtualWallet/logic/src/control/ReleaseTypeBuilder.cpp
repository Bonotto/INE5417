#include "ReleaseTypeBuilder.h"

namespace project {

ReleaseTypeBuilder::ReleaseTypeBuilder(std::string _name, int _id, int _userId) :
    name(_name),
    id(_id),
    userId(_userId)
{

}

ReleaseTypeBuilder::~ReleaseTypeBuilder() {
    
}

bool ReleaseTypeBuilder::isValid() {
    return !name.empty();
}

ReleaseType * ReleaseTypeBuilder::build() {
    if (!isValid())
        throw std::out_of_range("Os parâmetros para a criação não são validos!");
    return new ReleaseType(name, id, userId);
}

}
