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
    // TODO: implement this function.
    return left;
}

Node* Node::rightSubtree() const{
    // TODO: implement this function.
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
    Node* newnode = new Node("",0);
    newnode->str=leftNode->str+rightNode->str;
    newnode->num=leftNode->num+rightNode->num;
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
    root=rootNode;
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


int find_depth_helper(int depth,Node* node){
    if (node->rightSubtree()== nullptr && node->leftSubtree()== nullptr) {return depth;}
    depth++;
    if (node->rightSubtree()!= nullptr && node->leftSubtree()!= nullptr) {return max(find_depth_helper(depth,node->leftSubtree()),find_depth_helper(depth,node->rightSubtree()));}
    if (node->rightSubtree()== nullptr){return find_depth_helper(depth,node->leftSubtree());}
    return find_depth_helper(depth,node->rightSubtree());}
int BinaryTree::depth() const {
    int depth=1;
    depth=find_depth_helper(depth,root);
    return depth;
}

int node_get_depth(Node* node){
    int depth=find_depth_helper(1,node);
    return depth;
}
bool findpath_helper(const string &s, Node* node,string &result,string &finalstr,const int depth){
    if (node->getstr()==s){
        finalstr=result;
        return true;}
    if (node->leftSubtree()== nullptr && node->rightSubtree()== nullptr) {return false;}
    if (node->leftSubtree()== nullptr){
        result+="1";
        return findpath_helper(s,node->rightSubtree(),result,finalstr,depth);}
    if (node->rightSubtree()== nullptr) {
        result+="0";
        return findpath_helper(s,node->leftSubtree(),result,finalstr,depth);}
    result+="0";
    bool left=findpath_helper(s,node->leftSubtree(),result,finalstr,depth);
    if(result.size()<depth-node_get_depth(node) || result[result.size()-1]=='0'){result=result.substr(0,result.size()-1)+"1";}
    else {result=result.substr(0,depth-node_get_depth(node))+"1";}
    bool right=findpath_helper(s,node->rightSubtree(),result,finalstr,depth);
    return left||right;}

string BinaryTree::findPath(const string &s) const{
    // TODO: implement this function.
    string result,finalstr;
    int depth=this->depth();
    bool flag=findpath_helper(s,root,result,finalstr,depth);
    if(!flag){return "-1";}
    return finalstr;
}
void print_node_str(Node* node){
    cout<<node->getstr()<<" ";
}
void print_node_num(Node* node){
    cout<<node->getnum()<<" ";
}
void preorder_helper(Node* node){
    if(node==nullptr){return;}
    print_node_num(node);
    preorder_helper(node->leftSubtree());
    preorder_helper(node->rightSubtree());
}
void BinaryTree::preorder_num() const {
    preorder_helper(root);
}
void inorder_helper(Node* node){
    if(node==nullptr){return;}
    inorder_helper(node->leftSubtree());
    print_node_str(node);
    inorder_helper(node->rightSubtree());
}
void BinaryTree::inorder_str() const {
    inorder_helper(root);
}
void postorder_helper(Node* node){
    if(node==nullptr){return;}
    postorder_helper(node->leftSubtree());
    postorder_helper(node->rightSubtree());
    print_node_num(node);
}
void BinaryTree::postorder_num() const {
    postorder_helper(root);
}
int findsum_helper(Node* node,int sum){
    if(node==nullptr){return 0;}
    else{cout<<node->getstr()<<" "<<node->getnum()<<endl;
        //sum+=node->getnum();
        cout<<sum<<endl;
        return sum+node->getnum()+findsum_helper(node->leftSubtree(),sum)+findsum_helper(node->rightSubtree(),sum);
    }}
int BinaryTree::sum() const {
    if(root==nullptr) {
        return 0;
    }
    return findsum_helper(root,0);
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
            return false;
        }}
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

BinaryTree left_subtree_maker(Node* node){
    BinaryTree* left_subtree=new BinaryTree();
    if(node->leftSubtree()== nullptr) {return *left_subtree;}
    delete left_subtree;
    left_subtree=new BinaryTree(node->leftSubtree());
    return *left_subtree;
}
BinaryTree right_subtree_maker(Node* node){
    BinaryTree* right_subtree=new BinaryTree();
    if(node->rightSubtree()== nullptr) {return *right_subtree;}
    delete right_subtree;
    right_subtree=new BinaryTree(node->rightSubtree());
    return *right_subtree;
}
bool contained_helper(const BinaryTree& mytree,const BinaryTree& tree){
    Node* treeroot=tree.root;
    if(treeroot==nullptr || (treeroot->rightSubtree()== nullptr && treeroot->leftSubtree()==nullptr)){return false;}
    bool cur=mytree.covered_by(tree);
    BinaryTree left_tree=left_subtree_maker(treeroot);
    BinaryTree right_tree=right_subtree_maker(treeroot);
    bool left=mytree.covered_by(left_tree);
    bool right=mytree.covered_by(right_tree);
    if(cur || left || right) {return true;}
    else {return contained_helper(mytree,left_tree) || contained_helper(mytree,right_tree);}
}
bool BinaryTree::contained_by(const BinaryTree &tree) const {
    return contained_helper(*this, tree);
}
Node* copy_node(Node* node){
    Node* newnode=new Node(node->getstr(),node->getnum());
    return newnode;
}
void copytree_helper(Node* node,Node* newroot) {
    if(node->leftSubtree() == nullptr && node->rightSubtree() == nullptr){return;}
    if(node->leftSubtree()!= nullptr) {
        Node* newleft=copy_node(node->leftSubtree());
        newroot->setleft(newleft);
        copytree_helper(node->leftSubtree(),newleft);}
    if(node->rightSubtree()!= nullptr) {
        Node* newright=copy_node(node->rightSubtree());
        newroot->setright(newright);
        copytree_helper(node->rightSubtree(),newright);}
}
BinaryTree BinaryTree::copy() const {
    Node* newroot=copy_node(root);
    copytree_helper(root,newroot);
    BinaryTree* newtree=new BinaryTree(newroot);
    return *newtree;
}
