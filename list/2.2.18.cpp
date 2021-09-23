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

// add the node of head2 to the head1
void combine(lnode *head1,lnode *head2){
    lnode *h1_rear = head1 -> prior,*h2_head = head2 -> next,*h2_rear = head2 -> prior;
    h1_rear -> next = h2_head,h2_head -> prior = h1_rear;
    head1 -> prior = h2_rear,h2_rear -> next = head1;
    free(head2);
}

int main(){
    freopen("list.txt","r",stdin);

    int len1 = read(num);
    lnode *L1 = (lnode *)malloc(sizeof (lnode));
    build(L1,num,len1);
    // just insert the head
    lnode *head1 = (lnode *)malloc(sizeof(lnode));
    head1 -> next = L1;
    head1 -> prior = L1 -> prior;
    L1 -> prior -> next = head1;
    L1 -> prior = head1;

    num.clear();
    int len2 = read(num);
    lnode *L2 = (lnode *)malloc(sizeof (lnode));
    build(L2,num,len2);
    // just insert the head
    lnode *head2 = (lnode *)malloc(sizeof(lnode));
    head2 -> next = L2;
    head2 -> prior = L2 -> prior;
    L2 -> prior -> next = head2;
    L2 -> prior = head2;

    disp2dl(head1);
    disp2dl(head2);

    // combine the two circle two direction list
    // here we add h2 to the h1
    combine(head1,head2);
    printf("combine\n");
    disp2dl(head1);
    return 0;
}