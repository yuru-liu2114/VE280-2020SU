#include <iostream>
#include <fstream>
#include <sstream>
#include "simulation.h"
#include <string>
using namespace std;
ifstream logfile,username_file;
string command, subject, object;
int post_id,comment_id; //starts from 1
string user_address[MAX_USERS];
User_t all_users[MAX_USERS];
Tag_t all_tags[MAX_TAGS];

//TODO: CORRECT,finish initializing users and posts
int user_count=0,tag_count=0;
void access_user_address (string username_str) {
    // REQUIRES: username_str is valid
    // MODIFIES: user_address array, user_count;
    // EFFECTS: fetch address, store in array
    string first_address, second_address;
    username_file.open(username_str);
    try {
        if(!username_file) {
            // If username_file can't open
            ostringstream Ostream;
            string username_substr(username_str,3,username_str.size()-3);
            Ostream << "Error: Cannot open file " << username_substr << "!" << endl;
            throw Exception_t(FILE_MISSING,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    // read first line "username", as the first part of address
    getline(username_file, first_address);

    // read following lines, and determine total user number
    try {
        while (getline(username_file, second_address)) {
            // concatenate first address and second address, to form full relative path
            // count total user number
            all_users[user_count].username = second_address;
            user_address[user_count] = first_address + "/" + second_address;
            user_count ++; //TODO: user_count should be <= Max_user
        }
        unsigned int unsigned_user_count = user_count;
        if (unsigned_user_count > MAX_USERS) {
            // if too many users are included, raise capacity overflow error
            ostringstream Ostream;
            Ostream << "Error: Too many users!" << endl;
            Ostream << "Maximal number of users is "<<MAX_USERS<<"."<<endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }

}
void openfile(ifstream& userinfo_file, const int i,string userinfo_address) {
    // REQUIRES: userinfo_file is valid
    // MODIFIES: userinfo_file
    // EFFECTS: fetch userinfor_file
    try {
        userinfo_file.open(userinfo_address);
        if(!userinfo_file) {
            // If userinfo_file can't open
            ostringstream Ostream;
            Ostream << "Error: Cannot open file " << userinfo_address << "!" << endl;
            throw Exception_t(FILE_MISSING,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
}
void readin_numflwing(ifstream& userinfo_file, const int i) {
    // REQUIRES: userinfo_file is valid
    // MODIFIES: all_user array
    // EFFECTS: add following and follower to all_user array
    userinfo_file>> all_users[i].num_following;
    try {
        if (all_users[i].num_following > MAX_FOLLOWING) {
            // if number of followings exceed max following
            ostringstream Ostream;
            Ostream << "Error: Too many followings for user " << all_users[i].username << "!" << endl;
            Ostream << "Maximal number of followings is " << MAX_FOLLOWING << "." <<endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    if (all_users[i].num_following > 0) {
        // deal with followings
        char emptychar;
        userinfo_file.get(emptychar);

        for (unsigned k = 0; k < all_users[i].num_following; ++k) {
            string following_users;
            getline(userinfo_file, following_users);
            // fetch following user names, in string form
            for (int j = 0; j < user_count; ++j) {
                if (all_users[j].username == following_users) {
                    // transfer string to User_t type
                    all_users[i].following[k] = all_users + j;
                }
            }
        }
    }
    userinfo_file >> all_users[i].num_followers;
    try {
        if (all_users[i].num_followers > MAX_FOLLOWERS) {
            // if number of followings exceed max following
            ostringstream Ostream;
            Ostream << "Error: Too many followers for user " << all_users[i].username << "!" << endl;
            Ostream << "Maximal number of followers is " << MAX_FOLLOWERS << "." <<endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }

    if (all_users[i].num_followers > 0) { //deal with followers
        char emptychar;
        userinfo_file.get(emptychar);
        for (unsigned int k = 0; k < all_users[i].num_followers; ++ k) {
            string follower_users;
            getline(userinfo_file, follower_users);
            for (int j = 0; j < user_count; ++ j) {
                if (all_users[j].username == follower_users) {
                    all_users[i].follower[k] = all_users + j;
                }
            }
        }
    }

}
void initialize_tags(ifstream& post_file, const int i, const int post_id) {
    // REQUIRES: post_file is valid
    // MODIFIES: all_tags array
    // EFFECTS: add content and tag score
    string post_tag;
    char first_char;
    // perpost_tag_count <=MAX_TAGS
    getline(post_file, post_tag);
    first_char = post_tag[0];
    int perpost_tag_count = 0;
    while (first_char == '#') {
        string pure_tag(post_tag, 1, post_tag.size() - 2);
        all_users[i].posts[post_id - 1].tags[perpost_tag_count] = pure_tag;
        if (tag_count == 0) {
            all_tags[0].tag_content=all_users[i].posts[post_id - 1].tags[perpost_tag_count];
            all_tags[0].tag_score=5;
            tag_count++;}
        else {
            int i;
            for(i=0;i<tag_count;++i) {
                // search current content in previous all_tags array
                if (all_tags[i].tag_content == pure_tag){ //already exists, only plus 5
                    all_tags[i].tag_score+=5;
                    break;
                }
            }
            if (i >=tag_count) { //it the current content haven't existed, need to add
                all_tags[tag_count].tag_content = pure_tag;
                all_tags[tag_count].tag_score = 5;
                tag_count++;
            }
        }
        perpost_tag_count++;
        getline(post_file, post_tag);
        first_char = post_tag[0];
    }

    all_users[i].posts[post_id - 1].num_tags = perpost_tag_count;
    try {
        if ((unsigned int)perpost_tag_count > MAX_TAGS) {
            ostringstream Ostream;
            Ostream << "Error: Too many tags for post " << all_users[i].posts[post_id -1].title
                    << "!" << endl;
            Ostream << "Maximal number of tags is " << MAX_TAGS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    all_users[i].posts[post_id - 1].text = post_tag;
}
void initialize_user_helper(string username_str) {
    // EFFECTS: Implement initialization function.
    // Read username file, and initialize every User_t instance in all_users array
    // MODIFIES: Initialize all_user array
    // REQUIRES: username_file could be accessible and readable
    access_user_address (username_str);

    for (int i = 0; i < user_count; ++i) {
        string userinfo_address = user_address[i] + "/user_info";
        ifstream userinfo_file;
        openfile(userinfo_file,i,userinfo_address);
        userinfo_file >> all_users[i].num_posts;
        try {
            if (all_users[i].num_posts > MAX_POSTS) {
                // if number of posts exceed max post
                ostringstream Ostream;
                Ostream << "Error: Too many posts for user " << all_users[i].username << "!" << endl;
                Ostream << "Maximal number of posts is " << MAX_POSTS << "." <<endl;
                throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
            }
        }
        catch (Exception_t &exception) {
            cout << exception.error_info;
            return;
        }
        readin_numflwing(userinfo_file,i);
        post_id = 1; // post_id starts from 1,not 0
        string post_address,post_tag;
        all_users[i].posts[post_id - 1].owner = &all_users[i];
        if (all_users[i].num_posts > 0) { // mind that post_id <= MAX_POSTS
            // traversal every posts of a certain user
            for (unsigned post_id = 1; post_id <= all_users[i].num_posts; ++ post_id) {
                all_users[i].posts[post_id - 1].owner = &all_users[i];
                string post_index = to_string(post_id);
                post_address = user_address[i] + "/posts/" + post_index;
                ifstream post_file;
                try {
                    post_file.open(post_address);
                    if(!post_file) {
                        // If post_file can't open
                        ostringstream Ostream;
                        Ostream << "Error: Cannot open file " << post_address << "!" << endl;
                        throw Exception_t(FILE_MISSING,Ostream.str());
                    }
                }
                catch (Exception_t &exception) {
                    cout << exception.error_info;
                    return;
                }
                getline(post_file, all_users[i].posts[post_id - 1].title);
                initialize_tags(post_file,i,post_id);
                try {
                    post_file >> all_users[i].posts[post_id - 1].num_likes;
                    unsigned int num_like = all_users[i].posts[post_id - 1].num_likes;
                    if (num_like > MAX_LIKES) {
                        ostringstream oStream;
                        oStream << "Error: Too many likes for post " << all_users[i].posts[post_id -1].title
                                << "!" << endl;
                        oStream << "Maximal number of likes is " << MAX_LIKES << "." << endl;
                        throw Exception_t(CAPACITY_OVERFLOW,oStream.str());
                    }
                }
                catch (Exception_t &exception) {
                    cout << exception.error_info;
                    return;
                }
                for(unsigned int k = 0; k < all_users[i].posts[post_id - 1].num_tags; ++ k) {
                    for(int j = 0; j < tag_count; ++ j) {
                        if (all_users[i].posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                            all_tags[j].tag_score +=all_users[i].posts[post_id - 1].num_likes;
                        }
                    }
                }
                if (all_users[i].posts[post_id - 1].num_likes > 0) {
                    char empty_char;
                    post_file.get(empty_char);
                    int likeuser_count = 0;
                    for (unsigned int k = 0; k < all_users[i].posts[post_id - 1].num_likes; ++k) {
                        string like_users;
                        getline(post_file, like_users);
                        for (int j = 0; j < user_count; ++j) {
                            if (all_users[j].username == like_users) {
                                all_users[i].posts[post_id - 1].like_users[likeuser_count] = all_users + j;
                                likeuser_count++;
                                break;
                            }
                        }
                    }
                }
                post_file >> all_users[i].posts[post_id - 1].num_comments;
                try {
                    if (all_users[i].posts[post_id - 1].num_comments > MAX_COMMENTS) {
                        ostringstream Ostream;
                        Ostream << "Error: Too many comments for post " << all_users[i].posts[post_id -1].title
                                << "!" << endl;
                        Ostream << "Maximal number of comments is " << MAX_COMMENTS << "." << endl;
                        throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
                    }
                }
                catch (Exception_t &exception) {
                    cout << exception.error_info;
                    return;
                }
                for(unsigned int k = 0; k < all_users[i].posts[post_id - 1].num_tags; ++ k) {
                    for(int j = 0; j < tag_count; ++ j) {
                        if (all_users[i].posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                            all_tags[j].tag_score +=3*all_users[i].posts[post_id - 1].num_comments;
                        }
                    }
                }
                unsigned int total_comments = all_users[i].posts[post_id - 1].num_comments;
                if (total_comments > 0) {
                    char empty_char;
                    post_file.get(empty_char);
                    for (unsigned int comment = 0; comment < total_comments; ++ comment) {
                        //determine comment user
                        string comment_name;
                        getline(post_file, comment_name);
                        for (int user_index = 0; user_index < user_count; ++ user_index) {
                            if (all_users[user_index].username == comment_name) {
                                all_users[i].posts[post_id - 1].comments[comment].user = all_users + user_index;
                                break;
                            }
                        }
                        // determine comment text
                        string tmp;
                        getline(post_file, all_users[i].posts[post_id - 1].comments[comment].text);
                    }
                }
            }
        }
    }
    username_file.close();
}
void read_logfile(string logfile_str) {
    // EFFECTS: read logfile, extract subject, command, object
    // then call function command_execute()
    // MODIFIES: subject, command, object, post_id, comment_id
    // REQUIRES: logfile should be accessible and readable
    logfile.open(logfile_str);
    try {
        if(!logfile) {
            // If username_file can't open
            ostringstream Ostream;
            string logfile_substr(logfile_str,3,logfile_str.size()-3);
            Ostream << "Error: Cannot open file " << logfile_substr << "!" << endl;
            throw Exception_t(FILE_MISSING,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    string command_line;
    while (logfile) {
        getline(logfile, command_line);
        if (logfile) {
            post_id = 0;
            comment_id = 0;
            istringstream command_str(command_line);
            command_str >> subject >> command >> object >> post_id >> comment_id;
            command_execute();
        }
    }
    logfile.close();
}
void follow(User_t& flw_user1,User_t& flwed_user2) {
    // EFFECTS: Implement "follow" command, check whether user1 has followed user2
    // if not, add user2 to user1's following, add user1 to user2's followers
    // MODIFIES: User_t flw_user1, User_t flwed_user2
    // REQUIRES: flw_user1, flw_user2 could read and write
    cout<<">> follow"<<endl;
    unsigned int i;
    for (i = 0; i < flw_user1.num_following; ++ i) {
        if (flw_user1.following[i]->username == flwed_user2.username) {
            // if user1 has already followed user2
            break;
        }
    }
    if ( i >= flw_user1.num_following) {
        // if user1 has not follwed user2
        // then add user2 to user1's following
        flw_user1.following[flw_user1.num_following] = &flwed_user2;
        flw_user1.num_following++;
    }
    for (i = 0; i < flwed_user2.num_followers; ++ i) {
        if (flwed_user2.follower[i]->username == flw_user1.username) {
            // if user1 has already followed user2
            break;
        }
    }
    if (i >= flwed_user2.num_followers) {
        // if user1 has not follwed user2
        // then add user1 to user1's followers
        flwed_user2.follower[flwed_user2.num_followers] = &flw_user1;
        flwed_user2.num_followers++;
    }
    // if user1 has too many followings
    try {
        if (flw_user1.num_following > MAX_FOLLOWING) {
            // if number of followings exceed max following
            ostringstream Ostream;
            Ostream << "Error: Too many followings for user " << flw_user1.username << "!" << endl;
            Ostream << "Maximal number of followings is " << MAX_FOLLOWING << "." <<endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    // if user2 has too many followers
    try {
        if (flwed_user2.num_followers > MAX_FOLLOWERS) {
            // if number of followings exceed max following
            ostringstream Ostream;
            Ostream << "Error: Too many followers for user " << flwed_user2.username << "!" << endl;
            Ostream << "Maximal number of followers is " << MAX_FOLLOWERS << "." <<endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
}
void unfollow(User_t& unflw_user1,User_t& unflwed_user2){
    // MODIFIES: User_t unflw_user1, User_t unflwed_user2
    // REQUIRES: flw_user1, flw_user2 could read and write
    // EFFECTS: Implement "unfollow" command, check whether user1 has followed user2
    // if yes, remove user2 from user1's following, remove user1 from user2's followers
    unsigned int i,j;
    User_t *ptr[MAX_FOLLOWING];
    cout<<">> unfollow"<<endl;
    for (i=0; i<unflw_user1.num_following; ++i) {
        if (unflw_user1.following[i]->username == unflwed_user2.username) {
            // if user1 follows user2
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
            // if user1 follows user2
            for (j = 0; j < i; ++j) {
                ptr[j] = unflwed_user2.follower[j];
            }
            for (j = i; j < unflwed_user2.num_followers - 1; ++j) {
                ptr[j] = unflwed_user2.follower[j + 1];
            }
            unflwed_user2.num_followers--;

            for(unsigned int k=0; k<unflwed_user2.num_followers; ++k) {
                unflwed_user2.follower[k] = ptr[k];
            }
            break;
        }
    }

}
void like(User_t& lk_user1,User_t& lked_user2,int post_id) {
    // EFFECTS: Implement "like" command, to determine whether use2 has posted this post
    // and add user1 to post_id like user array
    // MODIFIES: User_t lk_user1, User_t lked_user2, Tags_t all_tags[]
    // REQUIRES: lk_user1, lked_user2 could read and write, post_id should be valid
    cout<<">> like"<<endl;
    unsigned int i;
    try {
        if (lked_user2.num_posts  < (unsigned int) post_id) {
            // if user2 doesn't have post post_id
            ostringstream Ostream;
            Ostream << "Error: "<< lk_user1.username << " cannot like post #" << post_id
            << " of " << lked_user2.username << "!" << endl;
            Ostream << lked_user2.username <<" does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    for (i = 0; i < lked_user2.posts[post_id-1].num_likes; ++ i) {
        if (lked_user2.posts[post_id-1].like_users[i]->username == lk_user1.username) {
            // if user1 has already like this post
            break;
        }
    }
    try {
        if (i < lked_user2.posts[post_id-1].num_likes) {
            ostringstream Ostream;
            Ostream << "Error: " <<lk_user1.username <<" cannot like post #" <<post_id<<" of "<<lked_user2.username<<"!" << endl;
            Ostream << lk_user1.username << " has already liked post #" <<post_id <<" of " <<lked_user2.username << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info ;
        return;
    }

    if (i >= lked_user2.posts[post_id-1].num_likes) {
        lked_user2.posts[post_id-1].like_users[i] = &lk_user1;
        lked_user2.posts[post_id-1].num_likes++;
        // add tag scores
        for(unsigned int k=0; k<lked_user2.posts[post_id - 1].num_tags; ++k) {
            for(int j=0; j<tag_count; ++j) {
                if (lked_user2.posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                    all_tags[j].tag_score +=1;
                }
            }
        }
    }
    try {
        // transform unsigned int to int type
        if (lked_user2.posts[post_id - 1].num_likes > MAX_LIKES) {
            ostringstream Ostream;
            Ostream << "Error: Too many likes for post " << lked_user2.posts[post_id -1].title
                    << "!" << endl;
            Ostream << "Maximal number of likes is " << MAX_LIKES << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
}
void unlike(User_t& unlk_user1,User_t& unlked_user2,int post_id) {
    // EFFECTS: Implement "unlike" command, remove user1 from like users of #post_id
    // post of user2
    // MODIFIES: User_t unlk_user1, User_t unlked_user2, Tags_t all_tags[]
    // REQUIRES: unlk_user1, unlked_user2 could read and write, post_id should be valid
    unsigned int i,j;
    cout<<">> unlike"<<endl;
    User_t *ptr[MAX_FOLLOWING];
    try {
        if (unlked_user2.num_posts  < (unsigned int) post_id  ) {
            // if user2 doesn't have posted post_id
            ostringstream Ostream;
            Ostream << "Error: "<< unlk_user1.username << " cannot unlike post #" << post_id
                    << " of " << unlked_user2.username << "!" << endl;
            Ostream << unlked_user2.username <<" does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    for(i = 0; i < unlked_user2.posts[post_id-1].num_likes; ++i) {
        if (unlked_user2.posts[post_id-1].like_users[i]->username == unlk_user1.username) {
            for (j = 0; j < i; ++j) {
                ptr[j] = unlked_user2.posts[post_id-1].like_users[j];
            }
            for (j = i; j < unlked_user2.posts[post_id-1].num_likes - 1; ++j) {
                ptr[j] = unlked_user2.posts[post_id-1].like_users[j + 1];
            }
            for(unsigned int k=0; k<unlked_user2.posts[post_id-1].num_likes-1; ++k) {
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
    try {
        if (i >= unlked_user2.posts[post_id-1].num_likes) {
            ostringstream Ostream;
            Ostream << "Error: " <<unlk_user1.username <<" cannot unlike post #" <<post_id<<" of "<<unlked_user2.username<<"!" << endl;
            Ostream << unlk_user1.username << " has not liked post #" <<post_id <<" of " <<unlked_user2.username << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    unlked_user2.posts[post_id-1].num_likes--;
}
void comment(User_t& cmt_user1, User_t& cmted_user2, int post_id) {
    // EFFECTS: Implement "comment" command, determine whether post_id exists, add comment
    // MODIFIES: User_t cmt_user1, User_t cmted_user2, Tags_t all_tags[]
    // REQUIRES: cmt_user1, cmted_user2 could read and write, post_id should be valid
    string comment_text;
    cout<<">> comment"<<endl;
    try {
        if (cmted_user2.num_posts < (unsigned int) post_id) {
            // if user2 doesn't have posted post_id
            ostringstream Ostream;
            Ostream << "Error: "<< cmt_user1.username << " cannot comment post #" << post_id
                    << " of " << cmted_user2.username << "!" << endl;
            Ostream << cmted_user2.username <<" does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    getline(logfile,comment_text);
    int total_comments=cmted_user2.posts[post_id -1].num_comments;
    cmted_user2.posts[post_id-1].comments[total_comments].text = comment_text;
    cmted_user2.posts[post_id-1].comments[total_comments].user = &cmt_user1;
    cmted_user2.posts[post_id -1].num_comments ++;
    try {
        // transform unsigned int to int type
        if (cmted_user2.posts[post_id - 1].num_comments > MAX_COMMENTS) {
            ostringstream Ostream;
            Ostream << "Error: Too many comments for post " << cmted_user2.posts[post_id -1].title
                    << "!" << endl;
            Ostream << "Maximal number of comments is " << MAX_COMMENTS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    // add tag scores
    for(unsigned int k = 0; k < cmted_user2.posts[post_id - 1].num_tags; ++ k) {
        for(int j = 0; j < tag_count; ++j) {
            if (cmted_user2.posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                all_tags[j].tag_score +=3;
            }
        }
    }
}
void uncomment(User_t& uncmt_user1, User_t& uncmted_user2, int post_id, int comment_id) {
    // EFFECTS: Implement "uncomment" command, determine whether post_id and comment_id exists and valid, remove comment
    // MODIFIES: User_t uncmt_user1, User_t uncmted_user2, Tags_t all_tags[]
    // REQUIRES: uncmt_user1, uncmted_user2 could read and write, post_id, comment_id should be valid
    unsigned int j,k;
    Comment_t tmp[MAX_COMMENTS];
    cout<<">> uncomment"<<endl;
    try {
        if (uncmted_user2.num_posts < (unsigned int) post_id) {
            // if user2 doesn't have posted post_id
            ostringstream Ostream;
            Ostream << "Error: "<< uncmt_user1.username << " cannot uncomment post #" << comment_id
                    << " of post #" << post_id << " posted by " << uncmted_user2.username << "!" << endl;
            Ostream << uncmted_user2.username <<" does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info ;
        return;
    }
    try {
        if (uncmted_user2.posts[post_id -1].num_comments < (unsigned int) comment_id) {
            // if user2 post_id doesn't have comment_id
            ostringstream Ostream;
            Ostream << "Error: "<< uncmt_user1.username << " cannot uncomment post #" << comment_id
                    << " of post #" << post_id << " posted by " << uncmted_user2.username << "!" << endl;
            Ostream << uncmted_user2.username <<" does not have comment #" << comment_id << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info ;
        return;
    }
    try {
        if (uncmted_user2.posts[post_id-1].comments[comment_id-1].user != &uncmt_user1) {
            // if user1 hasn't commented comment id
            ostringstream Ostream;
            Ostream << "Error: "<< uncmt_user1.username << " cannot uncomment post #" << comment_id
                    << " of post #" << post_id << " posted by " << uncmted_user2.username << "!" << endl;
            Ostream << uncmt_user1.username << " is not the owner of comment #" << comment_id << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    if (uncmted_user2.posts[post_id-1].comments[comment_id-1].user == &uncmt_user1) {
        for(int j=0; j<comment_id-1; ++j) {
            tmp[j]=uncmted_user2.posts[post_id-1].comments[j];
        }
        for(j=comment_id-1; j<uncmted_user2.posts[post_id-1].num_comments-1; ++j) {
            tmp[j]=uncmted_user2.posts[post_id-1].comments[j+1];
        }
        uncmted_user2.posts[post_id-1].num_comments--;

        for(j=0; j<uncmted_user2.posts[post_id-1].num_comments; ++j) {
            uncmted_user2.posts[post_id-1].comments[j] = tmp[j];
        }
        // add tag scores
        for(k=0; k<uncmted_user2.posts[post_id - 1].num_tags; ++k) {
            for(int j=0; j<tag_count; ++j) {
                if (uncmted_user2.posts[post_id - 1].tags[k] == all_tags[j].tag_content) {
                    all_tags[j].tag_score -=3;
                }
            }
        }
    }
}
void post(User_t& post_user) {
    // EFFECT: Implement "post" command, user posts a post, add tag scores
    // MODIFIES: User_t post_user, Tags_t all_tags[]
    // REQUIRES: post_user could be read and modify
    cout << ">> post" <<endl;
    post_user.num_posts ++;
    try {
        if (post_user.num_posts > MAX_POSTS) {
            // if number of posts exceed max post
            ostringstream Ostream;
            Ostream << "Error: Too many posts for user " << post_user.username << "!" << endl;
            Ostream << "Maximal number of posts is " << MAX_POSTS << "." <<endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    int max_index = post_user.num_posts - 1 ;
    //Post_t* tmp = &post_user.posts[max_index];
    string post_tag;
    int perpost_tag_count = 0;
    //getline(logfile,tmp->title);
    getline(logfile,post_user.posts[max_index].title);
    getline(logfile, post_tag);
    char first_char = post_tag[0];
    while (first_char == '#') {
        string pure_tag(post_tag,1,post_tag.size()-2);
        post_user.posts[max_index].tags[perpost_tag_count] = pure_tag;
        // implement tag array using pure_tag
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
        perpost_tag_count++;
        getline(logfile, post_tag);
        first_char = post_tag[0];
    }
    post_user.posts[max_index].num_tags = perpost_tag_count;
    try {
        // transform unsigned int to int type
        // int max_tags = MAX_TAGS;
        if ((unsigned) perpost_tag_count > MAX_TAGS) {
            ostringstream Ostream;
            Ostream << "Error: Too many tags for post " << post_user.posts[post_id -1].title
                    << "!" << endl;
            Ostream << "Maximal number of tags is " << MAX_TAGS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    post_user.posts[max_index].text = post_tag;
    post_user.posts[max_index].owner = &post_user;
}
void unpost(User_t& post_user, int post_id) {
    // EFFECT: Implement "delete" command, user delete post_id
    // MODIFIES: User_t post_user, Tags_t all_tags[]
    // REQUIRES: post_user could be read and modify, post_id should be valid
    Post_t tmp[MAX_POSTS];
    cout << ">> delete" << endl;
    try {
        if (post_user.num_posts + 1 <= (unsigned int) post_id) {
            // if user doesn't have posted post_id
            ostringstream Ostream;
            Ostream << "Error: "<< post_user.username << " cannot delete post #" << post_id << "!" << endl;
            Ostream << post_user.username <<" does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return;
    }
    if (post_user.num_posts >= (unsigned int) post_id) {

        for(unsigned int i = 0; i < post_user.posts[post_id - 1].num_tags; ++ i) {
            for(int j = 0; j < tag_count; ++ j) {
                if (post_user.posts[post_id - 1].tags[i] == all_tags[j].tag_content) {
                    all_tags[j].tag_score -=5;
                    all_tags[j].tag_score -= post_user.posts[post_id - 1].num_likes;
                    all_tags[j].tag_score -= 3*post_user.posts[post_id - 1].num_comments;
                }
            }
        }
        for (int i=0; i<post_id-1; ++i) {
            tmp[i] = post_user.posts[i];
        }
        for(unsigned int i=post_id-1; i<post_user.num_posts-1; ++i) {
            tmp[i] = post_user.posts[i+1];
        }
        post_user.num_posts--;
        for(unsigned int i=0; i<post_user.num_posts; ++i) {
            post_user.posts[i] = tmp[i];
        }
    }
}
void refresh(User_t& ref_user) {
// EFFECT: Implement "refresh" command, cout ref_user and its followings' posts
    // MODIFIES: test out file
    // REQUIRES: ref_user could be read and modify
    cout<<">> refresh"<<endl;
    for(unsigned i = 0; i < ref_user.num_posts; ++ i) {
        printPost(ref_user.posts[i]);
    }
    for(unsigned i = 0; i < ref_user.num_following; ++ i) {
        for (unsigned j = 0; j < ref_user.following[i]->num_posts; ++ j) {
            printPost(ref_user.following[i]->posts[j]);
        }
    }
}
void printPost(Post_t& post){
// MODIFIERS: print each post
    // REQUIRES: post should exist and valid
    // EFFECTS: implement "refresh" command
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
void printUser(User_t& user, const string& relationship){
    // MODIFIERS: print each user information and relationship
    // REQUIRES: user exists, relationship defined
    // EFFECTS: implement "visit" command
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}
void visit(User_t& user1, User_t& user2){
    // MODIFIERS: print user2 information
    // REQUIRES: user1 and user2 are exist and readable
    // EFFECTS: implement "visit" command
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
        for(unsigned int i=0; i<user2.num_following; ++i) {
            if (user1.username == user2.following[i]->username) {
                flag_2f1=1;
                break;
            }
        }
        if (flag_1f2 && flag_2f1) {
            relationship = "friend";
        }
        if (!flag_2f1 && flag_1f2) {
            relationship = "following";
        }
        if (!flag_1f2) {
            relationship = "stranger";}
    }
    printUser(user2,relationship);
}
void printTag(const Tag_t& tag, unsigned int rank){
    // MODIFIERS: print tag information
    // REQUIRES: tag and rank are valid
    // EFFECTS: implement "trending" command
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
void trending(Tag_t* all_tags,int num) {
// MODIFIERS: print tag information
    // REQUIRES: tag and rank are valid
    // EFFECTS: implement "trending" command
    for(int i=0; i<tag_count; ++i) {
        for(int j=i+1; j<tag_count; ++j) {
            if (all_tags[j].tag_score > all_tags[i].tag_score){
                // larger score in the front
                string content;
                int score;
                score = all_tags[i].tag_score;
                content=all_tags[i].tag_content;
                all_tags[i].tag_score = all_tags[j].tag_score;
                all_tags[i].tag_content=all_tags[j].tag_content;
                all_tags[j].tag_score = score;
                all_tags[j].tag_content = content;
            }
            if (all_tags[j].tag_score == all_tags[i].tag_score) {
                // same score, alphabet
                int tagj_size,tagi_size,min_size,index,flag=0,equal_count=0;
                tagj_size = all_tags[j].tag_content.size();
                tagi_size = all_tags[i].tag_content.size();
                min_size = min(tagj_size,tagi_size);
                for (index = 0; index < min_size; index ++) {
                    if (all_tags[j].tag_content[index] < all_tags[i].tag_content[index]) {
                        flag = 1;
                        break;
                    }
                    if (all_tags[j].tag_content[index] > all_tags[i].tag_content[index]) {
                        break;
                    }
                    else {
                        equal_count++;
                        continue;
                    }
                }
                if (tagj_size <= min_size && equal_count >= min_size) {
                    flag = 1;
                }
                if (flag == 1) {
                    string content;
                    int score;
                    score = all_tags[i].tag_score;
                    content = all_tags[i].tag_content;
                    all_tags[i].tag_score = all_tags[j].tag_score;
                    all_tags[i].tag_content=all_tags[j].tag_content;
                    all_tags[j].tag_score = score;
                    all_tags[j].tag_content = content;
                }
            }
        }
    }
    cout<<">> trending"<<endl;
    int min_val = min(num,tag_count);
    for(int i=0; i<min_val; ++i) {
        printTag(all_tags[i],i+1);
    }

}
void command_execute() {
    // MODIFIERS: manipulate to link read in command to functions
    // REQUIRES: commands are in correct forms
    // EFFECTS: guide command to function
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
        // instance user
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
    if (subject == "trending") {
        istringstream s(command);
        int num;
        s >> num;
        trending(all_tags,num);
    }
}

