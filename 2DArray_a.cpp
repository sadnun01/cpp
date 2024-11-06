#include <iostream>  
using namespace std;  

int main() {  
    int arr[3][3] = {  
        {12, 5, 8},  
        {6, 7, 4},  
        {18, 9, 2}  
    };  
    int sum = 0;  

    for (int r = 0; r < 3; r++) {  
        for (int c = 0; c < 3; c++) {  
            sum += arr[r][c];  
        }  
    }  
    cout << "Sum: " << sum << endl; // Output: Sum: 71  
    return 0;  
}   