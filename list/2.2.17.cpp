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

// circle double direction list
typedef struct LNode{
    int val;
    LNode * next;
    LNode * prior; 
} lnode;

void build(lnode * L,vector<int>& num,int len){
    lnode * s = L, *tmp,*first;
    s -> val = num[0];
    first = s;
    if(len == 1) {
        s -> next = first;
        first -> prior = s;
    }
    else{
        for(int i = 1;i < len;i ++){
            tmp = (lnode *) malloc(sizeof(lnode));
            tmp -> val = num[i];
            s -> next = tmp;
            tmp -> prior = s;
            s = tmp;
        }
        s -> next = first;
        first -> prior = s;
    }
}


void disp2dl(lnode *head){
    lnode *p = head -> next;
    while(p != head){
        cout << p -> val << " ";
        p = p -> next;
    }
    cout << '\n';
    return;
}

void judge(lnode *head){
    lnode *p = head -> next,*q = head -> prior;
    // this consider the len even and odd condition
    while(p != q && q -> next != p){
        if(p -> val == q -> val){
            p = p -> next;
            q = q -> prior;
        }else{
            cout << "fail" << endl;
            return;
        }
    }
    cout << "success" << endl;
}

int main(){
    freopen("list.txt","r",stdin);

    int len = read(num);
    lnode *L = (lnode *)malloc(sizeof (lnode));
    build(L,num,len);
    // just insert the head
    lnode *head = (lnode *)malloc(sizeof(lnode));
    head -> next = L;
    head -> prior = L -> prior;
    L -> prior -> next = head;
    L -> prior = head;

    disp2dl(head);
    // symmetry judge
    judge(head);

    return 0;
}