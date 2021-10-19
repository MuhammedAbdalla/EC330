// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


int main(){
  int *p, q;
  p = (int*)malloc(sizeof(int));
  *p = 5;
  q = *p;
  free(p);
  std::cout<<q;
  return 0;
}
