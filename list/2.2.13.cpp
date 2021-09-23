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

lnode * combine(lnode *head1,lnode *head2){
    lnode *head = (lnode *) malloc(sizeof (lnode));
    lnode *p1 = head1 -> next,*p2 = head2 -> next,*ne;
    while(p1 && p2){
        // inverse insert and insert the lower first
        if(p1 -> val >= p2 -> val){
            // insert p2
            ne = p2 -> next;
            p2 -> next = head -> next;
            head -> next = p2;
            p2 = ne; 
        }else{
            // insert p1
            ne = p1 -> next;
            p1 -> next = head -> next;
            head -> next = p1;
            p1 = ne;
        }
    }

    while(p1){
        ne = p1 -> next;
        p1 -> next = head -> next;
        head -> next = p1;
        p1 = ne;
    }
    while(p2){
        ne = p2 -> next;
        p2 -> next = head -> next;
        head -> next = p2;
        p2 = ne; 
    }
    return head;
}


int main(){
    freopen("list.txt","r",stdin);

    int len1 = read(num);
    lnode *L1 = (lnode *)malloc(sizeof (lnode));
    build(L1,num,len1);
    displ(L1);
    // just add the head
    lnode *head1 = (lnode *)malloc(sizeof(lnode));
    head1 -> next = L1;

    num.clear();
    int len2 = read(num);
    lnode *L2 = (lnode *)malloc(sizeof (lnode));
    build(L2,num,len2);
    displ(L2);
    // just add the head
    lnode *head2 = (lnode *)malloc(sizeof(lnode));
    head2 -> next = L2;

    
    lnode *head = combine(head1,head2);
    displh(head);

    
    return 0;
}