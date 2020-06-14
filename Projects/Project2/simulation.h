#include "server_type.h"
/*extern ifstream username_file,logfile;
extern string username_str,logfile_str;
extern string command, subject, object;
extern int post_id,comment_id; //starts from 1
extern string user_address[MAX_USERS];
extern User_t all_users[MAX_USERS];
extern Tag_t all_tags[MAX_TAGS];*/
// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.
void initialize_user_helper(string username_str);
void read_logfile(string logfile_str);
void command_execute();
void follow(User_t& flw_user1,User_t& flwed_user2);
void unfollow(User_t& unflw_user1,User_t& unflwed_user2);
void like(User_t& lk_user1,User_t& lked_user2,int post_id);
void unlike(User_t& unlk_user1,User_t& unlked_user2,int post_id);
void comment(User_t& cmt_user1, User_t& cmted_user2, int post_id);
void uncomment(User_t& uncmt_user1, User_t& uncmted_user2, int post_id,int comment_id);
void post(User_t& post_user);
void unpost(User_t& post_user, int post_id);
void refresh(User_t& ref_user);
void visit(User_t& user1, User_t& user2);
void trending(Tag_t* all_tags, int num);
/*

void trending(...);
*/

/* Helper Functions */

// Printing
void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);

