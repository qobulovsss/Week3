#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

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
    int sizes[] = {100, 500, 1000, 5000, 10000, 100000};

    srand(42);

    cout << fixed << setprecision(3);
    cout << "BUBBLE SORT VS STD::SORT" << endl << endl;

    cout << left << setw(12) << "n"
         << setw(22) << "Bubble sort (ms)"
         << setw(18) << "std::sort (ms)"
         << "Ratio" << endl;

    for (int s = 0; s < 6; s++) {
        int n = sizes[s];
        vector<int> original(n);

        // Generate one random array before timing.
        for (int i = 0; i < n; i++) {
            original[i] = rand();
        }

        vector<int> copy1 = original;
        vector<int> copy2 = original;

        high_resolution_clock::time_point start;
        high_resolution_clock::time_point stop;
        duration<double, milli> elapsed;

        start = high_resolution_clock::now();
        bubbleSort(copy1.data(), n);
        stop = high_resolution_clock::now();
        elapsed = stop - start;
        double bubbleTime = elapsed.count();

        start = high_resolution_clock::now();
        sort(copy2.begin(), copy2.end());
        stop = high_resolution_clock::now();
        elapsed = stop - start;
        double stdTime = elapsed.count();

        double ratio = 0.0;
        if (stdTime > 0.0) {
            ratio = bubbleTime / stdTime;
        }

        cout << left << setw(12) << n
             << setw(22) << bubbleTime
             << setw(18) << stdTime
             << ratio << "x" << endl;
    }

    return 0;
}