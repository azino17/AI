#include <stdio.h>

#define HUMAN 'X'
#define COMPUTER 'O'
#define EMPTY ' '

char board[3][3] = {
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY}
};

// Function to print the board
void printBoard() {
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%c | ", board[i][j]);
        }
        printf("\n-------------\n");
    }
}

// Check if any empty cells are left
int isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return 1;
    return 0;
}

// Evaluate the board
int evaluate() {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == COMPUTER)
                return +10;
            else if (board[row][0] == HUMAN)
                return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == COMPUTER)
                return +10;
            else if (board[0][col] == HUMAN)
                return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER)
            return +10;
        else if (board[0][0] == HUMAN)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER)
            return +10;
        else if (board[0][2] == HUMAN)
            return -10;
    }

    return 0;
}

// Minimax algorithm
int minimax(int depth, int isMax) {
    int score = evaluate();
    if (score == 10 || score == -10)
        return score;
    if (!isMovesLeft())
        return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    int val = minimax(depth + 1, 0);
                    best = (best > val) ? best : val;
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    int val = minimax(depth + 1, 1);
                    best = (best < val) ? best : val;
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Find the best move for the computer
void findBestMove(int bestMove[2]) {
    int bestVal = -1000;
    bestMove[0] = -1;
    bestMove[1] = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = minimax(0, 0);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove[0] = i;
                    bestMove[1] = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

int isGameOver() {
    return evaluate() != 0 || !isMovesLeft();
}

// Main function
int main() {
    printf("Welcome to Tic-Tac-Toe!\n");
    printBoard();

    while (!isGameOver()) {
        // Human move
        int row, col;
        printf("Your turn! Enter row and column (1-3): ");
        scanf("%d %d", &row, &col);
        row--; col--;

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row][col] = HUMAN;
        printBoard();

        if (isGameOver())
            break;

        // Computer move
        printf("Computer's turn:\n");
        int bestMove[2];
        findBestMove(bestMove);
        board[bestMove[0]][bestMove[1]] = COMPUTER;
        printBoard();
    }

    int score = evaluate();
    if (score == 10) {
        printf("Computer wins!\n");
    } else if (score == -10) {
        printf("You win!\n");
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}
