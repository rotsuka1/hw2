#include "book.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(string name, double price, int qty, string isbn, string author) : Product("book", name, price, qty){
    isbn_ = isbn;
    author_ = author;
}

Book::~Book(){
}

set<string> Book::keywords() const{
    set<string> nameWords = parseStringToWords(convToLower(getName()));

    set<string> authorWords = parseStringToWords(convToLower(author_));

    set<string> final = setUnion(nameWords, authorWords);

    final.insert(convToLower(isbn_));

    return final;
}

string Book::displayString() const{
    stringstream ss;

    ss << getName() << "\n";
    ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    ss << getPrice() << " " << getQty() << " left.";

    return ss.str();
}

void Book::dump(ostream& os) const{
    Product::dump(os);
    os << isbn_ << endl;
    os << author_ << endl;
}