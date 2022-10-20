#include <iostream>
#include <string>
#include <cmath>
#include "movie.h"
#include "product.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
Product(category, name, price_, qty){
    genre_ = genre;
    rating_ = rating;
}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> kwds;
    std::set<std::string> n = parseStringToWords(name_);
    for(typename std::set<std::string>::iterator it = n.begin(); it != n.end(); it++){
        kwds.insert(convToLower(*it));
    }

    kwds.insert(convToLower(genre_));

    return kwds;
}



std::string Movie::displayString() const{
    std::string dstring = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_)+ " " + to_string(qty_) + " left." + "\n";
    return dstring;
}


void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
}
