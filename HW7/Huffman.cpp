// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
// Copyright 2021 Johnson Yang johnsony@bu.edu
/* 
  Priority Queue data structure help from:
  https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
  https://ece.uwaterloo.ca/~dwharder/aads/STL/priority_queue/
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "Huffman.h"

using namespace std;

Element::Element(int f, string s, int qC) {
  this -> f = f;
  this -> s = s;
  this -> qC = qC;
}

// operator class for internal queue comparison method
bool Element::ElementSort::operator() (Element const &a, Element const &b) {
  return a.f > b.f || (a.f == b.f && a.qC > b.qC);
}

// Travserses the tree to assign the compression numbers
map<string, string> treeTraverse(Node* root, string num) {
  static map<string, string> c;
  if (root -> right == NULL || root -> left == NULL) {
    root -> num = num;
    c.emplace(root -> num, root -> text);
  } else {
    //traverse to the right
    treeTraverse(root->left, num + "0");
    treeTraverse(root->right, num + "1");
  }
  return c;
}

// void Huffman buildHuffmanTree
void Huffman::buildHuffmanTree(char* c, int* f, int size) {
  this -> queueCount = 0;
  string compressedText, str;

  for (int i = 0; i < size; i++) {
    str = c[i];
    Element e(f[i], str, this -> queueCount);
    this -> p_q.push(e);
    this -> queueCount++;
  }
  Node* e;


  while (!(this -> p_q.empty()) && (this -> p_q.size() > 1)) {
      Element E1 = p_q.top();
      p_q.pop();

      Element E2 = p_q.top();
      p_q.pop();
      compressedText = E1.s + E2.s;

      e = new Node();
      e -> text = compressedText;
      e -> left = new Node();
      e -> left -> text = E1.s;
      e -> right = new Node();
      e -> right -> text = E2.s;

      this -> textLevels.emplace_back(compressedText);
      this -> Branches.emplace_back(e);

      Element eNew(E1.f + E2.f, compressedText, this -> queueCount); // new tree containing T1 & T2
      p_q.push(eNew); // readd tree to Priority Queue

      //cout << compressedText << " F: " << E1.f + E2.f << '\n' << endl;
      this -> queueCount++;
    }

    // for (Node* N : this->Branches) {
    //   cout << N -> text << " ";
    //   cout << N -> left -> text << " ";
    //   cout << N -> right -> text << endl;
    // }

    this -> Tree = Branches.back();
    while (Branches.size()>0) {
      for (Node* N : this->Branches) {
        if (N -> text == Branches.back() -> left -> text)
          *(Branches.back() -> left) = *N;

        if (N -> text == Branches.back() -> right -> text)
          *(Branches.back() -> right) = *N;
      }
      Branches.pop_back();
    }

    codes = treeTraverse(Tree, "");
}

// prints the huffman codes
void Huffman::printCodes() {
  cout << "Huffman Code\tCharacter" << endl;
  cout << "---------------------------" << endl;
  string num = "";

  for (auto mapC = this->codes.begin(); mapC != this->codes.end(); ++mapC) {
    cout << mapC->first << "\t\t\t" << mapC->second << '\n';
  }
}

// decodes the compressed bitstream of the buffman text
void Huffman::decodeText(const char* text) {
  ifstream textFile(text);
  string line;
  cout << "The decoded text is: ";
  if (textFile.is_open()){
    while (getline(textFile, line)) {
      int space_char = line.find(' ');
      int counter = 0;
      if (space_char == -1) {
        while (counter <= line.size()) {
          auto S = this -> codes.find(line.substr(0,counter));
          //cout << '\n' << line.substr(0,counter) << ": ";
          if (S != codes.end()) {
            cout << S->second;
            line = line.substr(counter);
            counter = 0;
          }
          counter++;
        }
       } else {
        // if a sentence was used in a line implementation
        //decodeText(line.substr(0,space_char));
        line = line.substr(space_char);
      } 
    }
    cout << '\n';
  }
  textFile.close();
}
