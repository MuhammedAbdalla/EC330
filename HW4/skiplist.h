// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
// Copyright 2021 Johnson Yang johnsony@bu.edu
//  SkipList.h
//  Skip_List
//
//  Copyright Â© Tali Moreshet. All rights reserved.
//
//
//  This is an implementation of a Skip List class, consisting of Linked Lists, which are made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef SkipList_h
#define SkipList_h

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

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
    Node<T>* tail;
};

template <class T>
class SkipList {
public:
    SkipList(T minVal, T maxVal);                   // constructor: accepts -infinity, +infinity values,
                                                    //  creates skip list with top-level only
    ~SkipList();                                    // destructor
    Node<T>* search(T data);                        // search for data, return node <= data (existing node, or location
                                                    //  where new node should be inserted in the bottom-most list)
    Node<T>* insert(T data);                        // insert node with data, return pointer if inserted, NULL if error
    void printData();                               // prints skip list data
    void print();                                   // prints skip list with all nodes pointers
    LinkedList<T> *topList;                         // pointer to the top-most list
    int randSeed = 330;                             // to be used as seed for the getRand() function
};

//returns 0 or 1 with a 50% chance 
//When it returns 1, insert the node to next level of the skiplist
int getRand(){
    return rand()%2;
}

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

    this->tail = (Node<T>*) malloc(sizeof(Node<T>));
    *(this->tail) = *(this -> head -> next);
}

//destructor
template <class T>
LinkedList<T>::~LinkedList(){
    Node<T>* temp = head;
    Node<T>* next;
    while (temp!=NULL){
        next = temp->next;
        delete temp;
        temp = next;
    }
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

     if (compareFunction(element->data, dataSer))
            return nullptr;
     do {
        if (compareFunction(dataSer, element->data) && compareFunction(element->next->data, dataSer))
            return element;

        element = element-> next;

    } while (element != nullptr);

    do {
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
  return indxNode->next;
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


/****** Skip List Implementation ******/

template<class T>
SkipList<T>::SkipList(T minVal, T maxVal) {
    srand(this->randSeed);
    topList = new LinkedList<T>(minVal,maxVal);
}

template<class T>
SkipList<T>::~SkipList() {
    // when init take the existing linked list put at the bottom
    //create a new LL with maximally increasing elements place above LL
        //match same elements with same elements, -inf to -inf inf to inf
}

template<class T>
Node<T>* SkipList<T>::search(T data) {
    // start from topList node 1, (-inf) 
    // finding value is always > -inf so go right else go down then right until fines value
    // when value0 is less than value V then look down-left, else look right
    Node<T>* element = this -> topList -> head;

    do {
        if (data > element->data && data < element->next->data) {
            if (element->down != nullptr){
                element = element -> down;
                //cout<<"down"<<std::endl;
                continue;
            } else {
                //cout<<"found"<<std::endl;
                return element; // pos of the element prev to insert
            }
        } else {
            element = element -> next;
            //cout<<"next"<<std::endl;
        }
    } while (element != nullptr);

    return nullptr;
}

template<class T>
Node<T>* SkipList<T>::insert(T data) {
    // insert at topList
    // then recreate skipLists

    Node<T> *newNode, *indxNode;
    indxNode = this -> search(data);

    if (indxNode != nullptr) {
        // insert element at the bottom of the list

        newNode = this -> topList -> insert(indxNode, data);
        int flip = 0;
        //will index upwards until flip is 0 or has index until the top level list
        do { 
            Node<T>* e = indxNode;

            //go to -inf to go up
            while (e->prev != nullptr) {
                e = e->prev;
            }
            //index upwards
            indxNode = e->up;
           
            if (indxNode == nullptr)
                break;

            newNode -> up = this -> topList -> insert(indxNode, data);
            newNode -> up -> down = newNode;
            // flip the coin
            flip = getRand();
        } while (flip == 1);

        // this case is if the value has stacked to the top list. Adds the blank list.
        if (this->topList->head->next->data != this->topList->tail->data) {
            
            LinkedList<T> *newTopList = new LinkedList<T>(this -> topList->head->data, this -> topList->tail->data);

            //now stack new topList ontop
            newTopList->head->down = this->topList->head;
            newTopList->tail->down = this->topList->tail;
            this->topList->head->up = newTopList->head;
            this->topList->tail->up = newTopList->tail;

            *(this -> topList) = *newTopList;
        }
    }
    return newNode;
}

template<class T>
void SkipList<T>::printData(){
    Node<T>* rowElem = this -> topList -> head;
    Node<T>* colElem = this -> topList -> head;

    do {
        do {
            rowElem -> printData();
            rowElem = rowElem -> next;
        } while (rowElem != nullptr);
        colElem = colElem -> down;
        rowElem = colElem;
        cout<<std::endl;
    } while (colElem != nullptr);
}

template<class T>
void SkipList<T>::print() {
    Node<T>* rowElem = this -> topList -> head;
    Node<T>* colElem = this -> topList -> head;

    do {
        do {
            rowElem -> print();
            rowElem = rowElem -> next;
        } while (rowElem != nullptr);
        colElem = colElem -> down;
        rowElem = colElem;
        cout<<std::endl;
    } while (colElem != nullptr);
}


#endif /* SkipList_h */