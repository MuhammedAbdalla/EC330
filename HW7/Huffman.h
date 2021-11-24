// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
// Copyright 2021 Johnson Yang johnsony@bu.edu
/* 
  Priority Queue data structure help from:
  https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
  https://ece.uwaterloo.ca/~dwharder/aads/STL/priority_queue/
*/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Node {
  string text;
  Node* left;
  Node* right;
  string num;
};

class Element {
public:
  class ElementSort {
  public:
    bool operator() (Element const &, Element const &);
  };
  friend class ElementSort;
  Element(int, string, int);
  int f;
  string s;
  int qC; 
};

class Huffman {

public:
  void buildHuffmanTree(char*, int*, int);
  void printCodes();
  void decodeText(const char*);

private:
  int queueCount;
  priority_queue <Element, vector<Element>, Element::ElementSort > p_q;
  // parent n has children at 2n and 2n+1
  vector<string> textLevels;
  vector<Node*> Branches;
  Node* Tree;
  map<string, string> codes;
};

#endif // HUFFMAN_H