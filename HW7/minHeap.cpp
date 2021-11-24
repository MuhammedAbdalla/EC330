// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

void showpq(priority_queue<int, vector<int>, greater<int> > gq) {
    priority_queue<int, vector<int>, greater<int> > g = gq;
    while (!g.empty()) {
        cout << '\t' << g.top();
        g.pop();
    }
    cout << '\n';
}

int main(){
  priority_queue <int, vector<int>, greater<int> > gquiz;
  gquiz.push(10);
  gquiz.push(30);
  gquiz.push(20);
  gquiz.push(5);
  gquiz.push(1);

  cout << "The priority queue gquiz is : ";
  showpq(gquiz);
  return 0;
}
