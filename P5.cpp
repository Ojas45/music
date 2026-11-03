/*Write a program for analysis of quick sort by using deterministic and randomized
variant.*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

int partitionDeterministic(vector<int>& arr, int low, int high) {

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSortDeterministic(
    vector<int>& arr,
    int low,
    int high
) {

    if (low < high) {

        int pivotIndex =
            partitionDeterministic(arr, low, high);

        quickSortDeterministic(
            arr,
            low,
            pivotIndex - 1
        );

        quickSortDeterministic(
            arr,
            pivotIndex + 1,
            high
        );
    }
}


// --------------------------------------------------
// Randomized Quick Sort
// Pivot = randomly selected element
// --------------------------------------------------

int partitionRandomized(
    vector<int>& arr,
    int low,
    int high
) {

    int randomIndex =
        low + rand() % (high - low + 1);

    // Move random pivot to last position
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSortRandomized(
    vector<int>& arr,
    int low,
    int high
) {

    if (low < high) {

        int pivotIndex =
            partitionRandomized(arr, low, high);

        quickSortRandomized(
            arr,
            low,
            pivotIndex - 1
        );

        quickSortRandomized(
            arr,
            pivotIndex + 1,
            high
        );
    }
}


// --------------------------------------------------
// Display Array
// --------------------------------------------------

void displayArray(const vector<int>& arr) {

    for (int x : arr)
        cout << x << " ";

    cout << endl;
}


// --------------------------------------------------
// Main
// --------------------------------------------------

int main() {

    srand(time(0));

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    // Create two copies
    vector<int> deterministic = arr;
    vector<int> randomized = arr;

    // ----------------------------------------------
    // Deterministic Quick Sort
    // ----------------------------------------------

    auto start1 = high_resolution_clock::now();

    quickSortDeterministic(
        deterministic,
        0,
        n - 1
    );

    auto end1 = high_resolution_clock::now();

    auto time1 =
        duration_cast<microseconds>(
            end1 - start1
        ).count();

    // ----------------------------------------------
    // Randomized Quick Sort
    // ----------------------------------------------

    auto start2 = high_resolution_clock::now();

    quickSortRandomized(
        randomized,
        0,
        n - 1
    );

    auto end2 = high_resolution_clock::now();

    auto time2 =
        duration_cast<microseconds>(
            end2 - start2
        ).count();

    // ----------------------------------------------
    // Display Results
    // ----------------------------------------------

    cout << "\nSorted Array using Deterministic Quick Sort:\n";
    displayArray(deterministic);

    cout << "\nSorted Array using Randomized Quick Sort:\n";
    displayArray(randomized);

    cout << "\nExecution Time Analysis:\n";

    cout << "Deterministic Quick Sort: "
         << time1 << " microseconds" << endl;

    cout << "Randomized Quick Sort: "
         << time2 << " microseconds" << endl;

    return 0;
}
