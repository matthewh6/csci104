#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5]{0,0,0,0,0};
        std::string s;
        int a = 4;
        unsigned int l = 0;
        if (k.size() != 0) l = k.size()-1;

        
        while(l>=0){
            if(l >= 5){
                s = k.substr(l-5,6);
            }
            else{
                s = k.substr(0,l+1);
            }

            unsigned long long val = 0;
            for(int j = 0; j < s.size(); j++){
                val = val * 36 + letterDigitToNumber(s[j]);
            }
            w[a--] = val;
            if(l > 5){
                l-=6;
            }
            else{break;}
        }
        size_t r = 0;
            for (unsigned int m = 0; m < 5; m++) {
                std::cout << w[m] << std::endl;
                r += rValues[m] * w[m];
            }
        return r;




    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				//if the letter is an uppercase letter
				if (letter >= 97 && letter <= 122) {
                return int(letter) - 97;
                }
                else if (letter >= 65 && letter <= 90) {
                return int(letter) - 65;
                }
                else {
                return int(letter) - 22;
                }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
