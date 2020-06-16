#include <iostream>
#include <sstream>
using namespace std;
string name;
string names[100];
int cnt = 0,pos;
int cnt1=0;

void manipulate(string name) {
    int i;
    for(i=0; i<name.size(); ++i) {
        char comma = name[i];
        if (comma == ',') {
            break;
        }
    }

    //cout<<"name "<<name<< " i: "<<i<<" "<<"size "<<name.size()<<endl;
    if(i==0) {
        string substr(name,1,name.size()-1);
        //cout << "i==0 "<<substr << endl;
        if(substr.size() >1) {manipulate(substr);}
    }
    if(i==name.size()-1) {
        string substr(name,0,name.size()-1);
        //cout << "i==name.size()-1 "<<substr << endl;
        if(substr.size() >1) {manipulate(substr);}
    }
    if (i == name.size()) {
        names[cnt] = name;
        cnt ++;
        //cout<<"q111"<<endl;
        return;
    }
    if (i > 0 && i < name.size()-1) {
        pos = i;
        //cout<<"pos: "<<pos<<endl;
        string str1(name,0,pos);
        //cout << "str1 "<<str1 << endl;
        string str2 (name, pos+1, name.size()-pos);
        //cout << "str2 "<<str2 << endl;
        if(str1.size() >1) {
        manipulate(str1);}
        cnt++;
        if(str2.size() >1) {
        manipulate(str2);}
    }

}

int main() {
    string line;
    getline (cin, line);
    istringstream iStream;
    iStream.str(line);

    while (iStream) {
        iStream >> name;
        if (iStream && name.size() > 1) {
            manipulate(name);
    }}
        //cout<<"out"<<endl;
        //cout<<cnt<<endl;
    int i;
    for (i=0; i<cnt; ++i) {
       if (names[i].size() >=1) {
            cout << names[i] << endl;
            cnt1++;
        }
    }
    cout<<cnt1<<endl;
    return 0;
}
