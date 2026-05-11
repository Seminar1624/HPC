// Compile: g++ -fopenmp assi3.cpp -o assi3
// Run: .\assi3.exe

#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements: ";

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // ---------------- Sequential ----------------

    int seqMin = INT_MAX;
    int seqMax = INT_MIN;
    int seqSum = 0;

    double start = omp_get_wtime();

    for(int i = 0; i < n; i++) {

        if(arr[i] < seqMin)
            seqMin = arr[i];

        if(arr[i] > seqMax)
            seqMax = arr[i];

        seqSum += arr[i];
    }

    double seqAvg = (double)seqSum / n;

    double end = omp_get_wtime();

    cout << "\n----- Sequential Result -----\n";

    cout << "Minimum = " << seqMin << endl;
    cout << "Maximum = " << seqMax << endl;
    cout << "Sum = " << seqSum << endl;
    cout << "Average = " << seqAvg << endl;

    cout << "Time = " << end - start << " sec\n";

    // ---------------- Parallel ----------------

    int parMin = INT_MAX;
    int parMax = INT_MIN;
    int parSum = 0;

    start = omp_get_wtime();

    #pragma omp parallel for reduction(min:parMin) reduction(max:parMax) reduction(+:parSum)
    for(int i = 0; i < n; i++) {

        if(arr[i] < parMin)
            parMin = arr[i];

        if(arr[i] > parMax)
            parMax = arr[i];

        parSum += arr[i];
    }

    double parAvg = (double)parSum / n;

    end = omp_get_wtime();

    cout << "\n----- Parallel Result -----\n";

    cout << "Minimum = " << parMin << endl;
    cout << "Maximum = " << parMax << endl;
    cout << "Sum = " << parSum << endl;
    cout << "Average = " << parAvg << endl;

    cout << "Time = " << end - start << " sec\n";

    return 0;
}