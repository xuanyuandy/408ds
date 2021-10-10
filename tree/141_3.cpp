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


void Preorder(tnode *u){
    printf("Preorder :\n");
    stack<tnode *> stk;

    while(u != nullptr || !stk.empty()){
        while(u != nullptr){
            cout << char(u -> val + 'A') << ' ';
            stk.push(u);
            u = u -> left;
        }
        u = stk.top();
        stk.pop();
        u = u -> right;
    }
    cout << endl;

}

// the In-order traversal using stack
void Inorder(tnode *u){
    printf("Inorder :\n");
    stack<tnode *> stk;

    while(u != nullptr || !stk.empty()){
        while(u != nullptr){
            stk.push(u);
            u = u -> left;
        }
        u = stk.top();
        cout << char(u -> val + 'A') << ' ';
        stk.pop();
        u = u -> right;
    }
    cout << endl;
}

/*
analysis the stack condition of the post traversal
the first push is while(u = u -> left) 
the second push beacause this node have right son
the condition that node who have right node can be printed is that
its 
*/
// the Post-order traversal using stack
void Postorder(tnode *u){
    printf("Postorder :\n");
    stack<tnode *> stk;
    tnode *prev;

    while(u != nullptr || !stk.empty()){
        while(u != nullptr){
            stk.push(u);
            u = u -> left;
        }
        // each time get a number judge if this number has right node ,then go if have
        // when detect the prev node is right node which display that the whole son node of this node has been printed
        u = stk.top();
        stk.pop();
        // prev store the last right node to make sure that the left and right of this node has been printed
        if(u -> right == nullptr || u -> right == prev){
            cout << char(u -> val + 'A') << ' ';
            prev = u;
            u = nullptr;
        }else{
            stk.push(u);
            u = u -> right;
        }
    }
    cout << endl;
}



// Morris traversal method 
/*
the main difference of the Pre and In is the first time or second time visit the node
*/
void MorrisPre(tnode *u){
    printf("MorrisPre\n");
    while(u != nullptr){
        if(u -> left){
            tnode *pre = u -> left;
            while(pre -> right != nullptr && pre -> right != u){
                pre = pre -> right;
            }
            // the first visit this node
            if(pre -> right == nullptr){
                cout << char(u -> val + 'A') << ' ';
                pre -> right = u;
                u = u -> left;
            }else if(pre -> right == u){      // the second visit this node
                pre -> right = nullptr;
                u = u -> right;
            }
        }else{
            cout << char(u -> val + 'A') << ' ';
            u = u -> right;
        }
    }
    cout << endl;
}

/*
the MorrisIn and MorrisPost both use the pre node in the Inorder traversal 
for MorrisIn the pre node display that the whole left tree has been traversed,so it should print this node and go right
for MorrisPost the pre node show that the right path in the left tree should be print in reverse order
*/
void MorrisIn(tnode *u){
    printf("MorrisIn\n");
    while(u != nullptr){
        if(u -> left){
            tnode *pre = u -> left;
            while(pre -> right != nullptr && pre -> right != u){
                pre = pre -> right;
            }
            // the first visit this node
            if(pre -> right == nullptr){
                pre -> right = u;
                u = u -> left;
            }else if(pre -> right == u){       // the second visit this node
                cout << char(u -> val + 'A') << ' ';
                pre -> right = nullptr;
                u = u -> right;
            }
        }else{
            cout << char(u -> val + 'A') << ' ';
            u = u -> right;
        }
    }
    cout << endl;
}

// this need a new root node to make sure the last incline node can be printed
// the method it print is -45 bias just (the direction of vector (-1,1))
void MorrisPost(tnode *u){
    tnode *root = new(tnode);
    root -> left = u;
    u = root;
    printf("MorrisPost\n");
    while(u != nullptr){
        if(u -> left){
            tnode *pre = u -> left;
            while(pre -> right != nullptr && pre -> right != u){
                pre = pre -> right;
            }
            // the first visit this node
            if(pre -> right == nullptr){
                pre -> right = u;
                u = u -> left;
            }else if(pre -> right == u){
                // reverse print the path from [u -> left , pre]
                tnode *tmp = u -> left;
                vector<int> res;
                while(tmp != u){
                    res.push_back(tmp -> val);
                    tmp = tmp -> right;
                }
                reverse(res.begin(),res.end());
                for(int i = 0;i < res.size();i ++){
                    cout << char(res[i] + 'A') << ' ';
                }
                pre -> right = nullptr;
                u = u -> right;
            }
        }else{
            u = u -> right;
        }
    }
    cout << endl;
}


/*
now we try inorder traversal and postorder traversal and quick Morris traversal
*/

int main(){
    /* 
    the form of the input is use level traverse and we should display the NULL op for each node
    */
    freopen("binary_tree.txt","r",stdin);
    tnode *root = nullptr;
    build(root);
    dfs(root);
    output(root);

    vector<vector<int> > level(mxdep + 1);
    construct(root,level);
    beautyformat(level);
    
    // post traverse
    // Postorder(root);
    Preorder(root);
    Inorder(root);
    Postorder(root);

    MorrisPre(root);
    MorrisIn(root);
    MorrisPost(root);
    

    return 0;
}