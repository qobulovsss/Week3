#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int linearSearch(const int A[], int n, int key) {
for (int i = 0; i < n; i++) {
if (A[i] == key) {
return i;
}
}
return -1;
}

int main() {
int sizes[] = {1000, 5000, 10000, 50000, 100000};
int numberOfRuns = 5;


cout << fixed << setprecision(3);

cout << "LINEAR SEARCH TIMING" << endl;
cout << "Average of 5 runs" << endl << endl;

for (int s = 0; s < 5; s++) {
    int n = sizes[s];
    int* A = new int[n];

    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }

    int bestKey = A[0];
    int middleKey = A[n / 2];
    int missingKey = -1;

    double bestTotal = 0;
    double middleTotal = 0;
    double worstTotal = 0;

    for (int run = 0; run < numberOfRuns; run++) {
        high_resolution_clock::time_point start;
        high_resolution_clock::time_point stop;
        duration<double, micro> elapsed;

        start = high_resolution_clock::now();
        int result1 = linearSearch(A, n, bestKey);
        stop = high_resolution_clock::now();
        elapsed = stop - start;
        bestTotal = bestTotal + elapsed.count();

        start = high_resolution_clock::now();
        int result2 = linearSearch(A, n, middleKey);
        stop = high_resolution_clock::now();
        elapsed = stop - start;
        middleTotal = middleTotal + elapsed.count();

        start = high_resolution_clock::now();
        int result3 = linearSearch(A, n, missingKey);
        stop = high_resolution_clock::now();
        elapsed = stop - start;
        worstTotal = worstTotal + elapsed.count();
    }

    cout << "Input size: " << n << endl;
    cout << "Best case: "
         << bestTotal / numberOfRuns << " microseconds" << endl;
    cout << "Middle case: "
         << middleTotal / numberOfRuns << " microseconds" << endl;
    cout << "Worst case: "
         << worstTotal / numberOfRuns << " microseconds" << endl;
    cout << "------------------------------" << endl;

    delete[] A;
}

cout << endl;
cout << "MEMORY ESTIMATE" << endl;

for (int s = 0; s < 5; s++) {
    int n = sizes[s];

    cout << "n = " << n
         << ": array storage = "
         << (long long)n * sizeof(int)
         << " bytes" << endl;
}

return 0;


}

