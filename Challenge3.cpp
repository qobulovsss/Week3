#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

long long fibRecursive(int n) {
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

unsigned long long fibIterative(int n) {
    unsigned long long a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        unsigned long long next = a + b;
        a = b;
        b = next;
    }
    return a;
}

int main() {
    // Recursive vs iterative on small n
    int small[4] = {20, 25, 30, 35};
    for (int i = 0; i < 4; i++) {
        int n = small[i];

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        long long r = fibRecursive(n);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        unsigned long long it = fibIterative(n);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();

        duration<double, milli> recTime = t2 - t1;
        duration<double, micro> iterTime = t3 - t2;

        cout << "n=" << n
             << " | recursive: " << recTime.count() << " ms"
             << " | iterative: " << iterTime.count() << " us"
             << " | results: " << r << " / " << it << endl;
    }

    int large[2] = {1000, 1000000};
    for (int i = 0; i < 2; i++) {
        int n = large[i];

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        unsigned long long it = fibIterative(n);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double, micro> iterTime = t2 - t1;

        cout << "n=" << n
             << " | iterative: " << iterTime.count() << " us"
             << " | result (overflowed): " << it << endl;
    }

    return 0;
}
