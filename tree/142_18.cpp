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

using namespace std;

const int N = 100;  

int idx = 1,mxdep = 0;
/* 
this treenode consist of thread tree properity
*/
typedef struct TreeNode{
    int val;              // now the value can be int or A ~ Z which both store in int 
    int tag;              // this is the only identity of this TreeNode
    int dep;              // the depth of this node in this binary tree
    struct TreeNode *left;
    struct TreeNode *right;
    /**
     * ltag : 0 means point to its left child, 1 means point to its prefix
     * rtag : 0 means point to its right child, 1 means point to its succeed
     */
    int ltag,rtag;

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

// this is constrcut thread tree based on the constucted binary tree
void InThread(tnode *&p,tnode *&pre){
    if(p != nullptr){
        InThread(p -> left,pre);
        // the p node now don't have left son 
        if(p -> left == nullptr){ 
            p -> left = pre;
            p -> ltag = 1;
        }
        // deal with the pre node and solve its succeed node
        // but it means that the last node should be dealed extraly
        if(pre != nullptr && pre -> right == nullptr){
            pre -> right = p;
            pre -> rtag = 1;
        }
        pre = p;
        InThread(p -> right,pre);
    }        
}

// inorder tree
// return first node of this tree in InOrder Traverse
tnode *first(tnode *p){
    while(p -> ltag == 0) p = p -> left;
    return p;
}

// inorder tree
// return the succeed of node p
tnode *next(tnode *p){
    if(p -> rtag == 0) return first(p -> right);
    else return p -> right;
}

void InTraverse(tnode *root){
    for(tnode *p = first(root); p != nullptr;p = next(p)){
        cout << char(p -> val + 'A') << " ";
    }
    cout << endl;
}

tnode * findv(tnode *root,int x){
    if(root -> val == x) return root;
    tnode *tmp1 = nullptr,*tmp2 = nullptr;
    if(root -> left) tmp1 = findv(root -> left,x);
    if(root -> right) tmp2 = findv(root -> right,x);
    if(tmp1 != nullptr) return tmp1;
    else return tmp2;
}


// find the prefix about postorder of node p in InorderThreadTree
tnode * search(tnode *p){
    if(p -> rtag == 0) return p -> right;
    else if(p -> ltag == 0) return p -> left;
    else{
        tnode *tmp = p;
        // must search its prefix in a increasing adding route
        while(tmp -> ltag == 1 && tmp -> left != nullptr) tmp = tmp -> left;
        if(tmp -> ltag == 0) return tmp -> left;
        else return tmp;
    }
}
/*
Pay Attention !!!!!
because we have construct the InOrderThread Tree,so the pointer in the tree have changed
*/

void dfspost(tnode *u,vector<int> &postorder,vector<tnode *> &point){
    assert(u != nullptr);
    if(u -> left) dfspost(u -> left,postorder,point);
    if(u -> right) dfspost(u -> right,postorder,point);
    postorder.push_back(u -> val);
    point.push_back(u);
}

// check p prefix in postorder is q
bool check(tnode *p,tnode *q){
    tnode *tmp = search(p);
    if(tmp -> val == q -> val){
        return true;
    }
    return false;
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

    vector<int> postorder;
    vector<tnode *> point;
    dfspost(root,postorder,point);
    // first we should construct thread tree
    tnode *pre = nullptr;
    InThread(root,pre);
    pre -> right = nullptr;
    pre -> rtag = 1;
    
    // InOder Traverse
    InTraverse(root);

    cout << "postorder\n";
    for(int i = 0;i < postorder.size();i ++){
        cout << char('A' + postorder[i] ) << " ";
    }
    cout << endl;

    // check search funtion 
    bool flag = true;
    for(int i = 1;i < postorder.size();i ++){
        tnode *p = point[i];
        tnode *q = point[i - 1];
        cout << "test:\n";
        cout << char('A' + p -> val) << " " << char ('A' + q -> val) << endl;
        if(check(p,q)){
            cout << "success\n";
        }else{
            flag = false;
            cout << "failed\n";
        }
        puts("");
    }
    
    if(flag) cout << "all pass\n";
    else cout << "fail\n";
    
    return 0;
}