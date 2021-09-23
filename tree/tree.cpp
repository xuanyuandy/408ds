#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;
const int N = 100,M = 2 * N,root = 1;
int h[N],e[M],ne[M],idx;
int dep[N],n,mxdep = 0;

void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx ++;
}

void dfs(int u){
    cout << u << " ";
    for(int i = h[u]; ~i;i = ne[i]){
        dep[e[i]] = dep[u] + 1;
        dfs(e[i]);
    }
}

int build(){
    memset(h,-1,sizeof h);
    dep[root] = 1;
    int a,b,total = 0;
    string line;
    while(getline(cin,line)){
        stringstream ss(line);
        ss >> a,ss >> b;
        total = max(total,a);
        total = max(total,b);
        add(a,b);
    }
    dfs(root);
    cout << '\n';
    return total;
}

void addnull(int d,vector<vector<int> > &level){
    int res = 1;    
    for(int i = d + 1;i <= mxdep;i ++){
        for(int j = 0;j < res;j ++)
            level[i].push_back(0);
        res *= 2;
    }
}

void construct(int u,vector<vector<int> > &level){
    int son1 = 0,son2 = 0;
    int dp = dep[u];
    level[dp].push_back(u);
    bool first = true;
    for(int i = h[u]; ~i;i = ne[i]){
        int j = e[i];
        if(first) son1 = j,first = false;
        else son2 = j;
        construct(j,level);
    }
    // this node is the last level in the tree
    if(!son1 && dp < mxdep){
        addnull(dp,level);
        addnull(dp,level);
    }else if(son1 && !son2 && dp < mxdep){
        addnull(dp,level);
    }
}

/*
1 
3 2 
5 0 8 4 
7 6 0 0 9 0 0 0 
*/
// we should transform this to a tree 
void format(vector<vector<int> > &level){
    for(int i = 1;i <= mxdep;i ++){
        int w = 1 << (mxdep - i);    
        for(int j = 0;j < 1 << (i - 1);j ++) // %*d是包括当前数总共所占的位置
            printf("%*d%*c",w,level[i][j],w,' ');
        printf("\n");
    }
}

void beautyformat(vector<vector<int> > &level){
    for(int i = 1;i <= mxdep;i ++){
        int w = 1 << (mxdep - i + 2);    
        if(i == 1) printf("%*c\n",w,'_');
        else{
            for(int j = 0;j < 1 << (i - 2);j ++){
                printf("%*c",w + 1,' ');
                for(int k = 0;k < w - 3;k ++)
                    printf("_");
                printf("/ \\");
                for(int k = 0;k < w - 3;k ++)
                    printf("_");
                printf("%*c",w + 2,' ');   
            }
            printf("\n");
        }
        for(int j = 0;j < 1 << (i - 1);j ++)
            printf("%*c%d)%*c",w - 1,'(',level[i][j],w - 1,' ');
        printf("\n");
    }
}

int main(){
    freopen("tree.txt","r",stdin);
    n = build();
    for(int i = 1;i <= n;i ++)
        mxdep = max(mxdep,dep[i]);

    vector<vector<int> > level(mxdep + 1);
    
    construct(root,level);
    beautyformat(level);

    



    return 0;
}