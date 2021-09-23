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

void displh(lnode *head){
    lnode *p = head -> next;
    while(p != head){
        cout << p -> val << " ";
        p = p -> next;
    }
    cout << '\n';
}

void delmin(lnode *head){
    lnode *p = head -> next,*pre = head;
    int mx = 1e9;
    while(head -> next != head){
        if(p == head){
            pre = p;
            p = p -> next;
        }else{
            // del
            if(p -> val == mx){
                cout << p -> val << " ";
                pre -> next = p -> next;
                p = pre -> next;
                mx = 1e9;
            }else{
                mx = min(mx,p -> val);
                pre = p;
                p = p -> next;
            }
        }
    }
    cout << endl;
}


int main(){
    freopen("list.txt","r",stdin);
    int len = read(num);
    
    lnode *L = (lnode *)malloc(sizeof (lnode));
    build(L,num,len);
    // just add the head
    lnode *head = (lnode *)malloc(sizeof(lnode));
    head -> next = L;
    // to construct the single circle list 
    lnode *p = head;
    while(p -> next){
        p = p -> next;
    }
    p -> next = head;
    displh(head);

    delmin(head);

    return 0;
}