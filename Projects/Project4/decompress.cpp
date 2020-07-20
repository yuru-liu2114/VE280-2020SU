#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>
using namespace std;

void decompress_text(Node* root,const string& binary_file){
    ifstream iStream;
    iStream.open(binary_file);
    string binary;
    if(!iStream){cout<<"cannot open file: "<<binary_file<<endl;}
    while(iStream){
        Node* node=root;
        iStream>>binary;
        for(char c:binary){
            if(c=='0'){
                node=node->leftSubtree();
            }
            if(c=='1'){
                node=node->rightSubtree();
            }
        }
        cout<<node->getstr();
    }
    cout<<endl;
    iStream.close();
}
int main(int argc, char *argv[]) {
    string tree_file=argv[1];
    string binary_file=argv[2];
    HuffmanTree tree(tree_file);
    decompress_text(tree.root,binary_file);
    return 0;
}
