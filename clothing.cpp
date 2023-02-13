#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(string category, string name, double price, int qty, string size, string brand) : Product("clothing", name, price, qty),
	size_(size),
	brand_(brand){
}

Clothing::~Clothing()
{

}

set<string> Clothing::keywords() const{
	set<string> name = parseStringToWords(convToLower(name_));
	set<string> brand = parseStringToWords(convToLower(brand_));

	set<string> keywords = setUnion(name, brand); 

	return keywords;
}


void Clothing::dump(std::ostream& os) const
{
    os << "clothing" << "\n" << getName() << "\n" << getPrice() << "\n" << getQty() << "\n" << size_ << "\n" << brand_ << endl;
}

string Clothing::displayString() const{
	stringstream ss;
	ss << fixed << setprecision(2) << price_;
	string priceDisplay = ss.str();
	string quantityDisplay = to_string(getQty());

	string display = getName() + "\nSize: " + size_  + " Brand: " + brand_ + "\n" + priceDisplay + " " + quantityDisplay + " left.";
	return display;
}