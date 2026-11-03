/*Design n-Queens matrix having first Queen placed. Use backtracking to place remaining
Queens to generate the final n- queen‘s matrix*/

#include <iostream>
#include <vector>
using namespace std;

int n;

bool isSafe(vector<vector<int>>& board, int row, int col) {

    // Column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Left diagonal
    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0;
         i--, j--)
        if (board[i][j])
            return false;

    // Right diagonal
    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n;
         i--, j++)
        if (board[i][j])
            return false;

    return true;
}

bool solve(vector<vector<int>>& board, int row) {

    if (row == n)
        return true;

    for (int col = 0; col < n; col++) {

        if (isSafe(board, row, col)) {

            board[row][col] = 1;

            if (solve(board, row + 1))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

int main() {

    cout << "Enter N: ";
    cin >> n;

    vector<vector<int>> board(
        n, vector<int>(n, 0)
    );

    int firstCol;

    cout << "Enter column for first Queen (1-" << n << "): ";
    cin >> firstCol;

    firstCol--;

    // Place first Queen in first row
    board[0][firstCol] = 1;

    // Place remaining queens
    if (solve(board, 1)) {

        cout << "\nN-Queens Matrix:\n";

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";

            cout << endl;
        }
    }
    else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}