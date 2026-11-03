
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Method 1: Recursive approach
int knapsackRecursive(int n, int capacity,
                      vector<int>& weight,
                      vector<int>& value) {

    // Base condition
    if (n == 0 || capacity == 0)
        return 0;

    // If item weight is greater than capacity
    if (weight[n - 1] > capacity)
        return knapsackRecursive(n - 1, capacity, weight, value);

    // Include item
    int include = value[n - 1] +
                  knapsackRecursive(n - 1,
                  capacity - weight[n - 1], weight, value);

    // Exclude item
    int exclude = knapsackRecursive(n - 1, capacity, weight, value);

    return max(include, exclude);
}

// Method 2: Dynamic Programming (Tabulation)
int knapsackDP(int n, int capacity,
               vector<int>& weight,
               vector<int>& value) {

    vector<vector<int>> dp(n + 1,
                           vector<int>(capacity + 1, 0));

    // Build DP table
    for (int i = 1; i <= n; i++) {

        for (int w = 0; w <= capacity; w++) {

            // Exclude item
            dp[i][w] = dp[i - 1][w];

            // Include item if it fits
            if (weight[i - 1] <= w) {

                dp[i][w] = max(
                    dp[i][w],
                    value[i - 1] +
                    dp[i - 1][w - weight[i - 1]]
                );
            }
        }
    }

    // Find selected items
    cout << "\nSelected items: ";

    int w = capacity;

    for (int i = n; i > 0; i--) {

        if (dp[i][w] != dp[i - 1][w]) {

            cout << i << " ";
            w -= weight[i - 1];
        }
    }

    cout << endl;

    return dp[n][capacity];
}

// Main function
int main() {

    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    if (n < 0) {
        cout << "Invalid number of items.";
        return 0;
    }

    vector<int> weight(n);
    vector<int> value(n);

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++)
        cin >> weight[i];

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++)
        cin >> value[i];

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Invalid capacity.";
        return 0;
    }

    // Recursive result
    int recursiveResult = knapsackRecursive(
        n, capacity, weight, value
    );

    cout << "\nMaximum value using Recursion: "
         << recursiveResult << endl;

    // DP result
    int dpResult = knapsackDP(
        n, capacity, weight, value
    );

    cout << "Maximum value using DP: "
         << dpResult << endl;

    return 0;
}

