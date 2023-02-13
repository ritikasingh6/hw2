#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;


Book::Book(string category, string name, double price, int qty, string ISBN, string author) : Product("book", name, price, qty),
	ISBN_(ISBN),
	author_(author){
}


Book::~Book()
{

}

set<string> Book::keywords() const{
	set<string> name = parseStringToWords(convToLower(name_));
	set<string> author = parseStringToWords(convToLower(author_));

	set<string> keywords = setUnion(name, author); 
	set<string> ISBN;

	keywords.insert(ISBN_);

	return keywords;
}

void Book::dump(std::ostream& os) const
{
    os << "book" << "\n" << getName() << "\n" << getPrice() << "\n" << getQty() << "\n" << ISBN_ << "\n" << author_ << endl;
}

string Book::displayString() const{
	stringstream ss;
	ss << fixed << setprecision(2) << getPrice();
	string priceDisplay = ss.str();
	string quantityDisplay = to_string(getQty());

	string display = getName() + "\nAuthor: " + author_  + " ISBN: " + ISBN_ + "\n" + priceDisplay + " "+ quantityDisplay + " left.";

	return display;
}
