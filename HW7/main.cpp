//
//  main.cpp
//  Huffman
//
//  Created by Tali Moreshet
//

#include <iostream>
#include <fstream>
#include "Huffman.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // char characters[] = {'e', 'l', 'o', 'g'};
    // int freq[] = {1, 1, 2, 3};
    // int size = sizeof(characters) / sizeof(characters[0]);
    
    char characters[] = {'b', 'l', 'o', 'u', 't', 'g', 'e', 's'};
    int freq[] = {1, 2, 2, 1, 1, 3, 1, 1};
    int size = sizeof(characters) / sizeof(characters[0]);

    Huffman huffman;
    
    huffman.buildHuffmanTree(characters, freq, size);
    huffman.printCodes();
    
    if (argc != 2)
        cout << "Please supply a file name with Huffman encoded text\n";
    huffman.decodeText(argv[1]);
    return 0;
}

//bloutgoggles