#include "mydatastore.h"
#include "util.h"

#include <iostream>

using namespace std;

MyDataStore::MyDataStore(){
}

MyDataStore::~MyDataStore(){
    for(size_t i = 0; i < products_.size(); i++){
        delete products_[i];
    }

    map<string, User*>::iterator it;

    for(it = users_.begin(); it != users_.end(); ++it){
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p){
    products_.push_back(p);

    set<string> words = p->keywords();

    set<string>::iterator it;

    for(it = words.begin(); it!= words.end(); ++it){
        string word = convToLower(*it);

        keywordMap_[word].insert(p);
    }
}

void MyDataStore::addUser(User* u){
    string username = convToLower(u->getName());

    users_[username] = u;

    carts_[username] = vector<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
    vector<Product*> hits;

    if(terms.size() == 0){
        return hits;
    }

    set<Product*> result;

    if(type == 0){
        string firstTerm = convToLower(terms[0]);

        map<string, set<Product*> >::iterator mapIt;
        mapIt = keywordMap_.find(firstTerm);

        if(mapIt == keywordMap_.end()){
            return hits;
        }
    

    result = mapIt->second;

    for(size_t i = 1; i < terms.size(); i++){
        string term = convToLower(terms[i]);
        mapIt = keywordMap_.find(term);

        if(mapIt == keywordMap_.end()){
            return hits;
        }

        result = setIntersection(result, mapIt->second);
    }
    }else{
        for(size_t i = 0; i < terms.size(); i++){
            string term = convToLower(terms[i]);

            map<string, set<Product*> >::iterator mapIt;
            mapIt = keywordMap_.find(term);

            if(mapIt != keywordMap_.end()){
                result = setUnion(result, mapIt->second);
            }
        }
    }

    set<Product*>::iterator it;

    for(it = result.begin(); it != result.end(); ++it){
        hits.push_back(*it);
    }

    return hits;

}

bool MyDataStore::hasUser(string username) const{
    username = convToLower(username);
    
    return users_.find(username) != users_.end();
}

bool MyDataStore::addToCart(string username, Product* product){
    username = convToLower(username);

    if(users_.find(username) == users_.end()){
        return false;
    }

    carts_[username].push_back(product);

    return true;
}

bool MyDataStore::viewCart(string username) const{
    username = convToLower(username);

    map<string, User*>::const_iterator userIt;
    userIt = users_.find(username);

    if(userIt == users_.end()){
        return false;
    }

    map<string, vector<Product*> >::const_iterator cartIt;
    cartIt = carts_.find(username);

    if(cartIt == carts_.end()){
        return true;
    }

    const vector<Product*>& cart = cartIt->second;

    for(size_t i =0; i < cart.size(); i++){
        cout << "Item " << i+1 << endl;
        cout << cart[i]->displayString() << endl;
    }

    return true;
}

bool MyDataStore::buyCart(string username){

    username = convToLower(username);

    map<string, User*>::iterator userIt;
    userIt = users_.find(username);

    if(userIt == users_.end()){
        return false;
    }

    User* user = userIt->second;

    vector<Product*>& cart = carts_[username];

    vector<Product*> remaining;

    for(size_t i = 0; i < cart.size(); i++){
        Product* product = cart[i];

        if(product->getQty() > 0 && user->getBalance() >= product->getPrice()){
            product->subtractQty(1);

            user->deductAmount(product->getPrice());
        }else{
            remaining.push_back(product);
        }
    }

    cart = remaining;

    return true;
}

void MyDataStore::dump(ostream& ofile){
    ofile << "<products>" << endl;

    for(size_t i =0; i < products_.size(); i++){
        products_[i]->dump(ofile);
    }

    ofile << "</products>" << endl;

    ofile << "<users>" << endl;

    map<string, User*>::iterator it;

    for(it = users_.begin(); it != users_.end(); ++it){
        it->second->dump(ofile);
    }

    ofile << "</users>" << endl;
}

