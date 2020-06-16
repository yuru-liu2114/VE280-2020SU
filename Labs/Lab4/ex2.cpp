#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct apples {
    string variety;
    float price;
    float weight;
    float unit_price;
};
int main(int argc, char* argv[]) {
    string filename=argv[1];
    //string filename="price_list";
    string full_filename="../"+filename;
    ifstream price;
    price.open(filename);
    //string tmp;
    apples tmp,lowest;
    int count=0;
    while(price) {
        price>>tmp.variety>>tmp.price>>tmp.weight;
        tmp.unit_price=tmp.price/tmp.weight;
        //cout<<tmp.variety<<tmp.price<<tmp.weight<<tmp.unit_price<<endl;
        if (count == 0) {
            lowest.variety=tmp.variety;
            lowest.price=tmp.price;
            lowest.weight=tmp.weight;
            lowest.unit_price=tmp.unit_price;
            //cout<<lowest.variety<<lowest.price<<lowest.weight<<lowest.unit_price<<endl;
        }

        else {
            if (tmp.unit_price < lowest.unit_price) {
                lowest.variety=tmp.variety;
                lowest.price=tmp.price;
                lowest.weight=tmp.weight;
                lowest.unit_price=tmp.unit_price;
            }
        }
        count++;

        //if(price) {
        //cout<<tmp<<endl;}
    }
    //cout.precision(2);
    cout<<lowest.variety<<" "<<setiosflags(ios::fixed)<<setprecision(2)<<lowest.price<<" "<<setiosflags(ios::fixed)<<setprecision(2)<<lowest.weight<<endl;
    return 0;
}

