// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
//  LinkedList.h
//  Linked_List
//
//  Copyright Â© Tali Moreshet. All rights reserved.
//
//  This is an implementation of an ordered Linked List class, which is made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

template<class T>
class Node {
public:
    Node(const T& data);                            // constructor
    T data;                                         // node data, doubles as key
    Node<T> *next;                                  // node next pointer
    Node<T> *prev;                                  // node previous pointer
    Node<T> *up;                                    // node above pointer
    Node<T> *down;                                  // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

template <class T>
class LinkedList {
public:
    LinkedList(T minVal, T maxVal);                 // constructor: accepts -infinity, +infinity values,
                                                    //  creates linked list with two corresponding nodes
    ~LinkedList();                                  // destructor
    Node<T>* search(Node<T>* location, T data);     // search for data starting at location, return node <= data
    Node<T>* insert(Node<T>* location, T data);     // insert node with data at new node to be placed directly 
                                                    //  after node with povided location, return new node
    void printData();                               // prints linked list data
    void print();                                   // prints linked list with all nodes pointers
    Node<T>* head;                                  // head of list
};

/********************** From here down is the content of the LinkedList.cpp file: ***********************/

/****** Implementation of Node ******/

// Constructor
template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

// Print node's data value
template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

// Print entire node object content (data value, object's address, and all pointers)
template <class T>
void Node<T>::print()
{
    cout << " * " << data << ": [addr: " << this << " next: " << this->next << " prev: " << this->prev << " up: " << this->up << " down: " << this->down << "]  ";
}


/****** Implementation of linked list ******/

/*** TO BE COMPLETED ***/

template<class T>
LinkedList<T>::LinkedList(T minVal, T maxVal) {
    // inserts both end elements as nodes into list

    // allocate memory for the node<T>*
    this->head = (Node<T>*) malloc(sizeof(Node<T>));

    *(this->head) = Node<T>(minVal);

    this->head->next = (Node<T>*) malloc(sizeof(Node<T>));
    *(this->head->next) = Node<T>(maxVal);

    this->head->next->prev = (Node<T>*) malloc(sizeof(Node<T>));
    this->head->next->prev = this->head;
}

template<class T>
LinkedList<T>::~LinkedList() {
  // Free all elements (memory), deleting linked list
  // Node<T>* element = this->head->next;
    // do {
    //     free(element);
    //     element = element-> next;

    // } while (element != nullptr);
}

int compareFunction(int a, int b) {
  if (a == b)
    return a == b;
  return a > b;
}
int compareFunction(char a, char b) {
  return compareFunction(static_cast<int>(a), static_cast<int>(b));
}

int compareFunction(std::string a, std::string b) {
  return compareFunction(a.at(0),b.at(0));
}

int compareFunction(char* a, char* b) {
  return compareFunction(std::string(a),std::string(b));
}

template<class T>
Node<T>* LinkedList<T>::search(Node<T>* head, T dataSer) {
    // start from the head of the list and find, return if found.
    // return preceeding element if not found

    Node<T>* n = (Node<T>*) malloc(sizeof(Node<T>));
    // do-while used similar to for (int i = 0; element->next != nullptr; i++) 
    // but to count AND iterate
    // theta(n) linear search

    // search can traverse both ways if 'head' is not the start of the LL
    Node<T>* element = head;
     do {

        if (compareFunction(element->data, dataSer))
            return nullptr;
        if (compareFunction(dataSer, element->data) && compareFunction(element->next->data, dataSer))
            return element;

        element = element-> next;

    } while (element != nullptr);

    do {
        if (compareFunction(element->data, dataSer))
            return nullptr;
        if (compareFunction(element->data, dataSer) && compareFunction(dataSer,element->prev->data))
            return element->prev;

        element = element-> prev;

    } while (element != nullptr);

    return element;
}

template<class T>
Node<T>* LinkedList<T>::insert(Node<T>* head, T dataIns) {
    // search will be called first. no duplicates, so if found do not ins
    // if not found preeceeding pointer then ins nextptr making current nextptr the new element
    // returns the locations of the new pointer in the LL
    // INT & DOUBLE: BY INCREASING ORDER
    // CHAR BY ASCII VALUE
    // STRING BY FIRST LETTER - USING CHAR TO COMPARE

  Node<T>* indxNode = search(head, dataIns);
  if (indxNode->data == dataIns) {
    return indxNode;
  } else {
    Node<T> newNode = Node<T>(dataIns);
    // prev-> <-newblock-> <-next

    newNode.prev = indxNode;
    newNode.next = (Node<T>*) malloc(sizeof(Node<T>));
    *(newNode.next) = *(indxNode->next);

    *(indxNode->next) = newNode;
    
  }
  return indxNode;
}

template<class T>
void LinkedList<T>::printData() {
    // prints the contents of the LL, sep by spaces
    Node<T>* element = this->head;
    do {
        cout << element-> data << " ";
        element = element-> next;

    } while (element != nullptr);

    cout << std::endl;
}

template<class T>
void LinkedList<T>::print() {
    // prints everything: node's address and pointers and data
    Node<T>* element = this->head;
    do {
        element->print();
        cout << std::endl;
        element = element-> next;

    } while (element != nullptr);
}

#endif /* LinkedList_h */