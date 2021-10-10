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
#include <stack>

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

tnode * findv(tnode *root,int x){
    if(root -> val == x) return root;
    tnode *tmp1 = nullptr,*tmp2 = nullptr;
    if(root -> left) tmp1 = findv(root -> left,x);
    if(root -> right) tmp2 = findv(root -> right,x);
    if(tmp1 != nullptr) return tmp1;
    else return tmp2;
}

// find the closest ancestor between node p and node q 
void getp(tnode *u,tnode *p,tnode *q,tnode *&r){
    vector<tnode *> v1,v2;
    stack<tnode *> stk;
    tnode *prev;

    bool flag1 = false,flag2 = false;

    while(u != nullptr || !stk.empty()){
        while(u != nullptr){
            stk.push(u);
            u = u -> left;
        }

        u = stk.top();
        stk.pop();

        if(u -> val == p -> val && !flag1){
            stack<tnode *> tmp = stk;
            while(!tmp.empty()){
                tnode *t = tmp.top();
                tmp.pop();
                // cout << char('A' + t -> val) << endl;
                v1.push_back(t);
            }
            flag1 = true;
        }
        if(u -> val == q -> val && !flag2){
            flag2 = true;
            stack<tnode *> tmp = stk;
            while(!tmp.empty()){
                tnode *t = tmp.top();
                tmp.pop();
                // cout << char('A' + t -> val) << endl;
                v2.push_back(t);
            }
        }
        if(flag1 && flag2){
            reverse(v1.begin(),v1.end());
            reverse(v2.begin(),v2.end());
            tnode *pre = nullptr;
            int i = 0;
            for(i = 0;i < v1.size() && i < v2.size();i ++){
                if(v1[i] -> val != v2[i] -> val){
                    cout << "the closest ancestor of " << char('A' + p -> val) << " " << char ('A' + q -> val) << " is " << endl;
                    cout << char ('A' + pre -> val ) << endl;
                    return;
                }else{
                    pre = v1[i];
                }
            }
            if(v1.size() <= v2.size()){
                pre = v1.back();
            }else{
                pre = v2.back();
            }
            assert(pre != nullptr);
            cout << pre -> val << endl;
            cout << " the ancestor of " << char('A' + p -> val) << " " << char ('A' + q -> val) << endl;
            cout << char ('A' + pre -> val ) << endl;
            return;
        }

        if(u -> right == prev || u -> right == nullptr){
            prev = u;
            u = nullptr;
        }else {
            stk.push(u);
            u = u -> right;
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

    // find the closest ancestor of p and q node
    
    // first we can find a node by its value
    int x = 'K' - 'A';
    int y = 'F' - 'A';
    tnode *p = findv(root,x),*q = findv(root,y),*r;
    getp(root,p,q,r);
    
    return 0;
}