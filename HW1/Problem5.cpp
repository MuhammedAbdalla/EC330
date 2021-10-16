// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::stoi;

class Grid {
    private:

    public:
        int r, c;
        // CONSTRUCTORS: Form grid space empty will be marked with ~
        // init n x n
        Grid(int, int);
        // init n x m
        Grid(int, int, int);
};

Grid::Grid(int n, int N){

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            
            if ((j == i || j + 1 == i) && j <= N+1) { // x's placement; i & j dependent
                cout << "x ";
                continue;
            }

            if (N%2 == 0) { // o placements; N dependent
                if (i == N + 2 && j == N + 2) { // single o for even numbers
                    cout << "o ";
                    continue;
                }
            } else {
                if (i == N + 3 && j == N + 3) { // top o
                    cout << "o ";
                    continue;
                }
                if (i == N + 1 && j == N + 3) { // bottom o
                    cout << "o ";
                    continue;
                }
            }

            cout << "~ ";
        }
        cout << std::endl;
    }
    cout << std::endl;
}

int main(int argc, const char* argv[]){
  if (argc < 2) return 1;
  Grid(10, stoi(argv[1])); // Default grid size is 10x10, argv[1] is your N
  return 0;
}
