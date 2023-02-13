#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(string category, string name, double price, int qty, string genre, string rating) : Product("movie", name, price, qty),
	genre_(genre),
	rating_(rating){
}

Movie::~Movie()
{

}

set<string> Movie::keywords() const{
	set<string> name = parseStringToWords(convToLower(name_));
	set<string> genre = parseStringToWords(convToLower(genre_));

	set<string> keywords = setUnion(name, genre); 

	return keywords;
}


void Movie::dump(std::ostream& os) const
{
    os << "movie" << "\n" << getName() << "\n" << getPrice() << "\n" << getQty() << "\n" << genre_ << "\n" << rating_ << endl;
}

string Movie::displayString() const{
	stringstream ss;
	ss << fixed << setprecision(2) << price_;
	string priceDisplay = ss.str();
	string quantityDisplay = to_string(getQty());

	string display = getName() + "\nGenre: " + genre_  + " Rating: " + rating_ + "\n" + priceDisplay + " " + quantityDisplay + " left.";
	return display;
}