#include <iostream>
#include <fstream>
#include <sstream>
#include "server_type.h"
#include "simulation.h"
#include <string>
using namespace std;

int main(int argc,char* argv[]){
    try {
        if(argc < 3) {
            //if argc is less than 3, one of the mandatory arguments is missing
            ostringstream Ostream;
            Ostream << "Error: Wrong number of arguments!" << endl;
            Ostream << "Usage: ./p2 <username> <logfile>" << endl;
            throw Exception_t(INVALID_ARGUMENT,Ostream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    string s1(argv[1]);
    string s2(argv[2]);
    //string s1,s2;
    //cin>>s1>>s2;
    string username_str = s1;
    string logfile_str = s2;
    initialize_user_helper(username_str);
    read_logfile(logfile_str);

    return 0;
}
