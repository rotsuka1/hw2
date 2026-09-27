#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

Clothing::Clothing(string name, double price, int qty, string size, string brand) : Product("clothing", name, price, qty){
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing()
{
}

set<string> Clothing::keywords() const{
    set<string> nameWords = parseStringToWords(convToLower(getName()));

    set<string> brandWords = parseStringToWords(convToLower(brand_));

    return setUnion(nameWords, brandWords);
}

string Clothing::displayString() const{
    stringstream ss;

    ss << getName() << \n;
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << getPrice() << " " << getQty() << " left.";

    return ss.str();
}

void Clothing::dump(ostream& os) const{
    Product::dump(os);
    os << size_ << endl;
    os << brand_ << endl;
}