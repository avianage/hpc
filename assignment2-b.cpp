// Assignment 2
// Write a program to implement Parallel Bubble Sort and Merge sort using OpenMP. Use 
// existing algorithms and measure the performance of sequential and parallel algorithms. 
// b. Merge Sort

#include <iostream>
#include <algorithm>
#include <omp.h>

using namespace std;

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[low + i];

    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void parallelMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }

        merge(arr, low, mid, high);
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int n = 1000000;
    int arr[n];
    double start_time, end_time;

    omp_set_num_threads(4); // Set to the number of physical cores available

    for (int i = 0, j = n; i < n; i++, j--)
        arr[i] = j;

    start_time = omp_get_wtime();
    mergeSort(arr, 0, n - 1);
    end_time = omp_get_wtime();
    cout << "\nTime taken by the sequential Merge Sort algorithm: " << end_time - start_time << " seconds\n";

    for (int i = 0, j = n; i < n; i++, j--)
        arr[i] = j;

    start_time = omp_get_wtime();
    parallelMergeSort(arr, 0, n - 1);
    end_time = omp_get_wtime();
    cout << "\nTime taken by the parallel Merge Sort Algorithm: " << end_time - start_time << " seconds\n";

    return 0;
}