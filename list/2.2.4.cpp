#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

vector<int> num;
int x;

int read(vector<int>& num){
    int len = 0;
    string line;
    getline(cin,line);
    stringstream ss(line);
    while(ss >> x){
        len ++;
        num.push_back(x);
    }
    return len;
}

void dispv(vector<int> & num){
    for(int i = 0;i < num.size();i ++){
        cout << num[i] << " "; 
    }
    cout << endl;
}

// just single list
typedef struct LNode{
    int val;
    LNode * next;
} lnode;

void build(lnode * L,vector<int>& num,int len){
    lnode * s = L, *tmp;
    s -> val = num[0];
    if(len == 1) {
        s -> next = NULL;
    }
    else{
        for(int i = 1;i < len;i ++){
            tmp = (lnode *) malloc(sizeof(lnode));
            tmp -> val = num[i];
            s -> next = tmp;
            s = tmp;
        }
        s -> next = NULL;
    }
}

// this is for no head list 
void displ(lnode *l){
    do{
        cout << l -> val << " ";
        l = l -> next;
    }while(l != NULL);
    cout << endl;
}

// this is for head list 
void displh(lnode *head){
    while(head -> next){
        head = head -> next;
        cout << head -> val << " ";
    }
    cout << endl;
}

// first we should to know that delete a node should have two pointer
// now the header pointer help us

void del(lnode *head,int x){
    lnode *minp = head -> next,*minprep = head;
    lnode *p = head -> next,*pre = head;
    while(p){
        if(p -> val < minp -> val){
            minp = p;
            minprep = pre;
        }
        pre = p;
        p = p -> next;
    }
    // delete
    minprep -> next = minp -> next;
    free(p);
}

int main(){
    freopen("list.txt","r",stdin);
    int len = read(num);
    
    lnode * L;
    build(L,num,len);
    // displ(L);
    // just add the head
    lnode *head = (lnode *)malloc(sizeof(lnode));
    head -> next = L;

    displh(head);
    del(head,x);
    displh(head);

    return 0;
}