#include <iostream>
#include <string>
#include <cstring>

using namespace std;

bool if_hand_helper(string mystr, int start, int end){
    if(start>=end){
        cout<<"start char "<<mystr[start]<<"; end char "<<mystr[end]<<endl;
        cout<<"start char "<<start<<"; end char "<<end<<endl;
        return true;
    }
    if(mystr[start]==mystr[end]) {
        cout<<"start char "<<mystr[start]<<"; end char "<<mystr[end]<<endl;
        return if_hand_helper(mystr,start+1,end-1);
    }
    else {return false;}

}
int main(){
    string mystr="fuccuf";
    //int length=length(mystr);
    cout<<mystr.length()<<endl;
    cout<<if_hand_helper(mystr,0,mystr.length()-1)<<endl;
    return 0;
}
