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
#include <assert.h>

using namespace std;

const int N = 100;  

int idx = 1,mxdep = 0;
typedef struct TreeNode{
    int val;              // now the value can be int or A ~ Z which both store in int 
    int tag;              // this is the only identity of this TreeNode
    int dep;              // the depth of this node in this binary tree
    struct TreeNode *left;
    struct TreeNode *right;

    TreeNode() : tag(idx ++), val(0), dep(1), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), tag(idx ++), dep(1), left(nullptr), right(nullptr) {}
    TreeNode(int x, int u) : val(x), tag(u), dep(1), left(nullptr), right(nullptr) {}
    TreeNode(int x, int u, TreeNode *left, TreeNode *right) : val(x), tag(u), dep(1), left(left), right(right) {}
}tnode;

// now the method building the binary tree is preorder traverse when meet the '#' end this branch 
void build(tnode *&u){
    char ch = getchar();
    if( ch == '#'){
        u = nullptr;
    }else{
        u = new tnode(int (ch - 'A'));
        build(u -> left);
        build(u -> right);
    }
    
}

void dfs(tnode *u){
    if(u -> left) {
        u -> left -> dep = u -> dep + 1;
        mxdep = max(mxdep,u -> left -> dep);
        dfs(u -> left);
    }
    if(u -> right) {
        u -> right -> dep = u -> dep + 1;
        mxdep = max(mxdep,u -> right -> dep);
        dfs(u -> right);
    }
}

void output(tnode *u){
    cout << u -> tag << " " << char(u -> val + 'A') << " " << u -> dep << endl;
    if(u -> left){
        output(u -> left);
    }
    if(u -> right){
        output(u -> right);
    }
}

void addnull(int d,vector<vector<int> > &level){
    int res = 1;    
    for(int i = d + 1;i <= mxdep;i ++){
        for(int j = 0;j < res;j ++)
            level[i].push_back(-1);
        res *= 2;
    }
}

// first to display the basic object of this tree
void construct(tnode *u,vector<vector<int> > &level){
    level[u -> dep].push_back(u -> val);
    if(u -> left)
        construct(u -> left,level);
    else
        addnull(u -> dep,level);
    if(u -> right)
        construct(u -> right,level);
    else
        addnull(u -> dep,level);
}

void format(vector<vector<int> > &level){
    for(int i = 1;i <= mxdep;i ++){
        int w = 1 << (mxdep - i);    
        for(int j = 0;j < 1 << (i - 1);j ++) // %*d是包括当前数总共所占的位置
            printf("%*c%*c",w,level[i][j] + 'A',w,' ');
        printf("\n");
    }
}

void beautyformat(vector<vector<int> > &level){
    for(int i = 1;i <= mxdep;i ++){
        int w = 1 << (mxdep - i + 2);    
        if(i == 1) printf("%*c\n",w,'_');
        else{
            for(int j = 0;j < 1 << (i - 2);j ++){
                printf("%*c",w + 1,' ');
                for(int k = 0;k < w - 3;k ++)
                    printf("_");
                printf("/ \\");
                for(int k = 0;k < w - 3;k ++)
                    printf("_");
                printf("%*c",w + 2,' ');   
            }
            printf("\n");
        }
        for(int j = 0;j < 1 << (i - 1);j ++)
            printf("%*c%c)%*c",w - 1,'(',level[i][j] + 'A',w - 1,' ');
        printf("\n");
    }
}

// from down to up and from right to left level by level

// find sepcific node by its val
// the main problem is that you must store the whole information of its son sending 
// and you should choose a right to send its father
TreeNode *get(TreeNode *root,int v){
    tnode *tmp = nullptr,*tmp1,*tmp2;
    if(root -> val == v) tmp = root;
    if(root -> left) {
        tmp1 = get(root -> left,v);
        if(tmp1 != nullptr) 
            tmp = tmp1;
    }
    if(root -> right) {
        tmp2 = get(root -> right,v);
        if(tmp2 != nullptr)
            tmp = tmp2;
    }
    return tmp;
}

bool judge(TreeNode *root,int v){
    if(root -> val == v) return true;
    if(root -> left && judge(root -> left,v)) return true;
    if(root -> right && judge(root -> right,v)) return true;
    return false;
}

TreeNode* getp(TreeNode *root,int v){
    tnode *tmp = nullptr,*tmp1 = nullptr,*tmp2 = nullptr;
    if(root -> left){
        if(root -> left -> val == v) tmp = root;
        else tmp1 = getp(root -> left,v);
    }
    if(root -> right){
        if(root -> right -> val == v) tmp = root;
        else tmp2 = getp(root -> right,v);
    }
    if(tmp1 != nullptr){
        tmp = tmp1;
    }
    if(tmp2 != nullptr){
        tmp = tmp2;
    }
    return tmp;
}

void swapnode(tnode *root,int x,int y){
    TreeNode *tx = get(root,x),*ty = get(root,y);
    // 直接判断一棵树的子树有没有另外一个节点即可
    assert(tx != nullptr && ty != nullptr);
    if(!judge(tx,y) && !judge(ty,x)) {
        // swap
        TreeNode *xp = getp(root,x);
        TreeNode *yp = getp(root,y);

        int dx = (xp -> right == tx) ? 1 : 0;
        int dy = (yp -> right == ty) ? 1 : 0;

        if(dx){
            xp -> right = ty;
        }else{
            xp -> left = ty;
        }
        if(dy){
            yp -> right = tx;
        }else{
            yp -> left = tx;
        }
    }
}

void lastprint(tnode *root){
    dfs(root);
    vector<vector<int> > level(mxdep + 1);
    construct(root,level);
    beautyformat(level);
}

int main(){
    /* 
    the form of the input is use level traverse and we should display the NULL op for each node
    */
    freopen("binary_tree.txt","r",stdin);
    tnode *root = nullptr;
    build(root);
    dfs(root);
    vector<vector<int> > level(mxdep + 1);
    construct(root,level);
    beautyformat(level);

    // just swap the two node in the tree
    int x = 1,y = 2;
    swapnode(root,x,y);
    lastprint(root);

    x = 1,y = 6;
    swapnode(root,x,y);
    lastprint(root);

    return 0;
}