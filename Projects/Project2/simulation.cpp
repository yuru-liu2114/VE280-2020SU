#include <iostream>
#include <fstream>
#include <sstream>
#include "simulation.h"
#include <string>
#include <string.h>
using namespace std;
ifstream username_file,logfile;
ofstream outstream;
//string username_str,logfile_str;
string command, subject, object;
int post_id,comment_id; //starts from 1
string user_address[MAX_USERS];
User_t all_users[MAX_USERS];
Tag_t all_tags[MAX_TAGS];

//TODO: CORRECT,finish initializing users and posts
int user_count=0,tag_count=0;

void initialize_user_helper(string username_str) {
    string first_address, second_address;
    //cout<<username<<endl;
    username_file.open(username_str);
    //cout<<"11111"<<endl;
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
            for (unsigned k = 0; k < all_users[i].num_following; ++k) {
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
            for (unsigned int k = 0; k < all_users[i].num_followers; ++k) {
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

        post_id = 1; // TODO: post_id starts from 1,not 0
        string post_address;
        all_users[i].posts[post_id - 1].owner = &all_users[i];
        if (all_users[i].num_posts > 0) { //TODO: mind that post_id <= MAX_POSTS
            //TODO: traversal every posts of a certain user
            for (unsigned post_id = 1; post_id <= all_users[i].num_posts; ++post_id) {
                all_users[i].posts[post_id - 1].owner = &all_users[i];
                string post_index = to_string(post_id);
                post_address = user_address[i] + "/posts/" + post_index;
                //cout << all_users[i].username << post_address << endl;
                ifstream post_file;
                post_file.open(post_address);
                getline(post_file, all_users[i].posts[post_id - 1].title);
                //cout<<all_users[i].posts[post_id-1].title<<endl;
                //TODO: begin dealing with tags
                string post_tag;
                char first_char;
                int perpost_tag_count = 0; //TODO: tag_count <=MAX_TAGS
                getline(post_file, post_tag);
                //cout<<post_tag<<endl;
                first_char = post_tag[0];
                //cout<<first_char<<endl;

                //cout << all_users[i].posts[post_id - 1].owner->username << " " << post_id << endl;
                while (first_char == '#') {
                    string pure_tag(post_tag, 1, post_tag.size() - 2);
                    //cout<<"pure_tag "<<pure_tag<<endl;
                    all_users[i].posts[post_id - 1].tags[perpost_tag_count] = pure_tag;
                    //cout << "all_users[i].posts[post_id - 1].tags[perpost_tag_count]: "
                    //<< all_users[i].posts[post_id - 1].tags[perpost_tag_count] << endl;
                    //TODO: implement tag array using pure_tag

                    if (tag_count == 0) {
                        all_tags[0].tag_content=all_users[i].posts[post_id - 1].tags[perpost_tag_count];;
                        all_tags[0].tag_score=5;
                        //cout<<"post tags initialize"<<endl;
                        //cout<<tag_count<<" "<<all_tags[tag_count].tag_content<<" "<<all_tags[tag_count].tag_score<<endl;
                        tag_count++;
                    }
                    else {
                        int i;
                        for(i=0;i<tag_count;++i) {
                            if (all_tags[i].tag_content == pure_tag){ //already exists, only plus 5
                                all_tags[i].tag_score+=5;
                                //cout<<"post tags continue"<<endl;
                                //cout<<tag_count<<" "<<all_tags[i].tag_content<<" "<<all_tags[i].tag_score<<endl;
                                break;
                            }
                        }
                        if (i >=tag_count) { //haven't existed, need to add
                            //all_tags[tag_count].tag_content = all_users[i].posts[post_id - 1].tags[perpost_tag_count];
                            all_tags[tag_count].tag_content = pure_tag;
                            all_tags[tag_count].tag_score = 5;
                            //cout<<"post tags initialize"<<endl;
                            //cout<<tag_count<<" "<<all_tags[tag_count].tag_content<<" "<<all_tags[tag_count].tag_score<<endl;
                            tag_count++;
                        }
                    }

                    //cout << "perpost_tag_count " << perpost_tag_count << endl;
                    //cout << "tags[] " << all_users[i].posts[post_id - 1].tags[perpost_tag_count] << endl;
                    //cout<<all_users[i].posts[post_id-1].tags[tag_count]<<endl;
                    perpost_tag_count++;
                    getline(post_file, post_tag);
                    first_char = post_tag[0];
                }
                //cout << "out of while recursion " << endl;
                all_users[i].posts[post_id - 1].num_tags = perpost_tag_count;
                //cout<<tag_count<<endl;
                //for (int z = 0; z < perpost_tag_count; z++) { cout << all_users[i].posts[post_id - 1].tags[z] << endl; }

                //TODO: deal with post text
                //cout<<post_tag<<endl;
                all_users[i].posts[post_id - 1].text = post_tag;
                //cout << all_users[i].posts[post_id - 1].text << endl;
                //getline(post_file,all_users[i].posts[post_id-1].text);
                //cout<<all_users[i].posts[post_id-1].text<<endl;

                //TODO: deal with likes
                post_file >> all_users[i].posts[post_id - 1].num_likes;
                //cout << all_users[i].username<<" "<<post_id<<"like num "<<all_users[i].posts[post_id - 1].num_likes<<endl;
                for(unsigned int k=0; k<all_users[i].posts[post_id - 1].num_tags; ++k) {
                    for(int j=0; j<tag_count; ++j) {
                        //cout<<"tag_count "<<j<<"tag: "<<all_tags[j].tag_content<<endl;
                        if (all_users[i].posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                            all_tags[j].tag_score +=all_users[i].posts[post_id - 1].num_likes;
                            //cout<<"like "<<tag_count<<" "<<all_tags[j].tag_content<<" "<<all_tags[j].tag_score<<endl;
                        }
                    }

                }
                //cout << all_users[i].posts[post_id - 1].num_likes << endl;

                //TODO: deal with like users
                if (all_users[i].posts[post_id - 1].num_likes > 0) {
                    char empty_char;
                    post_file.get(empty_char);
                    int likeuser_count = 0;
                    for (unsigned int k = 0; k < all_users[i].posts[post_id - 1].num_likes; ++k) {
                        string like_users;
                        getline(post_file, like_users);
                        //cout << "string: " << like_users << endl;
                        //cout<<all_users[i].username<<"following string: "<<like_users<<endl;

                        for (int j = 0; j < user_count; ++j) {
                            if (all_users[j].username == like_users) {
                                all_users[i].posts[post_id - 1].like_users[likeuser_count] = all_users + j;
                                likeuser_count++;
                                break;
                                //cout << all_users[i].username<<" "<<post_id<<" "<<all_users[i].posts[post_id - 1].like_users[likeuser_count]->username << endl;
                            }
                        }

                        //cout<<all_users[i].username<<"following"<<all_users[i].following[k]->username<<endl;
                    }
                }
                //cout<<"likeuser_count: "<<likeuser_count<<endl;
                /*for(int i=0; i<likeuser_count; ++i) {
                    cout << all_users[i].username<<" "<<post_id<<" "<<all_users[i].posts[post_id - 1].like_users[likeuser_count]->username<<endl;
                }}*/
                //TODO: deal with comments
                post_file >> all_users[i].posts[post_id - 1].num_comments;
                //cout<<all_users[i].username<<" "<<post_id<<"comment num "<<all_users[i].posts[post_id - 1].num_comments<<endl;
                for(unsigned int k=0; k<all_users[i].posts[post_id - 1].num_tags; ++k) {
                    for(int j=0; j<tag_count; ++j) {
                        if (all_users[i].posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                            all_tags[j].tag_score +=3*all_users[i].posts[post_id - 1].num_comments;
                            //cout<<"comment "<<tag_count<<" "<<all_tags[j].tag_content<<" "<<all_tags[j].tag_score<<endl;
                        }
                    }
                }

                int total_comments = all_users[i].posts[post_id - 1].num_comments;
                //cout<<"total comments "<<total_comments<<endl;
                //<<"total comments: "<<total_comments<<endl;
                if (total_comments > 0) {
                    //every comment of certain post of certain user
                    char empty_char;
                    post_file.get(empty_char);
                    for (int comment = 0; comment < total_comments; ++comment) {//determine comment user
                        //cout<<"enter comment recursion"<<endl;
                        string comment_name;
                        getline(post_file, comment_name);//？
                        //cout<<"comment name"<<comment_name<<endl;
                        for (int user_index = 0; user_index < user_count; ++user_index) {
                            if (all_users[user_index].username == comment_name) {
                                //cout<<"enter comment user recursion"<<endl;
                                //User_t *tmp_str = all_users + user_index;
                                all_users[i].posts[post_id - 1].comments[comment].user = all_users + user_index;
                                // << tmp_str->username<< endl;
                                break;
                            }
                        }
                        //cout<<"quit comment user recursion"<<endl;
                        //TODO: determine comment text
                        string tmp;
                        getline(post_file, all_users[i].posts[post_id - 1].comments[comment].text);
                        //cout << "out of post_id recursion " << endl;
                        //cout<<all_users[i].posts[post_id-1].comments[comment].text<<endl;
                    }
                }
            }

        }
    }
    username_file.close();

}

void read_logfile(string logfile_str) {
    //cout<<logfile_str<<endl;
    logfile.open(logfile_str);
    string command_line;

    while (logfile) {
        getline(logfile, command_line);
        if (logfile) {
            //cout << "command line:" << endl;
            //cout << command_line << endl;
            post_id = 0;
            comment_id = 0;
            istringstream command_str(command_line);
            command_str >> subject >> command >> object >> post_id >> comment_id;
            //cout << subject << " " << command << " " << object << " " << post_id << " " << comment_id << endl;
            //string tmp_command=command;
            //if(atoi(tmp_command.c_str())) {
            command_execute();
            //cout << "111" << endl;
        }

    }
}

void follow(User_t& flw_user1,User_t& flwed_user2) {
    unsigned int i;
    for (i=0; i<flw_user1.num_following; ++i) {
        if (flw_user1.following[i]->username == flwed_user2.username) {
            break;
        }
    }
    if ( i >= flw_user1.num_following) {
        flw_user1.following[flw_user1.num_following] = &flwed_user2;
        flw_user1.num_following++;
    }
    for (unsigned i=0; i<flwed_user2.num_followers; ++i) {
        if (flwed_user2.follower[i]->username == flw_user1.username) {
            break;
        }
    }
    if (i >= flwed_user2.num_followers) {
        flwed_user2.follower[flwed_user2.num_followers] = &flw_user1;
        flwed_user2.num_followers++;
    }
    cout<<">> follow"<<endl;
    /*cout<<"flw_user1's following "<<endl;
    for(i=0; i<flw_user1.num_following; ++i) {
        cout<<flw_user1.following[i]->username<<endl;
    }
    cout<<"flwed_user2's follower "<<endl;
    for(i=0; i<flwed_user2.num_followers; ++i) {
        cout<<flwed_user2.follower[i]->username<<endl;
    }*/

}
void unfollow(User_t& unflw_user1,User_t& unflwed_user2){
    unsigned int i,j;
    User_t *ptr[MAX_FOLLOWING];
    for (i=0; i<unflw_user1.num_following; ++i) {
        if (unflw_user1.following[i]->username == unflwed_user2.username) {
            // action:
            //unflw_user1.following[i] = unflw_user1.following[unflw_user1.num_following - 1];
            //memset(unflw_user1.following[unflw_user1.num_following - 1],0,sizeof(User_t));

            for (j = 0; j < i; ++j) {
                ptr[j] = unflw_user1.following[j];
            }
            for (j = i ; j < unflw_user1.num_following - 1; ++j) {
                ptr[j] = unflw_user1.following[j + 1];
            }
            unflw_user1.num_following--;

            for(unsigned int k=0; k<unflw_user1.num_following; ++k) {
                unflw_user1.following[k] = ptr[k];
            }
            break;
        }
    }
    for (i=0; i<unflwed_user2.num_followers; ++i) {
        if (unflwed_user2.follower[i]->username == unflw_user1.username) {
            // action:
            //unflw_user1.following[i] = unflw_user1.following[unflw_user1.num_following - 1];
            //memset(unflw_user1.following[unflw_user1.num_following - 1],0,sizeof(User_t));

            for (j = 0; j < i; ++j) {
                ptr[j] = unflwed_user2.follower[j];
            }
            for (j = i + 1; j < unflwed_user2.num_followers - 1; ++j) {
                ptr[j] = unflwed_user2.follower[j + 1];
            }
            unflwed_user2.num_followers--;

            for(unsigned int k=0; k<unflwed_user2.num_followers; ++k) {
                unflwed_user2.follower[k] = ptr[k];
            }
            break;
        }
    }
    cout<<">> unfollow"<<endl;
    /*cout<<"flw_user1's following "<<endl;
    for(i=0; i<unflw_user1.num_following; ++i) {
        cout<<unflw_user1.following[i]->username<<endl;
    }
    cout<<"flwed_user2's follower "<<endl;
    for(i=0; i<unflwed_user2.num_followers; ++i) {
        cout<<unflwed_user2.follower[i]->username<<endl;
    }*/
    logfile.close();
}
void like(User_t& lk_user1,User_t& lked_user2,int post_id) {
    unsigned int i;
    for (i=0; i<lked_user2.posts[post_id-1].num_likes; ++i) {
        if (lked_user2.posts[post_id-1].like_users[i]->username == lk_user1.username) {
            break;
        }
    }
    //cout<<"i is: "<<i<<endl;
    if (i >= lked_user2.posts[post_id-1].num_likes) {
        lked_user2.posts[post_id-1].like_users[i] = &lk_user1;
        lked_user2.posts[post_id-1].num_likes++;
        for(unsigned int k=0; k<lked_user2.posts[post_id - 1].num_tags; ++k) {
            for(int j=0; j<tag_count; ++j) {
                if (lked_user2.posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                    all_tags[j].tag_score +=1;
                }
            }
        }
    }

    cout<<">> like"<<endl;
    /*cout<<lked_user2.username<<" "<< endl;
    for (i=0; i<lked_user2.posts[post_id-1].num_likes; ++i) {
        cout<<lked_user2.posts[post_id-1].like_users[i]->username<<endl;
    }*/
}
void unlike(User_t& unlk_user1,User_t& unlked_user2,int post_id) {
    unsigned int i,j;
    User_t *ptr[MAX_FOLLOWING];
    for(i=0; i<unlked_user2.posts[post_id-1].num_likes; ++i) {
        if (unlked_user2.posts[post_id-1].like_users[i]->username == unlk_user1.username) {
            for (j = 0; j < i; ++j) {
                ptr[j] = unlked_user2.posts[post_id-1].like_users[j];
            }
            for (j = i; j < unlked_user2.posts[post_id-1].num_likes - 1; ++j) {
                ptr[j] = unlked_user2.posts[post_id-1].like_users[j + 1];
            }
            unlked_user2.posts[post_id-1].num_likes--;

            for(unsigned int k=0; k<unlked_user2.posts[post_id-1].num_likes; ++k) {
                unlked_user2.posts[post_id-1].like_users[k] = ptr[k];
            }
            for(unsigned int k=0; k<unlked_user2.posts[post_id - 1].num_tags; ++k) {
                for(int j=0; j<tag_count; ++j) {
                    if (unlked_user2.posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                        all_tags[j].tag_score -=1;
                    }
                }
            }
            break;
        }
    }
    cout<<">> unlike"<<endl;
    /*cout<<"unlked_user2's post likers "<<endl;
    for(i=0; i<unlked_user2.posts[post_id-1].num_likes; ++i) {
        cout<<unlked_user2.posts[post_id-1].like_users[i]->username<<endl;
    }*/
}

void comment(User_t& cmt_user1, User_t& cmted_user2, int post_id) {
    string comment_text;
    getline(logfile,comment_text);
    int total_comments=cmted_user2.posts[post_id -1].num_comments;
    cmted_user2.posts[post_id-1].comments[total_comments].text = comment_text;
    cmted_user2.posts[post_id-1].comments[total_comments].user = &cmt_user1;
    cmted_user2.posts[post_id -1].num_comments++;
    for(unsigned int k=0; k<cmted_user2.posts[post_id - 1].num_tags; ++k) {
        for(int j=0; j<tag_count; ++j) {
            if (cmted_user2.posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                all_tags[j].tag_score +=3;
            }
        }
    }
    cout<<">> comment"<<endl;
    /*for(int i=0; i<total_comments+1; ++i) {
        cout<<cmted_user2.posts[post_id-1].comments[i].text<<endl;
        cout<<cmted_user2.posts[post_id-1].comments[i].user->username<<endl;
    }*/
}

void uncomment(User_t& uncmt_user1, User_t& uncmted_user2, int post_id, int comment_id) {
    unsigned int j,k;
    Comment_t tmp[MAX_COMMENTS];
    if (uncmted_user2.posts[post_id-1].comments[comment_id-1].user == &uncmt_user1) {
        for(int j=0; j<comment_id-1; ++j) {
            tmp[j]=uncmted_user2.posts[post_id-1].comments[j];
        }
        for(j=comment_id-1; j<uncmted_user2.posts[post_id-1].num_comments-1; ++j) {
            tmp[j]=uncmted_user2.posts[post_id-1].comments[j+1];
        }
        uncmted_user2.posts[post_id-1].num_comments--;
        //cout<<uncmted_user2.username<<" "<<post_id<<endl;
        for(j=0; j<uncmted_user2.posts[post_id-1].num_comments; ++j) {
            uncmted_user2.posts[post_id-1].comments[j] = tmp[j];
            //cout<<uncmted_user2.posts[post_id-1].comments[j].user->username<<endl;
        }
        for(k=0; k<uncmted_user2.posts[post_id - 1].num_tags; ++k) {
            for(int j=0; j<tag_count; ++j) {
                if (uncmted_user2.posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                    all_tags[j].tag_score -=3;
                }
            }
        }
    }
    cout<<">> uncomment"<<endl;
}
void post(User_t& post_user) {
    post_user.num_posts++;
    int max_index=post_user.num_posts-1;
    Post_t* tmp=&post_user.posts[max_index]; //smart
    string post_tag;
    int perpost_tag_count = 0; //TODO: tag_count <=MAX_TAGS
    getline(logfile,tmp->title);
    getline(logfile, post_tag);
    //cout<<post_tag<<endl;
    char first_char = post_tag[0];
    //cout<<first_char<<endl;
    while (first_char == '#') {
        string pure_tag(post_tag,1,post_tag.size()-2);
        //cout<<"pure_tag "<<pure_tag<<endl;
        tmp->tags[perpost_tag_count] = pure_tag;
        //TODO: implement tag array using pure_tag
        int i=0;
        for(;i<tag_count;++i) {
            if (all_tags[i].tag_content == pure_tag){ //already exists, only plus 5
                all_tags[i].tag_score+=5;
                break;
            }
        }
        if (i >=tag_count) { //haven't existed, need to add
            all_tags[tag_count].tag_content = pure_tag;
            all_tags[tag_count].tag_score = 5;
            tag_count++;
        }
        //cout<<all_users[i].posts[post_id-1].tags[tag_count]<<endl;
        perpost_tag_count++;
        getline(logfile, post_tag);
        first_char = post_tag[0];
    }
    tmp->num_tags = perpost_tag_count;
    tmp->text = post_tag;

    cout << ">> post" <<endl;
    //cout<<post_user.posts[post_user.num_posts-1].title<<endl;
    //cout<<post_user.posts[post_user.num_posts-1].text<<endl;
    /*for(int j=0; j<post_user.num_posts; ++j) {
        cout<<"post "<<j<<endl;
        for (int i = 0; i < post_user.posts[j].num_tags; ++i) {
            cout << post_user.posts[j].tags[i] << endl;
        }
    }*/

}
void unpost(User_t& post_user, int post_id) {
    Post_t tmp[MAX_POSTS];
    //Post_t* tmp1;
    cout<<"post user num posts"<<post_user.num_posts<<endl;
    if ((int)post_user.num_posts >= post_id) {
        //cout<<"post_id: "<<post_id<<endl;
        for(unsigned int i=0; i<post_user.posts[post_id - 1].num_tags; ++i) {
            for(int j=0; j<tag_count; ++j) {
                if (post_user.posts[post_id - 1].tags[i] == all_tags[j].tag_content) {
                    all_tags[j].tag_score -=5;
                }
            }
        }
        for (int i=0; i<post_id-1; ++i) {
            //cout<<i<<endl;
            tmp[i]=post_user.posts[i];
            //cout<<i<<post_user.posts[i].num_tags;
            //*(tmp1+i)=post_user.posts[i];
        }
        for(unsigned int i=post_id-1; i<post_user.num_posts-1; ++i) {
            //cout<<i<<endl;
            tmp[i] = post_user.posts[i+1];
            //cout<<i<<post_user.posts[i].num_tags;
            //*(tmp1+i)=post_user.posts[i+1];
        }
        post_user.num_posts--;
        //post_user.posts[0]=tmp1;
        for(unsigned int i=0; i<post_user.num_posts; ++i) {
            post_user.posts[i] = tmp[i];
            //cout<<post_user.posts[i].title<<endl;
        }
    }
    cout<<">> delete"<<endl;

}
void refresh(User_t& ref_user) {
    cout<<">> refresh"<<endl;
    for(unsigned i=0; i<ref_user.num_posts; ++i) {
        printPost(ref_user.posts[i]);
    }
    for(unsigned i=0; i<ref_user.num_following; ++i) {
        for (unsigned j=0; j<ref_user.following[i]->num_posts; ++j) {
            printPost(ref_user.following[i]->posts[j]);
        }
    }
}
void printPost(Post_t& post){ //refresh
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for(unsigned int i = 0; i<post.num_tags; ++i){
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0){
        cout << "Comments:" << endl;
        for(unsigned int i = 0; i<post.num_comments; ++i){
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}
void printUser(User_t& user, const string& relationship){ //visit
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}
void visit(User_t& user1, User_t& user2){
    cout<<">> visit"<<endl;
    string relationship;
    if (user1.username != user2.username) {
        int flag_1f2=0,flag_2f1=0;
        for(unsigned int i=0; i<user1.num_following; ++i) {
            if (user2.username == user1.following[i]->username) {
                flag_1f2=1;
                break;
            }
        }
        for(unsigned int i=0; i<user1.num_followers; ++i) {
            if (user2.username == user1.follower[i]->username) {
                flag_2f1=1;
                break;
            }
        }
        if (flag_1f2 && flag_2f1) {
            relationship="friend";
        }
        if (!flag_2f1 && flag_1f2) {
            relationship = "following";
        }
        if (!flag_1f2) {
            relationship = "stranger";}
    }
    printUser(user2,relationship);
}
void printTag(const Tag_t& tag, unsigned int rank){ //trending
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
void trending(Tag_t* all_tags,int num) {
    for(int i=0; i<tag_count; ++i) {
        for(int j=i+1; j<tag_count; ++j) {
            if (all_tags[j].tag_score > all_tags[i].tag_score){
                string content;
                int score;
                score = all_tags[i].tag_score;
                content=all_tags[i].tag_content;
                all_tags[i].tag_score = all_tags[j].tag_score;
                all_tags[i].tag_content=all_tags[j].tag_content;
                all_tags[j].tag_score = score;
                all_tags[j].tag_content = content;
                //cout<<i<<" "<<j<<endl;
            }
        }
    }
    cout<<">> trending"<<endl;
    for(int i=0; i<num; ++i) {
        printTag(all_tags[i],i+1);
    }

}
void command_execute() {
    //User_t object_user, subject_user;
    //subject: 主语，object:宾语
    int subject_index=0, object_index=0;
    if(command != "unpost" && command!= "trending") {
        for (int i = 0; i < user_count; ++i) {
            if (all_users[i].username == subject) {
                subject_index = i;
            }
            if (subject.size() > 0 && all_users[i].username == object) {
                object_index = i;
            }
        }
        User_t& subject_user=all_users[subject_index];
        User_t& object_user=all_users[object_index];
        if (command == "like") {
            like(subject_user,object_user,post_id);
        }
        if (command == "unlike") {
            unlike(subject_user,object_user,post_id);
        }
        if (command == "follow") {
            follow(subject_user,object_user);
        }
        if (command == "unfollow") {
            unfollow(subject_user,object_user);
        }
        if(command == "comment") {
            comment(subject_user,object_user,post_id);
        }
        if(command == "uncomment") {
            uncomment(subject_user,object_user,post_id,comment_id);
        }
        if(command == "post") {
            post(subject_user);
        }
        if(command == "refresh") {
            refresh(subject_user);
        }
        if(command == "visit") {
            visit(subject_user,object_user);
        }
    }
    if (command == "delete") {
        for (int i = 0; i < user_count; ++i) {
            if (all_users[i].username == subject) {
                subject_index = i;
            }
        }
        User_t& subject_user=all_users[subject_index];
        istringstream s(object);
        s >> post_id;
        unpost(subject_user,post_id);
    }
    if (subject =="trending") {
        istringstream s(command);
        int num;
        s>>num;
        trending(all_tags,num);
    }
    //cout<<"subject: "<<subject_user.username<<"object: "<<object_user.username<<endl;
    //1. 使用引用； 2. 在函数结束后value会消失，以便下次赋值
}

