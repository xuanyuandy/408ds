#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <random>
#include <assert.h>
#include <queue>

using namespace std;

struct Char {
    char ch;
    unsigned int freq;  // this is the weight of node

    Char(char c, int fq): ch(c), freq(fq) {}
    Char(): ch(0), freq(0) {}
};

struct BinaryTreeNode {
    Char c;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode(): c(), left(nullptr), right(nullptr) {}
};

bool operator<(const BinaryTreeNode& lhs, const BinaryTreeNode& rhs)
{
    return lhs.c.freq < rhs.c.freq;
}

bool operator>(const BinaryTreeNode& lhs, const BinaryTreeNode& rhs)
{
    return lhs.c.freq > rhs.c.freq;
}

template<typename T>
T* extract_min(priority_queue<T, vector<T>, greater<T> >& pq)
{
    if (pq.empty()) {
        cout << "Empty priority queue!" << endl;
        return nullptr;
    }
    T* pnode = new T(pq.top());
    pq.pop();
    return pnode;
}

BinaryTreeNode* huffman(vector<Char>& charset)
{
    // Get the number of chars in charset
    int n = charset.size();

    // Construct priority queue (min heap) for char set
    // default large heap
    priority_queue<BinaryTreeNode, vector<BinaryTreeNode>, greater<BinaryTreeNode> > pq;
    for (vector<Char>::iterator it = charset.begin(); it != charset.end(); ++it) {
        BinaryTreeNode node;
        node.c.ch = it->ch; 
        node.c.freq = it->freq;
        pq.push(node);
    }

    // Get non-leaf and leaf nodes:
    // get the lowest two frequencies objects, then merge them, and insert the merged object into pq
    for (int i = 0; i < n-1; i++) {
        BinaryTreeNode z;
        BinaryTreeNode* x = extract_min(pq);
        BinaryTreeNode* y = extract_min(pq);
        z.left = x;
        z.right = y;
        z.c.freq = x->c.freq + y->c.freq;
        pq.push(z);
    }
    return extract_min(pq);
}

// Use post-order traverse to deallocate BinaryTreeNode memory
void deallocate_memory(BinaryTreeNode* &root)
{
    if (root) {
        if (root->left)
            deallocate_memory(root->left);
        if (root->right)
            deallocate_memory(root->right);
        delete root;
        root = nullptr;
    }
}

void print_binarytree(const BinaryTreeNode* root, int order=0)
{
    if (root != nullptr) {
        if (order == 0)  // preorder traverse
            cout << root->c.freq << ' ';
        if (root->left != nullptr)
            print_binarytree(root->left, order);
        if (order == 1) // inorder traverse
            cout << root->c.freq << ' ';
        if (root->right != nullptr)
            print_binarytree(root->right, order);
        if (order == 2) // postorder traverse 
            cout << root->c.freq << ' ';
    }
}


int main(){    

    // huffman tree contruct 
    // we each find two min weight node and construct a father node whose weights is the sum of this two node
    // then we insert this father node to its heap and join the selection , it base on greedy

    unsigned int table[] = {45, 13, 12, 16, 9, 5};
    int n = sizeof(table)/sizeof(table[0]);

    vector<Char> charset;

    for (int i = 0; i < n; i++) {
        charset.push_back(Char('a'+i, table[i]));
    }

    BinaryTreeNode* roothuf = huffman(charset); 

    cout << " preorder sequence of huffman binary tree: " << endl
              << '\t';
    print_binarytree(roothuf);
    cout << endl;

    cout << " inorder sequence of huffman binary tree: " << endl
              << '\t';
    print_binarytree(roothuf, 1);
    cout << endl;

    // Deallocate all memory
    deallocate_memory(roothuf);

    return 0;
}







