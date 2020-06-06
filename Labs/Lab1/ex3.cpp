/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return the trace of the Laplacian of the weight matrix.
int traceLaplacian(int weight[][50], int size){
    int Degree[size];
    int Diagonal[size];
    int trace[size];
    int tracesum=0;
    for(int i=0;i<size;++i){
        Degree[i]=0;
        for(int j=0;j<size;++j){
            Degree[i]+=weight[i][j];
            if(j==i){Diagonal[i]=weight[i][j];};
        }
    }
    for(int i=0;i<size;++i){
        trace[i]=Degree[i]-Diagonal[i];
        //cout<<trace[i]<<endl;
        tracesum+=trace[i];
    }
return tracesum;

}


int main(){
    int size, trace;
    int weight[50][50] = {};
    cin >> size;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            cin >> weight[i][j];

    trace = traceLaplacian(weight, size);
    cout << trace << endl;
}

