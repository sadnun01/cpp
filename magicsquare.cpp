#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    int n;
    cout << "Please enter an odd number: ";
    cin >> n;
    int arr[n][n];
    memset(arr, 0, sizeof(arr));

    int i = 0, j = n / 2;
    for (int x = 1; x <= n * n; x++) {
        arr[i][j] = x;
        int newi = (i == 0) ? n - 1 : i - 1;
        int newj = (j == n - 1) ? 0 : j + 1;
        if (arr[newi][newj] != 0) i = (i + 1) % n;
        else {
            i = newi;
            j = newj;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
