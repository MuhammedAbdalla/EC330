//
//  main.cpp
//  Linked_List
//
//  Copyright Â© Tali Moreshet. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include "LinkedList.h"

int main(int argc, const char * argv[]) {

  /* Uncomment */
  LinkedList<char> *myLL = new LinkedList<char>(CHAR_MIN, CHAR_MAX);
  Node<char> *newNodeLoc;

  newNodeLoc = myLL->search(myLL->head, 'a');
  myLL->insert(newNodeLoc, 'a');
  newNodeLoc = myLL->search(myLL->head, '1');
  myLL->insert(newNodeLoc, '1');
  newNodeLoc = myLL->search(myLL->head, 'g');
  myLL->insert(newNodeLoc, 'g');

  cout << "Linked list data: \n";
  myLL->printData();

  cout << "\nLinked List entire content: \n";
  myLL->print();
  delete myLL;
    
  return 0;
}