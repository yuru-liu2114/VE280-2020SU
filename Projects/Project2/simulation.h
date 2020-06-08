
#include "server_type.h"

// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.

void follow(User_t& flw_user1,User_t& flwed_user2);
void unfollow(User_t& unflw_user1,User_t& unflwed_users);
void like(User_t& lk_user1,User_t& lked_user2,int post_id);
void unlike(User_t& unlk_user1,User_t& unlked_user2,int post_id);
/*
void visit(...);
void trending(...);
void refresh(...);



void comment(...);
void uncomment(...);
void post(...);
void unpost(...);
*/

/* Helper Functions */

// Printing
void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);

