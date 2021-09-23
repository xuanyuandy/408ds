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

// recursive delete the all value x node in this no header single list
// del function return have solved the behind sequence
lnode * del(lnode * L,int x){
    lnode * l = L;
    if(l -> val != x){
        if(l -> next){
            l -> next = del(l -> next,x);
        }
        return l;
    }else{
        if(l -> next){
            return del(l -> next,x);
            free(l);
        }else{
            return NULL;
        }
    }
}

int main(){
    freopen("list.txt","r",stdin);
    int len = read(num);
    
    lnode list;
    lnode * L = &list;
    build(L,num,len);
    displ(L);

    L = del(L,7);
    displ(L);
    
    return 0;
}