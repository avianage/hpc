#include <iostream>
#include <omp.h>
#include <algorithm>

using namespace std;

void bubble(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1])
                swap(array[j], array[j + 1]);
        }
    }
}

void pBubble(int array[], int n) {
    for (int i = 0; i < n; ++i) {
        #pragma omp for
        for (int j = 1; j < n; j += 2) {
            if (array[j] < array[j - 1]) {
                swap(array[j], array[j - 1]);
            }
        }

        #pragma omp barrier

        #pragma omp for
        for (int j = 2; j < n; j += 2) {
            if (array[j] < array[j - 1]) {
                swap(array[j], array[j - 1]);
            }
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}

int main() {
    int n = 10000;
    int arr[n];
    double start_time, end_time;

    for (int i = 0, j = n; i < n; i++, j--)
        arr[i] = j;

    start_time = omp_get_wtime();
    bubble(arr, n);
    end_time = omp_get_wtime();
    cout << "\nSequential Bubble Sort took: " << end_time - start_time << " seconds.\n";

    for (int i = 0, j = n; i < n; i++, j--)
        arr[i] = j;

    start_time = omp_get_wtime();
    pBubble(arr, n);
    end_time = omp_get_wtime();
    cout << "\nParallel Bubble Sort took: " << end_time - start_time << " seconds.\n";
}