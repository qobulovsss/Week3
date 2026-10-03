#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using namespace chrono;

int main() {
    vector<int> sizes = {50, 100, 200, 400};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);

    cout << left
         << setw(10) << "n"
         << setw(20) << "Time (ms)"
         << setw(20) << "Approx. bytes"
         << "Notes" << endl;

    cout << string(65, '-') << endl;

    for (int n : sizes) {
        vector<vector<int>> A(n, vector<int>(n));
        vector<vector<int>> B(n, vector<int>(n));
        vector<vector<int>> C(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = dist(gen);
                B[i][j] = dist(gen);
            }
        }

        auto start = high_resolution_clock::now();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        auto end = high_resolution_clock::now();

        double elapsed =
            duration<double, milli>(end - start).count();
        long long bytes =
            3LL * n * n * sizeof(int);

        cout << left
             << setw(10) << n
             << setw(20) << fixed << setprecision(2) << elapsed
             << setw(20) << bytes
             << "O(n^3) time, O(n^2) space"
             << endl;
    }

    return 0;
}
