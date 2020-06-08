#include <iostream>
#include <fstream>
#include "server_type.h"
#include <stdlib.h>
#include <string.h>
using namespace std;

string user_address[MAX_USERS];
User_t all_users[MAX_USERS];
int user_count=0;
void initialize_user_helper(){
    ifstream username_file;
    string first_address,second_address;
    username_file.open("../username");
    getline(username_file,first_address);
    //cout<<first_address<<endl;
    while(getline(username_file,second_address)) {
        all_users[user_count].username=second_address;
        user_address[user_count]="../"+first_address+"/"+second_address;
        //cout<<user_address[user_count]<<endl;
        user_count++; //mind: user_count should be <= Max_user
    }
    //cout<<user_count<<endl;
    for(int i=0;i<user_count;++i) {
        string userinfo_address=user_address[i]+"/user_info";
        //cout<<userinfo_address<<endl;
        ifstream userinfo_file;
        //define ifstream here, because need to renew everytime
        userinfo_file.open(userinfo_address);
        userinfo_file>>all_users[i].num_posts>>all_users[i].num_following;
        //cout<<all_users[i].username<<all_users[i].num_posts<<all_users[i].num_following<<endl;
        //CORRECT
        if (all_users[i].num_following > 0) {
            char emptychar;
            userinfo_file.get(emptychar);
            for(int k = 0;k < all_users[i].num_following;++ k) {
                string following_users;
                getline(userinfo_file,following_users);
                //cout<<all_users[i].username<<"following string: "<<following_users<<endl;
                for(int j = 0;j < user_count; ++ j) {
                    if (all_users[j].username==following_users) {
                        all_users[i].following[k] = all_users+j;
                    }
                }
            //cout<<all_users[i].username<<"following"<<all_users[i].following[k]->username<<endl;
            }
        } //finish finding followings
        userinfo_file>>all_users[i].num_followers;
        if (all_users[i].num_followers > 0) {
            char emptychar;
            userinfo_file.get(emptychar);
            for(int k = 0;k < all_users[i].num_followers;++ k) {
                string follower_users;
                getline(userinfo_file,follower_users);
                //cout<<all_users[i].username<<"following string: "<<following_users<<endl;
                for(int j = 0;j < user_count; ++ j) {
                    if (all_users[j].username==follower_users) {
                        all_users[i].follower[k] = all_users+j;
                    }
                }
                //cout<<all_users[i].username<<"followed by: "<<all_users[i].follower[k]->username<<endl;
            }
        }
    }
}//CORRECT,finish initializing users(except posts)
//如何识别tag #?

int main(){
    initialize_user_helper();
    return 0;
}
