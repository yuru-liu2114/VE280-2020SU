#include <iostream>
#include <fstream>
#include "server_type.h"
#include <stdlib.h>
#include <string.h>
using namespace std;

string user_address[MAX_USERS];
User_t all_users[MAX_USERS];
int user_count=0;
void initialize_user_helper() {
    ifstream username_file;
    string first_address, second_address;
    username_file.open("../username");
    getline(username_file, first_address);
    //cout<<first_address<<endl;
    while (getline(username_file, second_address)) {
        all_users[user_count].username = second_address;
        user_address[user_count] = "../" + first_address + "/" + second_address;
        //cout<<user_address[user_count]<<endl;
        user_count++; //TODO: user_count should be <= Max_user
    }
    //cout<<user_count<<endl;

    for (int i = 0; i < user_count; ++i) {
        //TODO: for every user
        string userinfo_address = user_address[i] + "/user_info";
        //cout<<userinfo_address<<endl;
        ifstream userinfo_file;
        //TODO: define ifstream here, because need to renew everytime
        userinfo_file.open(userinfo_address);
        userinfo_file >> all_users[i].num_posts >> all_users[i].num_following;
        //cout<<all_users[i].username<<all_users[i].num_posts<<all_users[i].num_following<<endl;

        if (all_users[i].num_following > 0) {//TODO: deal with followings
            char emptychar;
            userinfo_file.get(emptychar);
            for (int k = 0; k < all_users[i].num_following; ++k) {
                string following_users;
                getline(userinfo_file, following_users);
                //cout<<all_users[i].username<<"following string: "<<following_users<<endl;
                for (int j = 0; j < user_count; ++j) {
                    if (all_users[j].username == following_users) {
                        all_users[i].following[k] = all_users + j;
                    }
                }
                //cout<<all_users[i].username<<"following"<<all_users[i].following[k]->username<<endl;
            }
        } //finish finding followings
        userinfo_file >> all_users[i].num_followers;
        if (all_users[i].num_followers > 0) { //deal with followers
            char emptychar;
            userinfo_file.get(emptychar);
            for (int k = 0; k < all_users[i].num_followers; ++k) {
                string follower_users;
                getline(userinfo_file, follower_users);
                //cout<<all_users[i].username<<"following string: "<<following_users<<endl;
                for (int j = 0; j < user_count; ++j) {
                    if (all_users[j].username == follower_users) {
                        all_users[i].follower[k] = all_users + j;
                    }
                }
                //cout<<all_users[i].username<<"followed by: "<<all_users[i].follower[k]->username<<endl;
            }
        }
        int post_id = 1; // TODO: post_id starts from 1,not 0
        string post_address;
        if (all_users[i].num_posts > 0) { //TODO: mind that post_id <= MAX_POSTS
            //TODO: traversal every posts of a certain user
            for (post_id = 1; post_id <= all_users[i].num_posts; ++post_id) {
                string post_index = to_string(post_id);
                post_address = user_address[i] + "/posts/" + post_index;
                cout << all_users[i].username << post_address << endl;
                ifstream post_file;
                post_file.open(post_address);
                getline(post_file, all_users[i].posts[post_id - 1].title);
                //cout<<all_users[i].posts[post_id-1].title<<endl;
                //TODO: begin dealing with tags
                string post_tag;
                char first_char;
                int tag_count = 0; //TODO: tag_count <=MAX_TAGS
                getline(post_file, post_tag);
                //cout<<post_tag<<endl;
                first_char = post_tag[0];
                //cout<<first_char<<endl;
                while (first_char == '#') {
                    all_users[i].posts[post_id - 1].tags[tag_count] = post_tag;
                    //cout<<all_users[i].posts[post_id-1].tags[tag_count]<<endl;
                    tag_count++;
                    getline(post_file, post_tag);
                    first_char = post_tag[0];
                }
                //cout<<tag_count<<endl;
                //for(int z=0;z<tag_count;z++)
                //{cout<<all_users[i].posts[post_id-1].tags[z]<<endl;}

                //TODO: deal with post text
                //cout<<post_tag<<endl;
                all_users[i].posts[post_id - 1].text = post_tag;
                //getline(post_file,all_users[i].posts[post_id-1].text);
                //cout<<all_users[i].posts[post_id-1].text<<endl;

                //TODO: deal with likes
                post_file >> all_users[i].posts[post_id - 1].num_likes;
                //cout << all_users[i].posts[post_id - 1].num_likes << endl;

                //TODO: deal with like users
                if (all_users[i].posts[post_id - 1].num_likes > 0) {
                    char empty_char;
                    post_file.get(empty_char);

                    for (int k = 0; k < all_users[i].posts[post_id - 1].num_likes; ++k) {
                        string like_users;
                        getline(post_file, like_users);
                        //cout << "string: " << like_users << endl;
                        //cout<<all_users[i].username<<"following string: "<<following_users<<endl;
                        for (int j = 0; j < user_count; ++j) {
                            if (all_users[j].username == like_users) {
                                all_users[i].posts[post_id - 1].like_users[j] = all_users + j;
                                //cout << all_users[i].posts[post_id - 1].like_users[j]->username << endl;
                            }
                        }
                        //cout<<all_users[i].username<<"following"<<all_users[i].following[k]->username<<endl;
                    }
                //TODO: deal with comments
                post_file>>all_users[i].posts[post_id-1].num_comments;
                    int total_comments=all_users[i].posts[post_id-1].num_comments;
                    cout<<"total comments: "<<total_comments<<endl;
                    if(total_comments > 0) {
                        //every comment of certain post of certain user
                        post_file.get(empty_char);
                        for(int comment=0; comment<total_comments; ++ comment) {//determine comment user
                            //cout<<"enter comment recursion"<<endl;
                            string comment_name;
                            getline(post_file,comment_name);//？
                            //cout<<"comment name"<<comment_name<<endl;
                            for(int user_index=0; user_index<user_count; ++ user_index) {
                                if (all_users[user_index].username == comment_name) {
                                    //cout<<"enter comment user recursion"<<endl;
                                    User_t* tmp_str=all_users + user_index;
                                    all_users[i].posts[post_id - 1].comments[comment].user = all_users + user_index;
                                    cout << tmp_str->username<< endl;
                                    break;
                                }
                            }
                            //cout<<"quit comment user recursion"<<endl;
                            //determine comment text
                            string tmp;
                            //post_file.get(empty_char);
                            getline(post_file,tmp);
                            cout<<tmp<<endl;
                            //getline(post_file,all_users[i].posts[post_id-1].comments[comment].text);
                            //cout<<all_users[i].posts[post_id-1].comments[comment].text<<endl;
                        }
                    }
                }

            }
        }

    }
}
//TODO: CORRECT,finish initializing users and posts


int main(){
    initialize_user_helper();
    return 0;
}
