#include <sstream>
#include <iomanip>
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
	for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
		delete it -> second;
	}
	for (vector<Product*>::iterator it2 = products_.begin(); it2 != products_.end(); ++it2){
		delete *it2;
	}
}

void MyDataStore::addProduct(Product* p){
	products_.push_back(p);
	set<string> keywords = p -> keywords();

	map<string, set<Product*>>::iterator it2;

	for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it){
		// look for keyword in keyword product map .find()
		// if not there, create pair of keyword vector product*
		// add product* to set of product* keywords
		// if exists, just add it
		it2 = index_.find(convToLower(*it)); //convToLower?
		if (it2 == index_.end()){
			set<Product*> temp;
			temp.insert(p);
			index_.insert(make_pair(*it, temp));
		}
		else{
			index_[*it].insert(p);
		}
		
	}

}

void MyDataStore::addUser(User* u){
	// create cart to user
	// add user to user map 
	// add cart to user

	// make cart vector<Product*> cart;
	// make map pair of user get name and user
	//make map pair username to cart
	vector<Product*> cartCreate;
	users_[convToLower(u->getName())] = u;
	carts_[u->getName()] = cartCreate;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
	vector<Product*> returnVec;
	if (terms.size() == 0){
		return returnVec;
	}
	set<Product*> temp;
	// intersection is AND
	if (type == 0){
		vector<Product*> intersection;

		map<string, set<Product*>>::iterator it2;

		for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
			it2 = index_.find(*it);

			if(it2 == index_.end()){
				return intersection;
			}
			else{
				if(temp.empty()){
					temp = it2 -> second;
				}
				else{
					temp = setIntersection(temp, it2 -> second);
				}
			}

		}
	}
	//union is OR
	else if (type == 1){
		vector<Product*> unions;


		map<string, set<Product*>>::iterator it2;

		for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
			it2 = index_.find(*it);

			if(it2 == index_.end()){
				continue;
			}

			else{
				if(temp.empty()){
					temp = it2 -> second;
				}
				else{
					temp = setUnion(temp, it2 -> second);
				}
			}
		}

	}

	// at end, change temp to vector and return vector
	set<Product*>:: iterator itt;
	for (itt = temp.begin(); itt != temp.end(); ++itt){
		returnVec.push_back(*itt);
	}
	return returnVec;

}

void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << endl;

	for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
		(*it) -> dump(ofile);
	}

	ofile << "</products>" << endl;
	ofile << "<users>" << endl;

	// iterate through users
	for (map<string, User*>::iterator it2 = users_.begin(); it2 != users_.end(); ++it2){
		(it2 -> second) -> dump(ofile);
	}

	ofile << "</users>" << endl;
	
}

void MyDataStore::buyCart(string username){

	map<string, User*>::iterator it;
	it = users_.find(username);
	if (it == users_.end()){
		cout << "Invalid Username" << endl;
		return;
	}

	User* tempUser = it -> second;
	map<string, vector<Product*>>::iterator it2 = carts_.find(username);
	if (it2 == carts_.end()){
		return;
	}

	vector<Product*> tempCart = it2 -> second;
	vector<Product*> newCart;

	for (vector<Product*>::iterator it3 = tempCart.begin(); it3 != tempCart.end();){
		Product* tempProduct = *it3;
		// if user doesn't have enough money to buy
		if (tempUser -> getBalance() < tempProduct -> getPrice()){
			++it3;
			newCart.push_back(tempProduct);
		}
		// if the product is out of stock
		else if (tempProduct -> getQty() < 1){
			++it3;
			newCart.push_back(tempProduct);
		}
		else{
			tempProduct ->subtractQty(1);
			
			tempUser -> deductAmount(tempProduct -> getPrice());
			++it3;
		}

	}
	it2 -> second = newCart;

}

void MyDataStore::viewCart(string username){
	map<string, User*>::iterator it;
	it = users_.find(username);
	if (it == users_.end()){
		cout << "Invalid Username" << endl;
		return;
	}
	map<string, vector<Product*>>::iterator it2;
	it2 = carts_.find(username);
	if (it2 == carts_.end()){
		return;
	}

	vector<Product*> tempCart = it2 -> second;

	int curr = 1;
	
	for (vector<Product*>::iterator it3 = tempCart.begin(); it3 != tempCart.end(); ++it3){
		cout << "Item " << curr << endl;
		cout << (*it3) -> displayString() << endl;
		curr++;
	}
}

void MyDataStore::addToCart(string username, Product* product_){
	map<string, User*>::iterator it;
	it = users_.find(username);
	if (it == users_.end()){
		cout << "Invalid Request" << endl;
		return;
	}

	map<string, vector<Product*>>::iterator it2;
	it2 = carts_.find(username);
	if (it2 == carts_.end()){
		vector<Product*> productsList;
		productsList.push_back(product_);
		it2->second = productsList;
	}
	else{
		(it2 -> second).push_back(product_);
	}

}