/*
this use TreeNode struct to store the binary tree
we just use the order sequence to build the tree 
the '#' represent the NULL
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;
int idx = 1;
typedef struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    int tag;              // this is the only identity of this TreeNode

    TreeNode() : tag(idx ++),val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x, int u) : val(x), tag(u),left(nullptr), right(nullptr) {}
    TreeNode(int x, int u, TreeNode *left, TreeNode *right) : val(x), tag(u), left(left), right(right) {}
}tnode;

tnode* build(tnode *root,string &str,int cnt){
    if(cnt < str.size()){
        
        
    }
}



int main(){
    /* 
    the form of the input is use level traverse and we should display the NULL op for each node
    */
    freopen("binary_tree.txt","r",stdin);
    string str; cin >> str;
    tnode *root = (tnode *) malloc(sizeof (tnode));
    build(root,str,1);


    return 0;
}