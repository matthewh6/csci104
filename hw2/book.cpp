#include "book.h"
#include "util.h"
#include <cmath>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
Product(category, name, price, qty){
    isbn_ = isbn;
    author_ = author;
}

Book::~Book() {}

std::set<std::string> Book::keywords() const{
    std::set<std::string> kwds;
    std::set<std::string> n = parseStringToWords(name_);
    std::set<std::string> a = parseStringToWords(author_);
    for(std::set<std::string>::iterator it = n.begin(); it != n.end(); it++){
        kwds.insert(convToLower(*it));
    }

    for(std::set<std::string>::iterator it = a.begin(); it != a.end(); it++){
        kwds.insert(convToLower(*it));
    }

    kwds.insert(convToLower(isbn_));

    return kwds;
}



std::string Book::displayString() const{
    std::string dstring = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_)+ " " + to_string(qty_) + " left." + "\n";
    return dstring;
}


void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
}
