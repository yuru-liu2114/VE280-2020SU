#include "server_type.h"
void access_user_address (string username_str);
void openfile(ifstream& userinfo_file, const int i,string userinfo_address);
void initialize_user_helper(string username_str);
void read_logfile(string logfile_str);
void readin_numflwing(ifstream& userinfo_file, const int i);
void initialize_tags(ifstream& post_file, const int i, const int post_id);
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
void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);

