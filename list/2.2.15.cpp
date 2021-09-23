#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <assert.h>

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

// both head1 and head2 arrange in increasing order
// the difference with 2.2.14 is this problem need to free the node
// we should not malloc other space 
void Union(lnode *head1,lnode *head2){
    lnode *p1 = head1 -> next,*p2 = head2 -> next,*ne,*pre1 = head1;
    while(p1 && p2){
        // cout << p1 -> val << " " << p2 -> val << endl;
        if(p1 -> val > p2 -> val){
            ne = p2 -> next;
            free(p2);
            p2 = ne;
        }else if(p1 -> val < p2 -> val){
            ne = p1 -> next;
            pre1 -> next = p1 -> next;
            free(p1);
            p1 = ne;
        }else{
            // save p1 and del p2
            assert(p1 != NULL && p2 != NULL);
            pre1 = p1;
            p1 = p1 -> next;

            ne = p2 -> next;
            free(p2);
            p2 = ne;
        }   

    }
    /* beacause we just use the list a as the final list,so we should make sure that 
       the rear of list a should point to NULL, but when the above while loop ends,
       there are two conditions we should consider,p1 is NULL so we use pre1,p1 is 
       not NULL so we just use p1
    */ 
    // deal with the rear of the list a
    lnode *rear = NULL;
    if(p1) 
        rear = p1;
    else 
        rear = pre1;
    rear -> next = NULL;

    while(p1){
        ne = p1 -> next;
        free(p1);
        p1 = ne;
    }

    while(p2){
        ne = p2 -> next;
        free(p2);
        p2 = ne;
    }
    free(head2);
}

/*
2 4 5 5 5 6 6 6 7 8 9 9
3 4 5 5 5 6 9 9 10 12 34 
*/

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

    // union of A and B
    Union(head1,head2);

    displh(head1);
    return 0;
}