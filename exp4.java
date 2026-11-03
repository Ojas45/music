import java.util.*;

public class exp4 {
    static int n;

    public static boolean isSafe(int board[][], int row, int col) {
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 1) {
                return false;
            }
        }

        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) {
                return false;
            }

        }

        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {

            if (board[i][j] == 1) {
                return false;
            }
        }

        return true;
    }

    public static boolean solve(int board[][], int row) {
        if (row == n) {
            return true;
        }

        for (int col = 0; col < n; col++) {

            if (isSafe(board, row, col)) {
                board[row][col] = 1;

                if (solve(board, row + 1)) {
                    return true;
                }

                board[row][col] = 0;

            }

        }
        return false;

    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the size of the chessboard: ");
        n = sc.nextInt();

        int board[][] = new int[n][n];
        System.out.println("Enter the column number to insert the queen: ");
        int col = sc.nextInt();

        board[0][col - 1] = 1;

        if (solve(board, 1)) {
            System.out.println("N-Queens Matrix: ");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    System.out.print(board[i][j] + " ");
                }
                System.out.println();
            }

        } else {
            System.out.println("No solution exists.");
        }

    }

}