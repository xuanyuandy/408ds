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
#include <unordered_map>

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

tnode * buildpi(int pl,int pr,int il,int ir,vector<int> &preorder,
vector<int> &inorder,unordered_map<int,int> pos){
    if(pl > pr) return nullptr;
    assert(pr - pl == ir - il);
    if(pl == pr){
        return new tnode(preorder[pl]);
    }
    tnode *root = new tnode(preorder[pl]);
    int inp = pos[preorder[pl]];
    int leftlen = inp - il,rightlen = ir - inp;
    /*
    preorder: pl,(pl + 1,inp - il + pl),(inp - il + pl + 1,pr)
    inorder: (il,inp - 1),inp,(inp + 1,ir)
    */
    root -> left = buildpi(pl + 1,inp - il + pl,il,inp - 1,preorder,inorder,pos);
    root -> right = buildpi(inp - il + pl + 1,pr,inp + 1,ir,preorder,inorder,pos);
    return root;
}

tnode *buildip(int pl,int pr,int il,int ir,vector<int> &postorder,vector<int> &inorder,unordered_map<int,int> &pos){
    if(pl > pr) return nullptr;
    assert(pr - pl == ir - il);
    if(pl == pr){
        return new tnode(postorder[pr]);
    }
    tnode *root = new tnode(postorder[pr]);
    int inp = pos[postorder[pr]];
    int leftlen = inp - il,rightlen = ir - inp;
    /*
    preorder: (pl,pl + inp - il -1),(pl + inp - il,pr - 1),pr
    inorder: (il,inp - 1),inp,(inp + 1,ir)
    */
    root -> left = buildip(pl,pl + inp - il -1,il,inp - 1,postorder,inorder,pos);
    root -> right = buildip(pl + inp - il,pr - 1,inp + 1,ir,postorder,inorder,pos);
    return root;
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
    /* 
    use preorder and inorder to construct tree
    preorder : root , (part of left son) , (part of right son)
    inorder  : (part of left son) , root , (part of right son)
    */
    string pre = "ABCDEFG";
    string in = "BADCFGE";
    string post = "BDGFECA";

    int n = pre.size();
    vector<int> preorder,inorder,postorder;
    for(int i = 0;i < n;i ++){
        preorder.push_back(pre[i] - 'A');
        inorder.push_back(in[i] - 'A');
        postorder.push_back(post[i] - 'A');
    }
    unordered_map<int,int> pos;
    for(int i = 0;i < n;i ++){
        pos[inorder[i]] = i;
    }
    tnode *new_r = buildpi(0,n - 1,0,n - 1,preorder,inorder,pos);
    lastprint(new_r);

    new_r = buildip(0,n - 1,0,n - 1,postorder,inorder,pos);
    lastprint(new_r);
    return 0;
}