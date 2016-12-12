#include <bits/stdc++.h>
using namespace std;
struct state {
    int t, x, y;
    bool fighting;
    state(){}
    state(int t,int x,int y, bool f):t(t),x(x),y(y),fighting(f){}
};
const int dir[][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int main() {
    int n, m, s, i, j, x, y, t, tx, ty, sx, sy=sx=0; scanf("%d",&s);
    while (s--) {
        scanf("%d%d",&n,&m);
        char mp[222][222]={0}, tmp[222];
        bool vis[222][222]={0}, ok=false;
        queue<state> que;
        for (i = 0; i < n; ++i) {
            cin.ignore();
            scanf("%s",tmp);
            for (j = 0; j < m; ++j) {
                mp[i][j] = tmp[j];
                if (mp[i][j]=='r') {sx=i;sy=j;}
            }
        }
        que.push(state(0,sx,sy,false));
        vis[sx][sy]=true;
        while(!que.empty()&&!ok) {
            t=que.front().t; x=que.front().x; y=que.front().y;
            if (mp[x][y]=='x' && que.front().fighting) {
                que.push(state(t+1,x,y,false));
            } else {
                for (i = 0; i < 4; ++i) {
                    tx=x+dir[i][0];ty=y+dir[i][1];
                    if (tx<0||ty<0||tx>=n||ty>=m||vis[tx][ty]||mp[tx][ty]=='#') continue;
                    if (mp[tx][ty] == 'a') {
                        printf("%d\n",t+1);
                        ok = true;
                        break;
                    }
                    que.push(state(t+1,tx,ty,mp[tx][ty]=='x'?true:false));
                    vis[tx][ty]=true;
                }
            }
            que.pop();
        }
        if (!ok) printf("Impossible\n");
    }
}
