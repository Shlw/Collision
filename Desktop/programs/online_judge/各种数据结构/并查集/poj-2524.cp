#include <bits/stdc++.h>
using namespace std;
int parents[66666], ranks[66666];
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
        parents[pb] = pa;
        if (ranks[pa]==ranks[pb]) ++ranks[pa];
    }
}
int main() {
    int n, m, a, b, c=0, r;
    while (scanf("%d%d",&n,&m)!=EOF&&m&&n) {
        init(n); r = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d",&a,&b);
            unions(a-1,b-1);
        }
        for (int i = 0; i < n; ++i) if (parents[i]==i) ++r;
        printf("Case %d: %d\n", ++c, r);
    }
}
