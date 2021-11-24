#ifndef LL_h
#define LL_h

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

class Node {
public:
    Node(int data);                            // constructor
    int data;                                         // node data, doubles as key
    Node *next;                                  // node next pointer
    Node *prev;                                  // node previous pointer                                // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

class LinkedList {
public:
    LinkedList(vector<int> items);                 // constructor: accepts -infinity, +infinity values,
 
    Node* search(Node n, int i);     // search for data starting at location, return node <= data
    Node* insert(Node n, int i);     // insert node with data at new node to be placed directly 
                                                    //  after node with povided location, return new node
    void print();                               // prints linked list data
    Node* head;                                  // head of list
    Node* tail;
};

Node::Node(int data) {
    this -> data = data;
}

LinkedList::LinkedList(vector<int> items) {
    Node *element = this -> head;
    int counter = 0;

    //do {
        element -> next = new Node(items.at(counter));
        //element = element -> next;
        counter++;
    //} while (counter < items.size());
}

#endif /* LinkedList_h */