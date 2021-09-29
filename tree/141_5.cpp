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

typedef pair<tnode *,int> pti;

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

int getheightbfs(tnode *root){ 
    int res = 0;
    queue<pti> q;
    pti tmp; tmp.first = root,tmp.second = 1;
    q.push(tmp);  
    while(!q.empty()){
        pti t = q.front();
        q.pop();
        tnode *ne;
        if(t.first -> left){
            ne = t.first -> left;
            pti tmp; tmp.first = ne,tmp.second = t.second + 1;
            res = max(res,tmp.second);
            q.push(tmp);
        }
        if(t.first -> right){
            ne = t.first -> right;
            pti tmp; tmp.first = ne,tmp.second = t.second + 1;
            res = max(res,tmp.second);
            q.push(tmp);
        }
    }
    return res;
}

int getheightpointer(tnode *root){
    if(root == nullptr) return 0;
    int hh = 0,tt = -1;
    tnode *q[1010];
    q[++ tt] = root;
    tnode *last = root;
    int level = 1;
    while(hh <= tt){
        tnode *t = q[hh ++];
        if(t -> left){
            q[++ tt] = t -> left;
        }
        if(t -> right){
            q[++ tt] = t -> right;
        }
        if(last == t && hh <= tt ){
            last = q[tt];
            cout << char('A' + last -> val) << endl;
            level ++;
        }
    }
    return level;
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


    // get the length of the tree in no recursive method
    // we just use the level traversal 
    
    cout << getheightbfs(root) << endl;
    cout << getheightpointer(root) << endl;

    return 0;
}