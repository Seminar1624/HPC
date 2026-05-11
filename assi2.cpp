// Compile: g++ -fopenmp assi2.cpp -o assi2
// Run: .\assi2.exe


#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// ---------------- MERGE SORT ----------------

// Merge Function
void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp(high - low + 1);

    int i = low, j = mid + 1, k = 0;

    while(i <= mid && j <= high) {
        if(arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i <= mid) temp[k++] = arr[i++];
    while(j <= high) temp[k++] = arr[j++];

    for(int i = low; i <= high; i++)
        arr[i] = temp[i - low];
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int low, int high) {
    if(low < high) {
        int mid = (low + high) / 2;
        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int low, int high) {
    if(low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, low, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, high);
        }

        merge(arr, low, mid, high);
    }
}

// ---------------- BUBBLE SORT ----------------

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    // int x=0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1])
                 swap(arr[j], arr[j + 1]);
                // x=arr[j];
                // arr[j]=arr[j+1];
                // arr[j+1]=x;
        }
    }
}

// Parallel Bubble Sort (Odd-Even Transposition Sort)
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();

    for(int i = 0; i < n; i++) {

        // Even phase
        #pragma omp parallel for
        for(int j = 0; j < n - 1; j += 2) {
            if(arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }

        // Odd phase
        #pragma omp parallel for
        for(int j = 1; j < n - 1; j += 2) {
            if(arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// ---------------- DISPLAY ----------------
void printArray(vector<int> arr) {
    for(int x : arr)
        cout << x << " ";
    cout << endl;
}

// ---------------- MAIN ----------------
int main() {

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements: ";
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> seqMerge = arr;
    vector<int> parMerge = arr;
    vector<int> seqBubble = arr;
    vector<int> parBubble = arr;

    double start, end;

    // 🔷 Sequential Merge Sort
    start = omp_get_wtime();
    sequentialMergeSort(seqMerge, 0, n - 1);
    end = omp_get_wtime();

    cout << "\nSequential Merge Sort: ";
    printArray(seqMerge);
    cout << "Time: " << end - start << " sec\n";

    // 🔷 Parallel Merge Sort
    start = omp_get_wtime();
    parallelMergeSort(parMerge, 0, n - 1);
    end = omp_get_wtime();

    cout << "\nParallel Merge Sort: ";
    printArray(parMerge);
    cout << "Time: " << end - start << " sec\n";

    // 🔷 Sequential Bubble Sort
    start = omp_get_wtime();
    sequentialBubbleSort(seqBubble);
    end = omp_get_wtime();

    cout << "\nSequential Bubble Sort: ";
    printArray(seqBubble);
    cout << "Time: " << end - start << " sec\n";

    // 🔷 Parallel Bubble Sort
    start = omp_get_wtime();
    parallelBubbleSort(parBubble);
    end = omp_get_wtime();

    cout << "\nParallel Bubble Sort: ";
    printArray(parBubble);
    cout << "Time: " << end - start << " sec\n";

    return 0;
}