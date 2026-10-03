#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

int main() {
    int sizes[] = {1000, 5000, 10000, 50000, 100000};
    int numberOfRuns = 5;

    cout << fixed << setprecision(3);
    cout << "VECTOR PUSH_BACK VS RESERVE" << endl;
    cout << "Average of 5 runs" << endl << endl;

    for (int s = 0; s < 5; s++) {
        int n = sizes[s];

        double pushBackTotal = 0.0;
        double reserveTotal = 0.0;

        cout << "Input size: " << n << endl;
        cout << "Capacity changes without reserve:" << endl;

        vector<int> observed;
        size_t previousCapacity = observed.capacity();

        for (int i = 0; i < n; i++) {
            observed.push_back(i);

            if (observed.capacity() != previousCapacity) {
                cout << "  size = " << observed.size()
                     << ", capacity = " << observed.capacity() << endl;
                previousCapacity = observed.capacity();
            }
        }

        for (int run = 0; run < numberOfRuns; run++) {
            vector<int> v;
            high_resolution_clock::time_point start;
            high_resolution_clock::time_point stop;
            duration<double, micro> elapsed;

            start = high_resolution_clock::now();

            for (int i = 0; i < n; i++) {
                v.push_back(i);
            }

            stop = high_resolution_clock::now();
            elapsed = stop - start;
            pushBackTotal = pushBackTotal + elapsed.count();

            vector<int> w;

            w.reserve(n);

            start = high_resolution_clock::now();

            for (int i = 0; i < n; i++) {
                w.push_back(i);
            }

            stop = high_resolution_clock::now();
            elapsed = stop - start;
            reserveTotal = reserveTotal + elapsed.count();
        }

        cout << "push_back only average: "
             << pushBackTotal / numberOfRuns
             << " microseconds" << endl;

        cout << "reserve + push_back average (insertion loop): "
             << reserveTotal / numberOfRuns
             << " microseconds" << endl;

        cout << "----------------------------------------" << endl;
    }

    return 0;
}

