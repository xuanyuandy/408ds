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


int main(){
    freopen("list.txt","r",stdin);

    int len1 = read(num);
    lnode *L1 = (lnode *)malloc(sizeof (lnode));
    build(L1,num,len1);
    // just insert the head
    lnode *head1 = (lnode *)malloc(sizeof(lnode));

    // this list is not circle double direction list

    head1 -> next = L1;
    L1 -> prior = head1;
    
    disp2dl(head1);

    return 0;
}