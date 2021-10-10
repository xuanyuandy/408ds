/*
this use TreeNode struct to store the binary tree
we just use the order sequence to build the tree 
the '#' represent the NULL
a template of binary tree
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <random>
#include <assert.h>
#include <queue>

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

tnode *r;
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

void lastprint(tnode *root){
    if(root == nullptr){
        cout << "null tree" << endl;
    }
    else{
        dfs(root);
        vector<vector<int> > level(mxdep + 1);
        construct(root,level);
        beautyformat(level);
    }
}

// free the tree of u node
void free(tnode *&u){
    if(u == nullptr) return;
    free(u -> left);
    free(u -> right);
    delete u;
    u = nullptr;
}

// recursive method
// this delete the whole tree including the node u
void del(tnode *&root,int u){
    if(root == r && root -> val == u){
        free(root);
        return;
    }
    bool l = false,r = false;
    if(root -> left && root -> left -> val == u){
        root -> left = nullptr;
        free(root -> left);
        l = true;
    }
    if(root -> right && root -> right -> val == u){
        root -> right = nullptr;
        free(root -> right);
        r = true;
    }
    if(root -> left && !l){
        del(root -> left,u);
    }
    if(root -> right && !r){
        del(root -> right,u);
    }
}

// queue method
// this delete the whole tree including the node u
void delt(tnode *&u,int x){
    if(u -> val == x){
        free(u);
        return;
    }
    queue<tnode *> q;
    q.push(u);
    while(!q.empty()){
        tnode *tmp = q.front();
        // cout << tmp -> val << endl;
        q.pop();
        if(tmp -> left){
            if(tmp -> left -> val == x){
                free(tmp -> left);
                tmp -> left = nullptr;
            }
            else{
                q.push(tmp -> left);
            }
        }
        if(tmp -> right){
            if(tmp -> right -> val == x){
                free(tmp -> right);
                tmp -> right = nullptr;
            }
            else{
                q.push(tmp -> right);
            }
        }
    }
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
    r = root;

    // delete the val x node and free its son space
    del(root,4);
    delt(root,5);
    del(root,6);
    lastprint(root);
    return 0;
}