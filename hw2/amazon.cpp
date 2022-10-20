#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"


using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;
    

    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    map<string, vector<Product*>> cartMap;
    map<string, User*> userMap = ds.getMyUserMap();
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if(cmd == "ADD"){
                string usnme;
                int index;
                ss >> usnme;
                ss >> index;
                //validate username exists in userMap and index is within the size of hits
                if((userMap.find(usnme) != userMap.end()) && (index > -1) && (index < hits.size())){
                    Product* hitp = hits.at(index);
                    //if username exists in cartMap add to the vector
                    if(cartMap.find(usnme) != cartMap.end()){
                        cartMap[usnme].push_back(hitp);
                    }
                    //else, username does not exist in userMap and add a new user to the 
                    //cartMap 
                    else{
                        vector<Product*> p;
                        p.push_back(hitp);
                        cartMap.insert({usnme, p});
                    }

                }
                else{
                    cout << "Invalid request" << endl;
                }

            }



            
            else if(cmd == "VIEWCART"){
                string usnme;
                unsigned int index = 1;
                ss >> usnme;
                if(cartMap.find(usnme) != cartMap.end()){
                    vector<Product*> p;
                    p = cartMap[usnme];
                    
                    for(vector<Product*>::iterator it = p.begin(); it != p.end(); it++){
                        cout << index++ << ") " <<  (*it)->displayString() << endl;
                    }
                }
                else{
                    cout << "Invalid username" << endl;
                }
            }

            else if(cmd == "BUYCART"){
                string usnme;
                ss >> usnme;
                if(cartMap.find(usnme)!=cartMap.end()){
                    vector<Product*> prod = cartMap[usnme];
                    vector<Product*>::iterator  it;
                    User* us = userMap[usnme];
                    for(it=prod.begin(); it!=prod.end();){
                        Product* p = *it;
                        //if the product isn't out of stock and the user has sufficient money
                        if(p->getQty() > 0 && (us->getBalance() >= p->getPrice())){
                            //product qty--
                            p->subtractQty(1);
                            //user funds deducted by price of product
                            us->deductAmount(p->getPrice());
                            it = prod.erase(it);
                        }
                        else{
                        //only increase iterator if an erase didn't happen 
                            it++;
                        }
                    }
                }
                else{
                    cout << "Invalid username" << endl;
                }
            }

	        /* Add support for other commands here */


            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
