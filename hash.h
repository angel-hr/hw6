#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <vector>

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
        std::vector<HASH_INDEX_T> W;  //an array of size 5
        std::vector<HASH_INDEX_T> subset;

        if (k.size() <= 24){W.push_back(0);}
        if (k.size() <= 18) {W.push_back(0);}
        if (k.size() <= 12) {W.push_back(0);}
        if (k.size() <= 6) {W.push_back(0);}

        if (k.size() == 0) {W.push_back(0);}
    
        size_t leftover = k.size() % 6;

        if (leftover != 0){
            for (size_t i = 0; i < 6; i++){
                if (i  < 6 - leftover){subset.push_back(0);}
                else{
                    HASH_INDEX_T current = letterDigitToNumber(k[i- 6 + leftover]);
                    subset.push_back(current);
                }
            }
            HASH_INDEX_T value = ((((subset[0] * 36 + subset[1]) * 36 + subset[2]) * 36 + subset[3]) * 36 + subset[4]) * 36 + subset[5];
            W.push_back(value);
            subset.clear();
        }
         
        for (size_t i = leftover; i < k.size(); i++){
            HASH_INDEX_T current = letterDigitToNumber(k[i]);
            subset.push_back(current);
            if (subset.size() % 6 == 0){
                HASH_INDEX_T value = ((((subset[0] * 36 + subset[1]) * 36 + subset[2])
                                    * 36 + subset[3]) * 36 + subset[4]) * 36 + subset[5];  //base conversion
                W.push_back(value);
                subset.clear();
            }                
        } 

        HASH_INDEX_T function = rValues[0] * W[0] + rValues[1] * W[1] + rValues[2] * W[2] + rValues[3] * W[3] + rValues[4] * W[4];
        return function;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T value;
        if (letter >= 48 && letter <= 57){
            value = letter - 48 + 26;
        }
        else {
            letter = tolower(letter);
            value = letter - 97;
        }
        return value;
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
