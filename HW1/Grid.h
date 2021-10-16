// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::to_string;

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

Grid::Grid(int n, int m, int N) {

}