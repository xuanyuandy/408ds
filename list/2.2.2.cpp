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

void del(lnode *&head,int x){
    lnode * now, *pre = head;
    now = head -> next;
    while(now){
        if(now -> val == x ){        
            pre -> next = now -> next;
            free(now);
            now = pre -> next;
        }else{
            // keep the before state firstly 
            pre = now;
            now = now -> next;
        }
    }
}

int main(){
    freopen("list.txt","r",stdin);
    int len = read(num);
    
    // normal null header
    lnode list;
    lnode * L = &list;
    build(L,num,len);
    //displ(L);

    // just add header base on the up condition 
    lnode headnode;
    lnode *head = &headnode;
    head -> next = L;

    displh(head);

    del(head,3);

    displh(head);

    return 0;
}