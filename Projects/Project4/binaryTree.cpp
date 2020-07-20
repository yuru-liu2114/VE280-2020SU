#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) {
    // TODO: implement this function.
    this->str=str;
    this->num=num;
    this->left=left;
    this->right=right;
}

Node* Node::leftSubtree() const{
    return left;
}

Node* Node::rightSubtree() const{
    return right;
}

string Node::getstr() const {
    // TODO: implement this function.
    return str;
}

int Node::getnum() const {
    // TODO: implement this function.
    return num;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    // TODO: implement this function.
    Node *newnode=new Node(leftNode->str+rightNode->str,leftNode->num+rightNode->num,leftNode,rightNode);
    return newnode;
}
void Node::setleft(Node *n){
    this->left=n;
}
void Node::setright(Node *n) {
    this->right=n;
}
void Node::incnum() {
    num++;
}
/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    // TODO: implement this function.
    if(rootNode!= nullptr){
        root=rootNode;}
}
void recur_destroy(Node* node) {
    if(node== nullptr){return;}
    recur_destroy(node->leftSubtree());
    recur_destroy(node->rightSubtree());
    delete node;
}
BinaryTree::~BinaryTree(){
    recur_destroy(root);
}


int find_depth_helper(Node* node){
    if (node== nullptr) {return 0;}
    return 1+max(find_depth_helper(node->leftSubtree()),find_depth_helper(node->rightSubtree()));
}

int BinaryTree::depth() const {
    return find_depth_helper(root);
}

bool findpath_helper(const string &s, Node* node,string result,string &finalstr,const int depth){
    if (node->getstr()==s){
        finalstr=result;
        return true;}
    if (node->leftSubtree()== nullptr && node->rightSubtree()== nullptr) {return false;}
    if (node->leftSubtree()== nullptr){return findpath_helper(s,node->rightSubtree(),result+"1",finalstr,depth);}
    if (node->rightSubtree()== nullptr) {return findpath_helper(s,node->leftSubtree(),result+"0",finalstr,depth);}
    bool left=findpath_helper(s,node->leftSubtree(),result+"0",finalstr,depth);
    bool right=findpath_helper(s,node->rightSubtree(),result+"1",finalstr,depth);
    return left||right;}
string BinaryTree::findPath(const string &s) const{
    string result,finalstr;
    int depth=this->depth();
    bool flag=findpath_helper(s,root,result,finalstr,depth);
    if(!flag){return "-1";}
    return finalstr;
}
void preorder_helper(Node* node){
    if(node==nullptr){return;}
    cout<<node->getnum()<<" ";
    preorder_helper(node->leftSubtree());
    preorder_helper(node->rightSubtree());
}
void BinaryTree::preorder_num() const {
    preorder_helper(root);
    cout<<endl;
}
void inorder_helper(Node* node){
    if(node==nullptr){return;}
    inorder_helper(node->leftSubtree());
    cout<<node->getstr()<<" ";
    inorder_helper(node->rightSubtree());
}
void BinaryTree::inorder_str() const {
    inorder_helper(root);
    cout<<endl;
}
void postorder_helper(Node* node){
    if(node==nullptr){return;}
    postorder_helper(node->leftSubtree());
    postorder_helper(node->rightSubtree());
    cout<<node->getnum()<<" ";
}
void BinaryTree::postorder_num() const {
    postorder_helper(root);
    cout<<endl;
}
int findsum_helper(Node* node){
    if(node==nullptr){return 0;}
    else{
        return node->getnum()+findsum_helper(node->leftSubtree())+findsum_helper(node->rightSubtree());
    }}
int BinaryTree::sum() const {
    if(root==nullptr) {
        return 0;
    }
    return findsum_helper(root);
}
void findeverypath_helper(Node* node,int sum,vector<int>* sumvec) {
    sum+=node->getnum();
    if(node->leftSubtree()==nullptr && node->rightSubtree()== nullptr) {
        sumvec->push_back(sum);
        return;}
    if(node->rightSubtree()!= nullptr){findeverypath_helper(node->rightSubtree(),sum,sumvec);}
    if(node->leftSubtree()!= nullptr) {findeverypath_helper(node->leftSubtree(),sum,sumvec);}
}
bool BinaryTree::allPathSumGreater(int sum) const {
    vector<int>* sumvector = new vector<int>;
    findeverypath_helper(root,0,sumvector);
    vector<int>::iterator p;
    for(p=sumvector->begin();p!=sumvector->end();++p) {
        int tmp=*p;
        if(tmp<=sum) {
            delete sumvector;
            return false;
        }}
    delete sumvector;
    return true;
}
void inorder_vec_helper(Node* node, vector<int> *vec){
    if(node==nullptr) {return;}
    inorder_vec_helper(node->leftSubtree(),vec);
    vec->push_back(node->getnum());
    inorder_vec_helper(node->rightSubtree(),vec);
}
void postorder_vec_helper(Node* node, vector<int> *vec){
    if(node==nullptr) {return;}
    postorder_vec_helper(node->leftSubtree(),vec);
    postorder_vec_helper(node->rightSubtree(),vec);
    vec->push_back(node->getnum());
}
bool covered_helper(Node* thistree,Node* tree){
    if(thistree== nullptr){return true;}
    if(tree== nullptr || thistree->getnum()!= tree->getnum()){ return false;}
    return covered_helper(thistree->leftSubtree(),tree->leftSubtree()) && covered_helper(thistree->rightSubtree(),tree->rightSubtree());
}
bool BinaryTree::covered_by(const BinaryTree &tree) const {
    return covered_helper(root, tree.root);
}
bool if_contained(Node* mytree,Node* tree){
    if(covered_helper(mytree,tree)){return true;}
    if(tree== nullptr){return false;}
    return (covered_helper(mytree,tree->leftSubtree()) || covered_helper(mytree,tree->rightSubtree()));
}
bool BinaryTree::contained_by(const BinaryTree &tree) const {
    return if_contained(root,tree.root);
}

Node* copytree_helper(Node* node) {
   if(node== nullptr){return nullptr;}
   Node* newroot=new Node(node->getstr(),node->getnum(),copytree_helper(node->leftSubtree()),copytree_helper(node->rightSubtree()));
   return newroot;
}
BinaryTree BinaryTree::copy() const {
    BinaryTree tree(copytree_helper(root));
    return tree;
}
