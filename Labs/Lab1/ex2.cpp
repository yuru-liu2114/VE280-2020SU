/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright ? 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]){
    bool alpha=0;
    bool integer=0;
    bool other=0;
    bool final=0;
    int tmpint;
    for(int i=0;password[i];++i){
        tmpint=(int)password[i];
        //cout<<"tmpint "<<tmpint<<endl;
        if(tmpint<31&tmpint>126){continue;}
        if(tmpint>=48 && tmpint<=57){integer=1;}
        if(tmpint>=65 && tmpint<=90){alpha=1;}
        if(tmpint>=97 && tmpint<=122){alpha=1;}
        else{other=1;}
        //cout<<alpha<<integer<<other<<endl;
    }
    final=(alpha&&other&&integer);
    //cout<<"final:"<<endl;
    return final;
}


int main(){
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;

    //isValidPassword(password);
    return 0;
}
//
// Created by Lyric on 2020/5/21.
//

