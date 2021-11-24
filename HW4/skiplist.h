// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
//  Copyright 2021 Johnson Yang johnsony@bu.edu
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
    Node<T>* search(T data);                        // search for data, return node <= data (existing node, or location                                            //  where new node should be inserted in the bottom-most list)
    Node<T>* insert(T data);   
                                                    // insert node with data, return pointer if inserted, NULL if error
    void printData();                               // prints skip list data
    void print();                                   // prints skip list with all nodes pointers
    LinkedList<T> *topList;                         // pointer to the top-most list
    LinkedList<T> *botList;
    LinkedList<T> *ll;
    void fixtop();
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


/****** Skip List mplementation ******/
template<class T>
void SkipList<T>::fixtop(){
    ll = new LinkedList<T>(botList->head->data,botList->tail->data);
    ll->head->down = topList->head;
    topList->head->up = ll->head;
    ll->tail->down = topList->tail;
    topList->tail->up = topList->tail;
}


template<class T>
SkipList<T>::SkipList(T minVal, T maxVal){
    LinkedList<T> *myLL = new LinkedList<T>(minVal, maxVal);
    topList = myLL;
    botList = myLL;
    srand(this->randSeed);
}

template<class T>
SkipList<T>::~SkipList(){   //deletes from top to right
    Node<T> *temp;
    Node<T> *next;
    Node<T> *iterator = topList->head;
    while(iterator!= NULL){
        temp = iterator;
        next = iterator;
        while (temp!=NULL){
            next = temp->next;
            delete temp;
            temp = next;
        }
    iterator = iterator->down;
    }

}

template<class T>
Node<T>* SkipList<T>::search(T data){
    Node<T> *iterator = topList->head;
    while (iterator!=NULL){             //iterates through skiplist to return location if found
        if (iterator->data == data){
            return iterator;
        } 
        if (iterator->next->data < data){
            iterator = iterator->next;
        } else {
            iterator = iterator->down;
        }
    }

    iterator = topList->head; //reset iterator
    while (iterator != NULL){          //iteratres through skiplist to return location to put if not found
        if (iterator->data < data && iterator->next->data > data){
            return iterator;
        } 
        if (iterator->next->data < data){
            iterator = iterator->next;
        } else {
            iterator = iterator->down;
        }
    }
}

template<class T>
Node<T>* SkipList<T>::insert(T data){
    Node<T> *location;
    Node<T> *temp = botList->head;
    Node<T> *iterator;
    Node<T> *n ;
    int level = 0, i;
    
    while(temp != NULL){               //first loop to find data == data in LL
        if (temp->data == data){
            return NULL;
        }
        temp = temp->next;
    }
    temp = botList->head;
    location = botList->search(botList->head,data);
    location = botList->insert(location,data);


    while(getRand() == 1){
        temp = botList->head;
        for(i=0;i<level;i++){
            temp = temp->up;
            location = location->up;
        }

        n = new Node<T>(data);
        n->down = location;
        location->up = n;
        
        //cout << temp->up << '\n';

        if (temp->up == NULL){  //if there is no inf / -inf existing it will make it 
            topList = new LinkedList<T>(botList->head->data,botList->tail->data);
            topList->head->down=temp;
            temp->up = topList->head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            topList->tail->down=temp;
            temp->up = topList->tail;
            temp = topList->head;
        } else {
            temp = temp->up;
        }


        //cout << n << '\n' << temp << '\n' << location << '\n' << location->data << '\n';
        while (temp != NULL){
            if (temp->next->data > data && temp->data < data){
                n->next = temp->next;
                n->prev = temp;
                temp->next = n;
                if (n->next != NULL){
                    n->next->prev = n;
                }
                break;
            }   
            temp = temp->next;
        }
        level++;
    }
    
    return location;
}

template<class T>   
void SkipList<T>::printData(){     //prints from top left to bottom right
    fixtop();
    Node<T> *PrintingDown = topList->head->up;
    Node<T> *PrintingRight;
    while (PrintingDown != NULL){
        PrintingRight = PrintingDown;
        while (PrintingRight != NULL){
            PrintingRight->printData();
            PrintingRight = PrintingRight->next;
        }
        
        cout << '\n';
        PrintingDown = PrintingDown->down;
        
    }
    delete ll;
}

template<class T>
void SkipList<T>::print(){  //prints from top left to bottom left
    Node<T> *PrintingDown = topList->head;
    Node<T> *PrintingRight;

    while (PrintingDown != NULL){
        PrintingRight = PrintingDown;
        while (PrintingRight != NULL){
            PrintingRight->print();
            PrintingRight = PrintingRight->next;
        }
        cout << '\n';
        PrintingDown = PrintingDown->down;
    }
    
}

/*** TO BE COMPLETED ***/

/****** Implementation of linked list ******/

//searching for node location or where to place it
template<class T>
Node<T>* LinkedList<T>::search(Node<T>* location, T data){
    Node<T>* temp = location;
    
    while(temp != NULL){                 //if data isn't in LL, find where it should go
        if (temp->data < data && temp->next->data > data){
                return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//insert a node
template<class T>
Node<T>* LinkedList<T>::insert(Node<T>* location, T data){
    Node<T> *temp;
    if (location->next->data < data || location->data > data){  
        return NULL;            //if list isnt sorted, return NULL, else insert node
    }
    temp = new Node<T>(data);
    temp->next = location->next;
    temp->prev = location;
    location->next = temp;
    if (temp->next != NULL){
        temp->next->prev=temp;
    }
    return temp;
}

//constructor
template<class T>
LinkedList<T>::LinkedList(T minVal, T maxVal){
    Node<T> *n;

    n = new Node<T>(minVal);
    head = n;
    tail = n;

    n = new Node<T>(maxVal);
    n->prev = tail;
    tail->next = n;
    tail = n;

    tail->next = NULL;
}

//printing data
template <class T>
void LinkedList<T>::printData()
{
    Node<T>* temp = head;
    while(temp != NULL){
        temp->printData();
        temp = temp->next;
    }
}

//printing everything
template <class T>
void LinkedList<T>::print()
{
    Node<T>* temp = head;
    while(temp != NULL){
        temp->print();
        cout << '\n';
        temp = temp->next;
    }
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




#endif /* SkipList_h */