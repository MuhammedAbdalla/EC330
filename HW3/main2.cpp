//
//  main.cpp
//  Linked_List
//
//  Copyright Â© Tali Moreshet. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include <vector>
#include "LL.h"

using std::vector;

int main(int argc, const char * argv[]) {
  vector<int> num1 = {1, 2, 3, 5, 7, 10, 20};
  vector<int> num2 = {5, 7, 9, 10, 23, 24, 39};

  /* Uncomment */
  LinkedList *myLL1 = new LinkedList(num1);
  LinkedList *myLL2 = new LinkedList(num2);



  cout << "\nLinked List entire contents: \n";
  // myLL1->print();
  // myLL2->print();    
  return 0;
}