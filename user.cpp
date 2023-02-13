#include "user.h"
#include <iomanip>
#include "sstream"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
	stringstream ss;
	ss << fixed << setprecision(2) << balance_;
	string balanceDisplay = ss.str();
  os << name_ << " "  << balanceDisplay << " " << type_ << endl;
}
