#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(string name, double price, int qty, string genre, string rating) : Product("movie", name, price, qty){
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie()
{
}

set<string> Movie::keywords() const{
    set<string> result = parseStringToWords(convToLower(getName()));

    result.insert(convToLower(genre_));
    
    return result;
}

string Movie::displayString() const{
    stringstream ss;

    ss << getName() << "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << getPrice() << " " << getQty() << " left.:";

    return ss.str();
}

void Movie::dump(ostream& os) const{
    Product::dump(os);
    os << genre_ << endl;
    os << rating_ << endl;
}

