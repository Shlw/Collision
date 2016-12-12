#include <bits/stdc++.h>
using namespace std;
int parents[33333], ranks[33333];
inline
void init(int n) {
    memset(ranks,0,sizeof(ranks));
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
    int n, m, k, l, t, r;
    while (scanf("%d%d",&n,&m)!=EOF&&(m||n)) {
        init(n); r = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d",&k); scanf("%d",&l);
            while (--k) {
                scanf("%d", &t);
                unions(t, l);
            }
        }
        for (int i = 0; i < n; ++i) if (find(i)==find(0)) ++r;
        printf("%d\n", r);
    }
}
