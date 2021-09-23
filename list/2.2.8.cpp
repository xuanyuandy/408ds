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

int getlen(lnode *head){
    int res = 0;
    while(head -> next){
        res ++;
        head = head -> next;
    }
    return res;
}

// return the first same element
int getsame(lnode *head1,lnode *head2){
    int len1 = getlen(head1),len2 = getlen(head2);
    lnode *longl,*shortl;
    int dist = 0;
    if(len1 >= len2){
        longl = head1 -> next,shortl = head2 -> next;
        dist = len1 - len2;
    }else{
        longl = head2 -> next,shortl = head1 -> next;
        dist = len2 - len1;
    }
    while(dist --) longl = longl -> next;
    // the long and short list have the same length
    while(longl){
        if(longl -> val == shortl -> val){
            return longl -> val;
        }else{
            longl = longl -> next;
            shortl = shortl -> next;
        }
    }  
    return -1;
}

/*
2 3 45 6 0 3 3 3 45 45 
123 3445 435435534 110 34 0 3 3 3 45 45
*/
int main(){
    freopen("list.txt","r",stdin);
    // list1
    int len = read(num);
    lnode *L = (lnode *)malloc(sizeof (lnode));
    build(L,num,len);
    displ(L);
    // just add the head
    lnode *head = (lnode *)malloc(sizeof(lnode));
    head -> next = L;

    // list2
    num.clear();
    int len2 = read(num);
    lnode *L2 = (lnode *)malloc(sizeof (lnode));
    build(L2,num,len2);
    displ(L2);
    // just add the head
    lnode *head2 = (lnode *)malloc(sizeof(lnode));
    head2 -> next = L2;

    cout << getsame(head,head2) << endl;


    
    return 0;
}