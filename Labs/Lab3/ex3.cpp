#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;


int main(int argc, char* argv[]) {
    int size,sum=0,min=0,add=0;
    cin >> size;
    int array[size];
    for (int i = 0; i < size; ++ i) {
        cin>>array[i];
        sum+=array[i];
        if(i==0) {
            min=array[i];
        }
        if(i>0) {
            if(array[i] < min) {
                min=array[i];
            }
        }
    }
    int help_tmp=-1,add_tmp=-1,verbose_tmp=-1,small_tmp=-1;
    int help_det=0,add_det=0,verbose_det=0,small_det=0;
    for (int i=1; i<argc; ++ i) {
        if(atoi(argv[i])) {
            add=atoi(argv[i]);
        }
        help_tmp=strcmp("--help",argv[i]);
        if (help_tmp==0) {
            help_det=1;
        }
        add_tmp=strcmp("--add",argv[i]);
        if (add_tmp==0) {
            add_det=1;
        }
        verbose_tmp=strcmp("--verbose",argv[i]);
        if (verbose_tmp==0) {
            verbose_det=1;
        }
        small_tmp=strcmp("--small",argv[i]);
        if (small_tmp==0) {
            small_det=1;
        }
    }
    //cout<<help_det<<" "<<add_det<<" "<<verbose_det<<" "<<small_det<<" "<<sum<<" "<<min<<" "<<add<<endl;
    if(help_det) {
        cout<<"Hey, I love Integers."<<endl;
        return 0;
    }
    if(argc==1 || (argc==2 && verbose_det==1)) {
        cout<<"No work to do!"<<endl;
    }
    if(argc>=3 && verbose_det==1) {
        if (add_det) {
            cout<<"This is add operation."<<endl;
            cout<<sum<<endl;
        }
        if (small_det) {
            cout<<"This is small operation."<<endl;
            cout<<add+min<<endl;
        }
    }

    if (add_det && verbose_det==0) {
        cout<<sum<<endl;
    }
    if (small_det && verbose_det==0) {
        cout<<add+min<<endl;
    }


    return 0;
}