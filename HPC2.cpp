#include <iostream>
#include <omp.h>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
        #pragma omp parallel for
        for (int j = first; j < n - 1; j += 2)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
    }
}

int main() {
    int n;
    cout << "\nEnter number of elements: ";
    cin >> n;
    int *a = new int[n];

    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++) cin >> a[i];

    bubble(a, n);

    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

    delete[] a;
    return 0;
}
