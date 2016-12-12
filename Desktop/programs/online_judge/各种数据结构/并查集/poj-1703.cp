#include <bits/stdc++.h>
using namespace std;
#define MAX_N 233333
int parents[MAX_N], ranks[MAX_N], id[MAX_N];
inline
void init(int n) {
    memset(ranks,0,sizeof(ranks));
    memset(id,0,sizeof(id));
    for (int i = 0; i < n; ++i) parents[i] = i;
}
int find(int a) {
    if (parents[a]==a) return a;
    return (parents[a]=find(parents[a]));
}
inline
void unions(int a, int b) {
    int pa=find(a), pb=find(b);
    if (pa==pb) return;
    if (ranks[pa]<ranks[pb]) {
        parents[pa] = pb;
    } else {
        if (ranks[pa]==ranks[pb]) ++ranks[pa];
        parents[pb] = pa;
    }
}
int main() {
    int n, m, k, l, t;
    char c;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d",&n,&m);
        init(n*2);
        for (int i = 0; i < m; ++i) {
            cin.ignore();
            scanf("%c%d%d",&c,&k,&l);
            if (c=='D') {
                unions(k,l+n); unions(k+n,l);
            } else {
                if (find(k)==find(l)) {
                    printf("In the same gang.\n");
                } else if (find(k)==find(l+n)) {
                    printf("In different gangs.\n");
                } else {
                    printf("Not sure yet.\n");
                }
            }
        }
    }
}
