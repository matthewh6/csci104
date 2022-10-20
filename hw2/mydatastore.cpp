#include "mydatastore.h"
#include "product.h"
#include "user.h"

MyDataStore::MyDataStore(){

}
MyDataStore::~MyDataStore(){
    // Deleting products from products vector 
    std::vector<Product*>::iterator it;
    for (it = products.begin(); it != products.end(); it++)
    {
        delete *it;
    }

    // Deleting users from userMap: all users (and keys) are deleted
    std::map<std::string, User*>::iterator uit;
    for (uit = userMap.begin(); uit != userMap.end(); uit++)
    {
        delete uit -> second;
    }
}

void MyDataStore::addProduct(Product* p){
    products.push_back(p);
    std::set<std::string> kwds = p->keywords();
    std::set<std::string>::iterator it;
    //iterate through keywords of given input Product 
    for(it = kwds.begin(); it != kwds.end(); it++){
        //if current keyword is found in schMap, 
        //insert the Product* to the set of Product*s (value)
        if(schMap.find(*it) != schMap.end()){
            schMap[*it].insert(p);
        }
        //if current keyword does not exist in schMap, 
        //insert a new key (*it) and value (new set with the Product) into the schMap 
        else{
            std::set<Product*> pr;
            pr.insert(p);
            schMap.insert({*it, pr});
        }
    }
}

void MyDataStore::addUser(User* u){
    users.push_back(u);
    userMap.insert({u->getName(), u});
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    std::set<Product*> searchProds;
    std::vector<Product*> ret;
    //AND search
    if(type == 0){
        for(unsigned int i  = 0; i < terms.size(); i++){
            //if a term is equal to one of the keywords in schMap
            if(schMap.find(terms.at(i)) != schMap.end()){
                //check if searchProds is empty, if it is then make it the value(set) of 
                //the first key(keyword) that matches a term
                if(searchProds.size() == 0){
                    searchProds = schMap[terms.at(i)];
                }
                //if not empty, call setIntersection on searchProds so that it contains 
                //only the Product*s that have include all keywords so far
                else{
                    searchProds = setIntersection(searchProds, schMap[terms.at(i)]);
                }
                    
            }
        } 
    }
    //OR search
    else{
        for(unsigned int i  = 0; i < terms.size(); i++){
            if(schMap.find(terms.at(i)) != schMap.end()){
                //call setUnion which makes searchprods a set with all Product*s
                //that have a keywords
                searchProds = setUnion(searchProds,schMap[terms.at(i)]);
            }
        }
    }
    //convert searchProds to vector<Product*> to return proper type
    ret.assign(searchProds.begin(), searchProds.end());
    return ret;
}


void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << "\n";
    for(unsigned int i = 0; i < products.size(); i++){
        products.at(i)->dump(ofile);
    }
    ofile << "</products>" << "\n" << "<users>" << "\n";
    for(unsigned int i = 0; i < users.size(); i++){
        users.at(i)->dump(ofile);
    }
    ofile << "</users>" << "\n";
}


std::map<std::string, User*> MyDataStore::getMyUserMap(){
    return userMap;
}
    




