#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;


struct Node {
    int data;
    Node* next;
};

void testVector(int n, int target) {
    vector<int> v;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        v.push_back(i);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (v[i] == target) {
            found = i;
            break;
        }
    }
    high_resolution_clock::time_point t3 = high_resolution_clock::now();

    duration<double, milli> insertTime = t2 - t1;
    duration<double, milli> searchTime = t3 - t2;
    cout << "Vector  | insert: " << insertTime.count() << " ms | search: "
         << searchTime.count() << " ms | found at " << found
         << " | bytes: " << v.capacity() * sizeof(int) << endl;
}

void testArray(int n, int target) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            found = i;
            break;
        }
    }
    high_resolution_clock::time_point t3 = high_resolution_clock::now();

    duration<double, milli> insertTime = t2 - t1;
    duration<double, milli> searchTime = t3 - t2;
    cout << "Array   | insert: " << insertTime.count() << " ms | search: "
         << searchTime.count() << " ms | found at " << found
         << " | bytes: " << (long long)n * sizeof(int) << endl;

    delete[] arr;
}

void testList(int n, int target) {
    Node* head = NULL;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i = n - 1; i >= 0; i--) {   // add at the front, so the list reads 0,1,2,...
        Node* newNode = new Node;
        newNode->data = i;
        newNode->next = head;
        head = newNode;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    int found = -1;
    int index = 0;
    Node* current = head;
    while (current != NULL) {
        if (current->data == target) {
            found = index;
            break;
        }
        current = current->next;
        index++;
    }
    high_resolution_clock::time_point t3 = high_resolution_clock::now();

    duration<double, milli> insertTime = t2 - t1;
    duration<double, milli> searchTime = t3 - t2;
    cout << "List    | insert: " << insertTime.count() << " ms | search: "
         << searchTime.count() << " ms | found at " << found
         << " | bytes: " << (long long)n * sizeof(Node) << endl;

    current = head;
    while (current != NULL) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

int main() {
    int n = 1000000;
    int target = n - 1;

    cout << "n = " << n << endl;
    cout << "Node size: " << sizeof(Node) << " bytes" << endl;

    testVector(n, target);
    testArray(n, target);
    testList(n, target);

    return 0;
}
