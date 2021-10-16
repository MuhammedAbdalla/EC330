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
    int nums[] = {1, 5, 7, 3, 2, 4};
    int nums2[] = {2, 23, 3, 10, 1, 4, 7};
    int length = sizeof(nums)/sizeof(nums[0]);
    
    MaxDecSeq(nums, length);
    return 0;
}

static vector<int> FinalSequence;

void FindClosetMinDiff(int indx, vector<int> seq, int* nums) {
  if (indx < seq.size()) {
    int min = nums[seq.at(indx)];
    int newStart = 0;
    for (int i = indx + 1; i < seq.size(); i++) {

      if (nums[seq.at(indx)] - nums[seq.at(i)] < min && i < seq.size()-1) {
        cout << nums[seq.at(indx)] << " - " << nums[seq.at(i)] << std::endl;
        min = nums[seq.at(indx)] - nums[seq.at(i)];
        newStart = seq.at(i);
      }
    }
    if (newStart != 0) {
      FinalSequence.push_back(nums[newStart]);
      cout << "INDEX " << newStart << std::endl;
    
      FindClosetMinDiff(newStart, seq, nums);
    }
  } else if (seq.at(indx) < FinalSequence.at(FinalSequence.size() - 1)) {
    FinalSequence.push_back(nums[seq.at(indx)]);
  }
}
void MaxDecSeq (int *nums, int len) {
  vector<vector<int>> sequences;
  // test print using address iterator instead of access by index
  // for(int i = 0; i < len; i++)
  //   cout << *(nums + i) << ", ";
  // cout << std::endl;

  int max[] = {0, 0};

  // calculate the sequences with decreasing integers from each i'th element in the array
  for (int i = 0; i < len - 1; i++) {
    vector<int> seq;

    seq.push_back(i);
    for (int j = i + 1; j < len; j++)
      if (nums[i] - nums[j] > 0)
        seq.push_back(j);

    if (seq.size() > 0)
      sequences.push_back(seq);
  }

  
  // find the sequence with the most decreasing numbers from Vi[0]
  for (int i = 0; i < sequences.size(); i++) {
    vector<int> Vi = sequences.at(i);

    if (Vi.size() > max[0]) {
      max[0] = Vi.size();
      max[1] = i;
    }
  }

  for (int I : sequences.at(max[1]))
    cout << nums[I] << ", ";
  cout << std::endl;
  FinalSequence.push_back(nums[sequences.at(max[1]).at(0)]);
  FindClosetMinDiff(0, sequences.at(max[1]), nums);

  for (int I : FinalSequence)
    cout << I << ", ";
  cout << std::endl;
}