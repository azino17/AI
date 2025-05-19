#include <iostream>
#include <vector>
using namespace std;


void printBoard(const vector<int>& queens, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (queens[i] == j)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}


bool isSafe(const vector<int>& queens, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (queens[i] == col ||                      
            queens[i] - i == col - row ||            
            queens[i] + i == col + row)              
            return false;
    }
    return true;
}

bool solveNQueens(vector<int>& queens, int row, int N) {
    if (row == N) {
        return true; // Successfully placed all queens
    }

    for (int col = 0; col < N; ++col) {
        cout << "Trying to place queen at row " << row << ", column " << col << "...\n";
        
        if (isSafe(queens, row, col)) {
            queens[row] = col;
            cout << "Placed queen at row " << row << ", column " << col << "\n";
            printBoard(queens, N);
            cout << "---------------------\n";

            if (solveNQueens(queens, row + 1, N))
                return true;

            // Backtrack
            cout << "Backtracking from row " << row << ", column " << col << "\n";
            queens[row] = -1;
        } else {
            cout << "Cannot place queen at row " << row << ", column " << col << " (unsafe)\n";
        }
    }

    return false; // No valid position found in this row
}


int main() {
    int N;
    cout << "Enter the value of N: ";
    cin >> N;

    vector<int> queens(N, -1); 

    if (solveNQueens(queens, 0, N)) {
        cout << "\nOne solution for " << N << "-Queens problem:\n";
        printBoard(queens, N);
    } else {
        cout << "No solution exists for N = " << N << "\n";
    }

    return 0;
}