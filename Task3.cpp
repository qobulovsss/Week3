#include <iostream>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int arraySum(const int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + A[i];
    }
    return sum;
}

void bubbleSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

int main() {
    int sizes[] = {1000, 5000, 10000, 50000, 100000};
    int numberOfRuns = 5;

    srand(42);

    cout << fixed << setprecision(3);
    cout << "ARRAY SUM AND BUBBLE SORT TIMING" << endl;
    cout << "Average of 5 runs" << endl << endl;

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];
        int* original = new int[n];

        for (int i = 0; i < n; i++) {
            original[i] = rand() % 1000;
        }

        double sumTotal = 0.0;
        double sortTotal = 0.0;
        int sumCheck = 0;

        for (int run = 0; run < numberOfRuns; run++) {
            high_resolution_clock::time_point start;
            high_resolution_clock::time_point stop;
            duration<double, micro> elapsed;

            start = high_resolution_clock::now();
            sumCheck = arraySum(original, n);
            stop = high_resolution_clock::now();
            elapsed = stop - start;
            sumTotal = sumTotal + elapsed.count();

            int* copy = new int[n];
            for (int i = 0; i < n; i++) {
                copy[i] = original[i];
            }

            start = high_resolution_clock::now();
            bubbleSort(copy, n);
            stop = high_resolution_clock::now();
            elapsed = stop - start;
            sortTotal = sortTotal + elapsed.count();

            delete[] copy;
        }

        cout << "Input size: " << n << endl;
        cout << "Array sum average: "
             << sumTotal / numberOfRuns << " microseconds" << endl;
        cout << "Bubble sort average: "
             << sortTotal / numberOfRuns << " microseconds" << endl;
        cout << "Sum check: " << sumCheck << endl;
        cout << "----------------------------------------" << endl;

        delete[] original;
    }

    cout << endl << "MEMORY ESTIMATE (array storage only)" << endl;

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];
        cout << "n = " << n << ": "
             << (long long)n * sizeof(int) << " bytes" << endl;
    }

    return 0;
}
