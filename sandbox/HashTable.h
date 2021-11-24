#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

class Node {
  Node(const int data);
  int data;
  Node* next;
};


class HashTable {
  // k % m
  HashTable(vector<int>);
  int divHash(int v);
  Node search(int v);
  Node insert(int k, int v);

  int m_size;
  Node m[];
};

Node::Node(int value) {
  m_size = 17;
  Node m[this -> m_size-1];
  this -> data = value;
}

HashTable::HashTable(vector<int> n) {
  for (int i : n) 
    insert(this -> divHash(i), i);
}

int HashTable::divHash(int value) {
  return value % this -> m_size;
}

// Node HashTable::search(int value) {

//   return 
// }

Node HashTable::insert(int key, int value) {
  Node *n = new Node(value);
  m[key] = *n;
  return m[key];
}


#endif /* HashTable.h */