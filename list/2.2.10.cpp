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

void decompose(lnode *head,lnode *head1,lnode *head2){
    lnode *p = head -> next,*pre,*h1 = head1,*h2 = head2;
    bool flag = false;
    while(p){
        if(flag){
            h1 -> next = p;
            h1 = h1 -> next;
            p = p -> next;
            flag = false;
        }else{
            h2 -> next = p;
            h2 = h2 -> next;
            p = p -> next;
            flag = true;
        }
    }
    h1 -> next = NULL;
    h2 -> next = NULL;
}

int main(){
    freopen("list.txt","r",stdin);
    int len = read(num);
    
    lnode *L = (lnode *)malloc(sizeof (lnode));
    build(L,num,len);
    displ(L);
    // just add the head
    lnode *head = (lnode *)malloc(sizeof(lnode));
    head -> next = L;

    // decompose the list 
    lnode *head1 = (lnode *)malloc(sizeof(lnode));
    lnode *head2 = (lnode *)malloc(sizeof(lnode));
    head1 -> next = head2 -> next = NULL;

    
    decompose(head,head1,head2);

    displh(head1);
    displh(head2);

    return 0;
}