
#include <cassert>
#include <iostream>

using namespace std;

const int MAXSIZE = 10;

bool canWin(int count, int arr[], int position) {
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence
    // TODO: implement this function
    assert(count < 11 && count > 1);
    // cout<<"position "<<position<<endl;
    // cout<<"arr[position] "<<arr[position]<<endl;
    // cout<<"count "<<count<<endl;
    if (position < 0 || position > (count-1) || arr[position] == 0 || count <= 0) {
        return 0;
    }
    if (arr[position] == 280) {
        return 1;
    }
    else {
        //cout<<"into recursion"<<endl;
        int tmp = arr[position];
        arr[position] =0;
            return (canWin(count-1,arr,position+tmp) || canWin(count-1,arr,position-tmp));
    }

}

int main() {
    int count;
    cin >> count;
    // cout<< "count: "<<count<<endl;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position);
}
