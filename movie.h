#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <string>
#include <set>

using namespace std;

class Movie: public Product{
    public:
    Movie(string name, double price, int qty, string genre, string rating);

    virtual ~Movie();

    set<string> keywords() const;
    string displayString() const;
    void dump(ostream& os) const;

    private:
    string genre_;
    string rating_;
};

#endif