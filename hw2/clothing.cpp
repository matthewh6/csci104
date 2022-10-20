#include <iostream>
#include <string>
#include "clothing.h"
#include "product.h"
#include "util.h"
#include <string>
#include <string.h>
#include <cmath>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
Product(category, name, price, qty){
    size_ = size;
    brand_ = brand;
}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> kwds;
    std::set<std::string> n = parseStringToWords(name_);
    std::set<std::string> b = parseStringToWords(brand_);
    for(typename std::set<std::string>::iterator it = n.begin(); it != n.end(); it++){
        kwds.insert(convToLower(*it));
    }

    for(typename std::set<std::string>::iterator it = b.begin(); it != b.end(); it++){
        kwds.insert(convToLower(*it));
    }

    return kwds;
}



std::string Clothing::displayString() const{
    std::string dstring = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_)+ " " + to_string(qty_) + " left." + "\n";
    return dstring;
}


void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}
