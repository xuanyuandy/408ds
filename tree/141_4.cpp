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
    dfs(root);
    vector<vector<int> > level(mxdep + 1);
    construct(root,level);
    beautyformat(level);
}

// from right to left and from down to up using level traversal
void leveltraverse(tnode *root,int dep,vector<vector<int> >&res){
    if(root -> right){
        leveltraverse(root -> right,dep + 1,res);
    }
    if(root -> left){
        leveltraverse(root -> left,dep + 1,res);
    }
    res[dep].push_back(root -> val);
}

// level traversal without recursive
void basiclevel(tnode *root){
    // just use a queue to maintain the dealing order
    queue<tnode *> q;
    q.push(root);
    while(!q.empty()){
        tnode *tmp = q.front();
        cout << char(tmp -> val + 'A') << " ";
        q.pop();
        if(tmp -> left){
            q.push(tmp -> left);
        }
        if(tmp -> right){
            q.push(tmp -> right);
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
    

    // do level traverse
    dfs(root); // find maxdepth
    vector<vector<int> > res(mxdep + 1);
    leveltraverse(root,1,res);

    printf("level traversal :\n");
    for(int i = mxdep;i >= 1;i --){
        for(int j = 0;j < res[i].size();j ++){
            int t = res[i][j];
            cout << char(t + 'A') << " ";
        }
    }

    printf("\nbasic level traversal: \n");
    basiclevel(root);

    return 0;
}