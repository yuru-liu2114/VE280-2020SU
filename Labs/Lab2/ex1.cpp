
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

#define RANGE 100000
bool isPrime[RANGE + 1];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime() {
    // TODO: implement Eratosthenes Sieve Algorithm
    bool PrimeNum[RANGE + 1];
    memset(PrimeNum,0,sizeof(PrimeNum));
    PrimeNum[0] = 1;
    PrimeNum[1] = 1;
    for(int i = 2;i < sqrt(RANGE+1);++ i) {
        if(PrimeNum[i] == 0) {
            for(int j = 2*i ;j < RANGE + 1  ; j+=i) {
                if(PrimeNum[j]==0){
                    PrimeNum[j] = 1;}
                
            }
        }
    }
    for(int i = 0;i < RANGE+1; ++ i) {
        isPrime[i] =! PrimeNum[i];
    }
}

int main() {
    // TODO: generate lookup table
    generateIsPrime();
    // TODO: read input and check if each num is prime
    int test_array_size,tmp_num;
    cin>>test_array_size;
    for(int i = 0;i < test_array_size;++ i) {
        cin >> tmp_num;
        if(isPrime[tmp_num]) {
            cout << tmp_num << " ";
        }
    }
    return 0;
}
