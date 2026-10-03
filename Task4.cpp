#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main() {
    const int CAP = 100000;
    int sizes[] = {1000, 5000, 10000, 50000, 100000};
    int numberOfRuns = 5;

    int A[CAP];

    cout << fixed << setprecision(3);
    cout << "STATIC ARRAY VS DYNAMIC ARRAY" << endl;
    cout << "Average of 5 runs" << endl << endl;

    cout << "Static array sizeof(A): "
         << sizeof(A) << " bytes" << endl;
    cout << "Size of one int: "
         << sizeof(int) << " bytes" << endl << endl;

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];
        int* B = new int[n];

        double staticTotal = 0.0;
        double dynamicTotal = 0.0;

        for (int run = 0; run < numberOfRuns; run++) {
            high_resolution_clock::time_point start;
            high_resolution_clock::time_point stop;
            duration<double, micro> elapsed;

            start = high_resolution_clock::now();

            for (int i = 0; i < n; i++) {
                A[i] = i;
            }

            stop = high_resolution_clock::now();
            elapsed = stop - start;
            staticTotal = staticTotal + elapsed.count();

            start = high_resolution_clock::now();

            for (int i = 0; i < n; i++) {
                B[i] = i;
            }

            stop = high_resolution_clock::now();
            elapsed = stop - start;
            dynamicTotal = dynamicTotal + elapsed.count();
        }

        cout << "n = " << n << endl;
        cout << "Static fill average: "
             << staticTotal / numberOfRuns
             << " microseconds" << endl;

        cout << "Dynamic fill average: "
             << dynamicTotal / numberOfRuns
             << " microseconds" << endl;

        cout << "Dynamic array bytes: "
             << (long long)n * sizeof(int)
             << " bytes" << endl;

        cout << "----------------------------------------" << endl;

        delete[] B;
    }

    return 0;
}
