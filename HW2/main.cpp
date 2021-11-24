//  Copyright 2021 Muhammed Abdalla muhabda@bu.ed
//
//  main.cpp
//  ec330_hw2
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Problem3.h"

using std::cout;
using std::vector;
using std::map;

int main() {
    int nums[] = {5, 8, 7, 1, 9};
    int length = sizeof(nums)/sizeof(nums[0]);
    
    MaxDecSeq(nums, length);
    return 0;
}

void MaxDecSeq (int *nums, int len) {
  int B[len];

  for (int i = 0; i < len; i++)
    B[i] = 1;

  for (int i = 1; i < len; i++)
    for (int j = 0; j < i; j++)
      if (nums[i] > nums[j] && B[i] <= B[j])
        B[i]++;


  int prev, max;
  prev = max = 0;

  for (int i = 0; i < len; i++) {
    if (B[i] >= max) {
      max = B[i];
      prev = i;
    }
    cout << B[i] << " ";
  }

  vector<int> revSeq,seq;
  
  cout << std::endl;
  revSeq.push_back(nums[prev]);
  for (int i = prev; i > -1; i--)
    if (B[prev] - B[i] == 1) {
      revSeq.push_back(nums[i]);
      prev = i;
    }

  cout << std::endl;
  for (int i = revSeq.size()-1; i > -1; i--){
    cout << revSeq.at(i) << " ";
    seq.push_back(revSeq.at(i));
  }
}