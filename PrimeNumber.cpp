#include <iostream>
using namespace std;

int main(){
    int n=11;
    bool isPrime = true;

    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            isPrime= false;
            break;
        }
    }

    if(isPrime==true){
        cout<<"Prime no";
    }
    return 0;
}
