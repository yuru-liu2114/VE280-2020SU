#include <iostream>
#include <fstream>
#include <sstream>
#include "server_type.h"
#include "simulation.h"
#include <string>
using namespace std;

/*ifstream username_file,logfile;
string username_str,logfile_str;
string command, subject, object;
int post_id,comment_id; //starts from 1
string user_address[MAX_USERS];
User_t all_users[MAX_USERS];
Tag_t all_tags[MAX_TAGS];*/


int main(int argc,char* argv[]){
    string s1(argv[1]);
    string s2(argv[2]);
    //string s1,s2;
    //cin>>s1>>s2;
    string username_str="../"+ s1;
    string logfile_str="../" + s2;
    initialize_user_helper(username_str);
    read_logfile(logfile_str);

    return 0;
}
