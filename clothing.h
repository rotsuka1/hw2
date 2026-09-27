#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <string>
#include <set>

using namespace std;

class Clothing: public Product{
    public:
    Clothing(string name, double price, int qty, string size, string brand);
    
    virtual ~Clothing();

    set<string> keywords() const;
    string displayString() const;
    void dump(ostream& os) const;

    private:
    string size_;
    string brand_;
};

#endif