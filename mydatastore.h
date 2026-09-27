#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

class MyDataStore : public DataStore{
    public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);

    vector<Product*> search(vector<string>& terms, int type);

    void dump(ostream& ofile);

    bool hasUser(string username) const;

    bool addToCart(string username, Product* product);

    bool viewCart(string username) const;

    bool buyCart(string username);

    private:
    vector<Product*> products_;

    map<string, User*> users_;

    map<string, set<Product*>> keywordMap_;

    map<string, vector<Product*> > carts_;

};

#endif
