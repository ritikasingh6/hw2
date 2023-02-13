#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <list>
#include <map>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"
#include "datastore.h"

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */

	//buy cart, view cart

class MyDataStore: public DataStore{
public:
		MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);


		// buy cart
		// 

		void buyCart(std:: string);
		void viewCart(std:: string);
		void addToCart(std:: string, Product*);




		


protected:

private:
std::map<std::string, std::set<Product*>> index_;
std::map<std::string,User*> users_;
std::vector<Product*> products_;
std::map<std::string, std::vector<Product*>> carts_;

};

#endif