#include <iostream>

using namespace std;

const int N = 100010, M = 1000010;

int n, m;
// ne[i] should lower than i to make sequence must shorter than the primary sequence
int ne[N];
char s[M], p[N];

int main()
{
    cin >> n >> p + 1 >> m >> s + 1;

    ne[0] = -1; // this means ne cannot skip back
    ne[1] = 0;
    for(int i = 2,j = 0;i <= n;i ++){
        while(j != -1 && p[j + 1] != p[i]) j = ne[j];
        ne[i] = ++ j;
    }

    for(int i = 1,j = 0;i <= m;i ++){
        while(j != -1 && p[j + 1] != s[i]) j = ne[j];
        j ++;
        if(j == n){
            printf("%d ",i - n);
            j = ne[j];
        }
    }
    return 0;
}
