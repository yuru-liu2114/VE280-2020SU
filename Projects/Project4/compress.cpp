#include "binaryTree.h"
#include "huffmanTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// int argc, char *argv[]

string read_file(const string& filename){
    string line;
    ifstream iStream;
    iStream.open(filename);
    if(!iStream){cout<<"cannot open file: "<<filename<<endl;}
    getline(iStream,line,',');
    iStream.close();
    return line;
}
bool check_exist(Node* node[], int size,string cmp){
    for(int i=0;i<size;++i) {
        if(node[i]->getstr()==cmp){
            return true;
        }
    }
   return false;
}
int search_index(Node* node[],int size,string tmp){
    for(int i=0;i<size;++i){
        if(node[i]->getstr()==tmp){
            return i;
        }
    }
    return -1;
}
bool compare(Node* node1,Node* node2){ //descending order: return a>b
    if(node1->getnum() > node2->getnum()){return true;}
    if(node1->getnum() == node2->getnum()){
        return (node1->getstr()[0]>node2->getstr()[0]);
    }
    return false;
}
HuffmanTree* construct_tree(string line){
    Node* node[512];
    int size=0;
    for(char c : line){
        string tmp(1,c);
        if(check_exist(node,size,tmp)){
            node[search_index(node,size,tmp)]->incnum();
        }
        else{
            node[size++]=new Node(tmp,1);
        }
    }
    while(size>1){
        sort(node,node+size,compare);
        size--;
        node[size-1]=Node::mergeNodes(node[size-1],node[size]);
    }
    return new HuffmanTree(node[0]);
}
void get_binary(HuffmanTree& tree,const string& line){
    for(char c:line){
        string tmp(1,c);
        cout<<tree.findPath(tmp)<<" ";
    }
    cout<<endl;
}

int main(int argc, char* argv[]){
    string filename=argv[argc-1];
    string line=read_file(filename);
    HuffmanTree* tree=construct_tree(line);
    if(argc==3){tree->printTree();}
    if(argc==2){get_binary(*tree,line);}
    delete tree;
    return 0;
}
