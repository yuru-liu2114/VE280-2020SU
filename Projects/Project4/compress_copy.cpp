#include "binaryTree.h"
#include "huffmanTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
// int argc, char *argv[]
Node* del_min(vector<Node*>& nodevec){
    vector<Node*>::iterator p=nodevec.begin();
    int min=(*p)->getnum();
    int pos=0;
    string min_str=(*p)->getstr();
    Node *left=(*p)->leftSubtree();
    Node *right=(*p)->rightSubtree();
    for(;p!=nodevec.end();++p) {
        int tmp=(*p)->getnum();
        string tmp_str=(*p)->getstr();
        if(tmp<min){
            pos=p-nodevec.begin();
            min=tmp;
            min_str=(*p)->getstr();
            left=(*p)->leftSubtree();
            right=(*p)->rightSubtree();
        }
        else if(tmp==min){
            if(tmp_str[0]<min_str[0]){
                pos=p-nodevec.begin();
                min=tmp;
                min_str=tmp_str;
                left=(*p)->leftSubtree();
                right=(*p)->rightSubtree();
            }
        }
    }
    Node* remv=new Node(min_str,min,left,right);
    nodevec.erase(nodevec.begin()+pos);
    return remv;
}
void get_binary(Node* final_node,vector<Node*> copy) {
    vector<Node*>::iterator p=copy.begin();
    BinaryTree* tree=new BinaryTree(final_node);
    for(;p!=copy.end();++p) {
        string tmp=(*p)->getstr();
        string binary=tree->findPath(tmp);
        cout<<binary<<" ";
    }
    delete tree;
}
int main() {
    // TODO: implement this function
    string line,bit,curr;
    line="aeistpaeistpaeistpaeitpaeipaeipaeipaeipaeipaeipeipeipepeen";
    int linesize=line.size();
    vector<Node*> nodevec;
    vector<Node*> copyvec;

    for(int i=0;i<linesize;++i) {
        bit=line[i];
        string::size_type idx;
        idx=curr.find(bit);

        if(idx==string::npos){
            curr+=bit;
            Node* newnode= new Node(bit,1, nullptr, nullptr);
            nodevec.push_back(newnode);
            copyvec.push_back(newnode);
        }
        else {
            vector<Node*>::iterator p;
            for(p=nodevec.begin();p!=nodevec.end();++p) {
                if((*p)->getstr()==bit){
                    (*p)->incnum();
                    break;
                }
            }
        }
    }
    vector<Node*>::iterator p;
    for(p=nodevec.begin();p!=nodevec.end();++p) {
        cout<<(*p)->getstr()<<" "<<(*p)->getnum()<<endl;
    }
    while(nodevec.size()>1){
        Node* rmv1=del_min(nodevec);
        Node* rmv2=del_min(nodevec);
        string add_str=rmv2->getstr()+rmv1->getstr();
        int add_sum=rmv1->getnum()+rmv2->getnum();
        Node* add=new Node(add_str,add_sum,rmv2,rmv1);
        nodevec.push_back(add);
    }
    cout<<"111"<<endl;
    for(p=nodevec.begin();p!=nodevec.end();++p) {
        cout<<(*p)->getstr()<<" "<<(*p)->getnum()<<endl;
    }
    p=nodevec.begin();  
    Node* final_node = (*p);
    cout<<"222"<<endl;
    cout<<final_node->getstr()<<final_node->getnum()<<endl;
    //BinaryTree tree(final_node);
    //tree.printTree();
    get_binary(final_node,copyvec);

    return 0;
}

