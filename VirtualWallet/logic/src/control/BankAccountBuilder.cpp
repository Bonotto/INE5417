#include "BankAccountBuilder.h"

namespace project {

BankAccountBuilder::BankAccountBuilder(int _id, std::string _name, double _balance, std::string _accountNumber, std::string _agency, std::string _bank, int _userId) :
    id(_id),
    name(_name),
    balance(_balance),
    accountNumber(_accountNumber),
    agency(_agency),
    bank(_bank),
    userId(_userId)
{

}

BankAccountBuilder::~BankAccountBuilder() {
    
}

bool BankAccountBuilder::isValid() {
    return !name.empty() && balance >= 0 && !accountNumber.empty() && !agency.empty() && !bank.empty();
}

BankAccount* BankAccountBuilder::build() {
    if (!isValid())
        throw std::out_of_range("Os parâmetros para a criação não são validos!");

    return new BankAccount(id, name, balance, accountNumber, agency, bank, userId);
}

}  // namespace project
