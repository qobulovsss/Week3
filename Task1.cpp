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

int main() {
    int sizes[] = {1000, 5000, 10000, 50000, 100000};
    int numberOfRuns = 5;

    srand(42);

    cout << fixed << setprecision(3);
    cout << "Array Sum Timing Results (average of "
         << numberOfRuns << " runs)\n";
    cout << "---------------------------------------------------\n";
    cout << left << setw(15) << "Input size (n)"
         << setw(18) << "Average time (us)"
         << "Sum (check)\n";

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];
        int* A = new int[n];

        for (int i = 0; i < n; i++) {
            A[i] = rand() % 1000;
        }

        long long totalMicroseconds = 0;
        int sumCheck = 0;

        for (int run = 0; run < numberOfRuns; run++) {
            high_resolution_clock::time_point start;
            high_resolution_clock::time_point stop;

            start = high_resolution_clock::now();

            int result = arraySum(A, n);

            stop = high_resolution_clock::now();

            microseconds duration =
                duration_cast<microseconds>(stop - start);

            totalMicroseconds =
                totalMicroseconds + duration.count();

            sumCheck = result;
        }

        double average =
            (double)totalMicroseconds / numberOfRuns;

        cout << left << setw(15) << n
             << setw(18) << average
             << sumCheck << '\n';

        delete[] A;
    }

    cout << "\nMemory estimate (assuming sizeof(int) = "
         << sizeof(int) << " bytes):\n";

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];

        cout << "n = " << n << ": array storage = "
             << (long long)n * sizeof(int)
             << " bytes\n";
    }

    return 0;

    }
