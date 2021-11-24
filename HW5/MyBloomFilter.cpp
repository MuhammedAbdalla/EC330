// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

/*
 My bloom filter implememntation was going to be a straight implementation of the main class
 because after reading many piazza posts and the HW modifications, it'd be easier to implement
 my member functions straight up. First I had to research was a bit BF was and know that it's like a
 HashTable, but elements will propagate more than once, (k hash functions). then with knowing how 
 false negatives and false positives work, the functionality of a BF was to find data, without searching
 the entire data base, rather look up K,V pairs where k can be (Kn, Vn).

 My implementation of a char BF has 3 hash functions and the length of the BF to be 3 times the input length.
 my hash functions are: the sum of all ascii character values, the cumulative product of ascii values and
 the sum of the squares of the ascii values. I tried to make sure these hash functions have no commonality
 because that'd increase the false positive percent. I chose k = 3 and m = len * 3 because I calculated my error % 
 to be <0.50%

 The rest of the BF implementation was utilizing my hash functions to insert and search. since this was a char based
 BF, I assumed that the indexes of each char element are 32 to 126, therefore I shifted all my hash values by
 the ascii value of ' ', because if my hash1 number was <32 It'd be unprintable. therefore duirng the insert 
 I made sure to add ' ' to the index of the BF to make that specific char visible.



*/


#include <string>
#include "BloomFilter.h"

using namespace std;

// using 3 hashing functions
// one that sums the char ascii values
int hashFunction1(string s, int len) {
    int hash = 0;
    for (char c: s)
        hash += c;
    return hash % len;
}

// the cumulative-product of each char ascii values
int hashFunction2(string s, int len) {
    int hash = 1;
    for (char c: s)
        hash *= c;
    return hash % len;
}

// the sum of the squared char ascii values
int hashFunction3(string s, int len) {
    int hash = 0;
    for (char c: s)
        hash += c*c;
    return hash % len;
}

BloomFilter::BloomFilter(int len) {
    // call the super class
    this -> length = len * 3;
    this -> bf = new char[length];
}

void BloomFilter::insert(string item) {
    int h1 = hashFunction1(item, this->length);
    int h2 = hashFunction2(item, this->length);
    int h3 = hashFunction3(item, this->length);

    // the plus ' ' is because 0 thru 31 ascii values are null and only 32 thru 127 are actual values
    // assuming we ONLY use the usable characters from 32 to 127 we can make each char elem to a ascii value
    // between 32 and 127 and change m to any size

    bf[h1] = (char)(h1 + ' ');
    bf[h2] = (char)(h2 + ' ');
    bf[h3] = (char)(h3 + ' ');
}

bool BloomFilter::exists(string item) {
    int h1 = hashFunction1(item, this->length);
    int h2 = hashFunction2(item, this->length);
    int h3 = hashFunction3(item, this->length);

    //check if the characters at these positions are valid
    bool expression = (
        (char)(h1 + ' ') == bf[h1] && 
        (char)(h2 + ' ') == bf[h2] && 
        (char)(h3 + ' ') == bf[h3]);

    return expression;
}

string BloomFilter::output() {
    string output = "";
    for (int i = 0; i < this -> length; i++)
        output += bf[i];
    return output;
}

