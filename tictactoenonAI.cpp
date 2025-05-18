#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char human, computer;

// Magic square for win logic
int magicSquare[3][3] = {
    {8, 1, 6},
    {3, 5, 7},
    {4, 9, 2}
};

// Print board
void printBoard() {
    cout << "\n-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// Check if a player has won
bool checkWin(char player) {
    int sum;

    // Rows
    for (int i = 0; i < 3; i++) {
        sum = 0;
        for (int j = 0; j < 3; j++)
            if (board[i][j] == player)
                sum += magicSquare[i][j];
        if (sum == 15) return true;
    }

    // Columns
    for (int i = 0; i < 3; i++) {
        sum = 0;
        for (int j = 0; j < 3; j++)
            if (board[j][i] == player)
                sum += magicSquare[j][i];
        if (sum == 15) return true;
    }

    // Diagonals
    sum = 0;
    for (int i = 0; i < 3; i++)
        if (board[i][i] == player)
            sum += magicSquare[i][i];
    if (sum == 15) return true;

    sum = 0;
    for (int i = 0; i < 3; i++)
        if (board[i][2 - i] == player)
            sum += magicSquare[i][2 - i];
    return (sum == 15);
}

// Check if board is full
bool isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

// Get position from magic value
pair<int, int> getPosition(int val) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (magicSquare[i][j] == val)
                return {i, j};
    return {-1, -1};
}

// Check if a move is valid by magic number
bool isValidMove(int val) {
   pair<int, int> pos = getPosition(val);
return (pos.first != -1 && board[pos.first][pos.second] == ' ');

}

// Make computer move using AI
void makeComputerMove() {
    // Try to win
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                if (checkWin(computer)) return;
                board[i][j] = ' ';
            }
        }
    }

    // Try to block
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = human;
                if (checkWin(human)) {
                    board[i][j] = computer;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Play random
    srand(time(0));
    int move;
    do {
        move = rand() % 9 + 1;
    } while (!isValidMove(move));

pair<int, int> pos = getPosition(move);
board[pos.first][pos.second] = computer;

}

int main() {
    cout << "Choose your shape (X or O): ";
    cin >> human;
    human = toupper(human);
    computer = (human == 'X') ? 'O' : 'X';

    bool humanTurn = (human == 'X');
    int row, col;

    while (true) {
        printBoard();

        if (checkWin(human)) {
            cout << "You win!\n";
            break;
        }

        if (checkWin(computer)) {
            cout << "Computer wins!\n";
            break;
        }

        if (isBoardFull()) {
            cout << "It's a tie!\n";
            break;
        }

        if (humanTurn) {
            cout << "Enter your move (row and column 1-3 1-3): ";
            cin >> row >> col;
            row--; col--;

            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                board[row][col] = human;
                humanTurn = false;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        } else {
            makeComputerMove();
            humanTurn = true;
        }
    }

    printBoard();
    return 0;
}
