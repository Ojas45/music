
import java.util.*;

public class Knapsack {

    static int knapsackRecursive(int n, int capacity,
            int weight[], int value[]) {

        if (n == 0 || capacity == 0)
            return 0;

        if (weight[n - 1] > capacity)
            return knapsackRecursive(n - 1, capacity, weight, value);

        int include = value[n - 1] +
                knapsackRecursive(n - 1,
                        capacity - weight[n - 1], weight, value);

        int exclude = knapsackRecursive(n - 1, capacity, weight, value);

        return Math.max(include, exclude);
    }

    static int knapsackDP(int n, int capacity,
            int weight[], int value[]) {

        int dp[][] = new int[n + 1][capacity + 1];

        for (int i = 1; i <= n; i++) {

            for (int w = 0; w <= capacity; w++) {

                dp[i][w] = dp[i - 1][w];

                if (weight[i - 1] <= w) {

                    dp[i][w] = Math.max(
                            dp[i][w],
                            value[i - 1] + dp[i - 1][w - weight[i - 1]]);
                }
            }
        }

        System.out.print("\nSelected items: ");

        int w = capacity;

        for (int i = n; i > 0; i--) {

            if (dp[i][w] != dp[i - 1][w]) {

                System.out.print(i + " ");
                w -= weight[i - 1];
            }
        }

        System.out.println();

        return dp[n][capacity];
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of items: ");
        int n = sc.nextInt();

        if (n < 0) {
            System.out.println("Invalid number of items.");
            return;
        }

        int weight[] = new int[n];
        int value[] = new int[n];

        System.out.println("Enter weights of items:");
        for (int i = 0; i < n; i++)
            weight[i] = sc.nextInt();

        System.out.println("Enter values of items:");
        for (int i = 0; i < n; i++)
            value[i] = sc.nextInt();

        System.out.print("Enter knapsack capacity: ");
        int capacity = sc.nextInt();

        if (capacity < 0) {
            System.out.println("Invalid capacity.");
            return;
        }

        int recursiveResult = knapsackRecursive(
                n, capacity, weight, value);

        System.out.println("\nMaximum value using Recursion: "
                + recursiveResult);

        int dpResult = knapsackDP(
                n, capacity, weight, value);

        System.out.println("Maximum value using DP: " + dpResult);

        sc.close();
    }
}
