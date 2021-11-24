/*
Name & Collaborator Name: Johnson Yang & Muhammed Abdalla
U44370020 & U45097807

BU ID used for Problem3: U44370020

main.cpp output:
Longest Word Length: 124
Valid Passwords: 18250736
Number of valid dictionary words: ??

Explanation:
a) Everytime there is a whitespace or newline, the count resets to 0, then for each character following the 
white space or newline, count would increase by 1. Before reseting the count, I compare the count of each 
word to the max count, if the count of a certain word is greater than max count it replaces max count. 

b) Part b builds off the framework of part a, but I just add boolean statements, and if there exists 
a lower, an upper, between 8 and 20 characters and at least one digit, all the boolean statements will be true. If 
all the boolean statements are true, the count would increment by 1, indicating that it is a possible password. 

c) My method to c is a bruteforce method. I made a vector of words from dictionary that doesn't include c,s, or b 
(BUID ending in 0 so choco snickers bar aka c,s, & b). Then for each of those letters, they go through the data file
incrementing count by 1 each time a word from dictionary vector is found in the data file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int fourA(){
    string one_line;
    int i = 0, j = 0, max = 0, count = 0;
    bool addcount = true;
    char c;
    ifstream file("BigData.txt");
    if (file.is_open()){
        while(getline(file, one_line)){
            while (one_line[i]){
                c = one_line[i];
                if (isspace(c)){
                    if (count > max){
                        max = count;
                    }
                    count = 0;
                } else {
                    count++;
                }
                i++;
            }
            i=0;
            if (count > max){
                max = count;
            }
            count = 0;
        }
        file.close();
    } else {
        return 0;
    }
    return max;
}
int fourB(){
    string one_line;
    int i = 0, count = 0, pwCount = 0;
    bool oneLower = false, oneUpper = false, oneDigit = false, charLim = false;
    char c;
    ifstream file("BigData.txt");
    if (file.is_open()){
        while(getline(file, one_line)){
            while (one_line[i]){
                c = one_line[i];
                if (isspace(c)){
                    if (oneLower && oneUpper && oneDigit && charLim) pwCount++;
                    count = 0;
                    oneLower = false;
                    oneUpper = false;
                    oneDigit = false;
                    charLim = false;
                } else {
                    count++;
                    if (isupper(c)) oneUpper = true;
                    if (islower(c)) oneLower = true;
                    if (isdigit(c)) oneDigit = true;
                    if (count >= 8 && count <= 20){
                        charLim = true;
                    } else {
                        charLim = false;
                    }
                }
                i++;
            }
            if (oneLower && oneUpper && oneDigit && charLim){
                pwCount++;
                count = 0;
                oneLower = false;
                oneUpper = false;
                oneDigit = false;
                charLim = false;
            }
            i=0;
            count = 0;
        }
        file.close();
    } else {
        return 0;
    }
    return pwCount;
}

int fourC(){
    string s1,s2;
    int count = 0, i;
    std::string::size_type pos=0;
    ifstream file("dictionary.txt");
    ifstream file2("BigData.txt");
    vector<string> v1;
    bool cExist, sExist, bExist;

    if (file.is_open()){
        while(getline(file,s1)){
            cExist = false;
            sExist = false;
            bExist = false;
            for (auto e:s1){
                if ( e =='c' || e == 'C'){
                    cExist = true;
                }
                if ( e == 's' || e == 'S'){
                    sExist = true;
                }
                if ( e == 'b' || e == 'B'){
                    bExist = true;
                }
            }

            if (cExist && sExist && bExist){
                cExist = false;
                sExist = false;
                bExist = false;
            } else {
                v1.push_back(s1);
            }
        }
    }
    file.close();

    if (file2.is_open()){
        while (getline(file2,s2)){
            for (auto e:v1){
                pos = 0;
                while ((pos = s2.find(e, pos)) != std::string::npos){
                    count++;
                    pos += e.length();
                    //cout << e << '\n';
                }
            }
        }
    }
    file2.close();

    return count;
}