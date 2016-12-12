#include <bits/stdc++.h>
#define MO 10000
#define BASE 2011
using namespace std;
inline
int m(int a) {
    int r = 1, t = BASE;
    for (; a; a >>= 1) {
        if (a%2) r = (r * t % MO);
        t *= t; t %= MO;
    }
    return r;
}
int main() {
    char c[222]; int r; scanf("%d",&r);
    while(r--) {
        memset(c,0,sizeof(c));
        scanf("%s", c);
        int l = strlen(c)-1, t = c[l]-'0'+(l>0?(c[l-1]-'0')*10:0)+(l>1?(c[l-2]-'0')*100:0);
        printf("%d\n",m(t));
    }
}
