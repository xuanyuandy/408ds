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

// just get the value of last kth lnode
int get(lnode *head,int k){
    lnode *l = NULL,*r;
    r = head -> next;
    int len = 0;
    while(r){  
        len ++;
        if(len == k + 1){
            l = head -> next;
        }
        if(l != NULL) l = l -> next;
        r = r -> next;
    }
    if(l){
        cout << "find " << l -> val << endl;
        return 1;
    }else{
        cout << "fail" << endl;
        return 0;
    }
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

    get(head,1);
    get(head,2);
    get(head,3);
    get(head,4);
    
    return 0;
}