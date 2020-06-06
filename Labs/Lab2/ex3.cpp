
#include <cmath>
#include <iostream>

using namespace std;

#define MAX_LEN 1024

int square[MAX_LEN][MAX_LEN];

void initSquare(int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            square[i][j] = 1;
        }
    }
}

// REQUIRES: the square with left-upper corner at (x,y)
//           and length len is within square[MAX_LEN][MAX_LEN]
// MODIFIES: square[][]
// EFFECTS: fully update the specified square
void updateSquare(int x, int y, int len) {
    // TODO: check boundary condition
    if(len==2){
        square[x][y]=0;
    }
    // TODO: update left upper square
    else {
        for(int i = x;i < x+len/2;++ i) {
            for(int j = y; j < y+len/2;++ j) {
                square[i][j]=0;
            }
        }
        updateSquare(x+len/2,y,len/2);
        updateSquare(x,y+len/2,len/2);
        updateSquare(x+len/2,y+len/2,len/2);
    }
    // TODO: recursive call for remaining 3 squares

}

void printSquare(int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            cout << square[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // TODO: read input
    int n,len;
    cin >> n;
    len = pow(2,n);
    // TODO: init, update, and print square
    initSquare(len);
    updateSquare(0,0,len);
    printSquare(len);
    return 0;
}

