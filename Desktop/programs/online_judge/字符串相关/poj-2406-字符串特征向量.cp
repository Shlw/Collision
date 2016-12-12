//getchar()需判断是否为eof或'\n'。
//while(cin.getline(s,length))可以成立，到末位自会break。另外实际输入的字符为length-1。
//在前一个cin后立刻getline会得到一个空行，这是因为cin不处理换行符。请使用cin.ignore(0x7fffffff,'\n')，无视之前的换行符。
//%0xd == 前导零#include <iostream>
//map如果访问了未包含的key，会自动创建一个。
//两个iterator不可以用大于／小于号比较。
//链表在用iterator遍历时，如果erase了元素，原来的iterator就不可用了，若要继续遍历必须使用it=list.erase(...)语句重置iterator（删除后就不用++it了）。
//cin.peek()观测输入的第一个字符（返回char） cin.peek() == '\n' 判断输入了换行符

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <list>
#define FIN(i,N) for(i=0;i<(N);++i)
#define FIN1(i,N) for(i=1;i<=(N);++i)
#define FINM(i,N) for(i=((N)-1);i>=0;--i)
#define FINM1(i,N) for(i=(N);i>=1;--i)
#define inf 1<<30 // 2*inf<=2^31, 1<<30 is good
#define iginf 0x7fffffff // 2147483647
#define MAX_LEN 1000010
using namespace std;
typedef long long int ll;

int len;
char s[MAX_LEN];
int charVec[MAX_LEN];

void calc() {
    int i;
    charVec[0] = 0;
    FIN1(i,len-1) {
        for(int j = charVec[i - 1]; j >= 0; j = charVec[j - 1]) {
            if (s[i] == s[j]) {
                charVec[i] = j + 1;
                break;
            }
            if (!j) {
                if (s[0] == s[i]) charVec[i] = 1; else charVec[i] = 0;
                break;
            }
        }
    }
}

int main() {
    while (scanf("%s", s)!=EOF) {
        if (s[0] == '.') break;
        len = (int)strlen(s);
        calc();
        if (!(len % (len - charVec[len - 1]))) {
            cout << len / (len - charVec[len - 1]) << endl;
        } else cout << 1 << endl;
        memset(s,0,sizeof(s));
        memset(charVec,-1,sizeof(s));
    }
    return 0;
}

/*
//00000000 00000000 00000000 00000000
//tttttttt tttttttt tttttttt ttt43210
int BossMap[MAX_LEN][MAX_LEN] = {{0}}, path[MAX_LEN][MAX_LEN] = {{0}},
    stones[MAX_LEN][MAX_LEN] = {{0}};
int r, c, k, cd = 0;
int doors[10][2] = {{0}};
const int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
*/
/*
1
7 8 2
00000000
00S00#00
0##0#000
00#0#000
00#1#000
000##E00
00000000
*/
/*
struct pos {
    int x;
    int y;
    int state; // stone
} tmp;

int bfs(int x0, int y0) {
    int i, x1, y1, x, y, t = 0, state, ts, oc;
    queue<pos> que;
    tmp.x = x0; tmp.y = y0; tmp.state = 0;
    que.push(tmp);
    while (!que.empty()) {
        x = que.front().x; y = que.front().y; state = que.front().state; t = path[x][y];
        FIN(i,4) {
            x1 = x + dir[i][0]; y1 = y + dir[i][1];
            if (x1 < r && x1 >= 0 && y1 < c && y1 >= 0 &&
                BossMap[x1][y1] != '#' && ((1 << state) & ~stones[x1][y1])) {
                stones[x1][y1] |= (1 << state);
                path[x1][y1] = t + 1;
                switch (BossMap[x1][y1]) {
                    case 'E':
                    ts = state;
                    for (oc = 0; ts; ++oc) {
                        ts &= (ts - 1); // count '1's in state
                    }
                    if (oc >= k) {
                        return (t + 1);
                    }
                    break;
                    case '.': case 'S': case '$':
                    tmp.x = x1; tmp.y = y1; tmp.state = state;
                    que.push(tmp);
                    break;
                    default:
                    path[x1][y1] |= (1 << (BossMap[x1][y1] - '0'));
                    tmp.x = x1; tmp.y = y1; tmp.state = state | (1 << (BossMap[x1][y1] - '0'));
                    que.push(tmp);
                }
                
            }
        }
        if (BossMap[x][y] == '$') {
            FIN(i,cd) {
                x1 = doors[i][0]; y1 = doors[i][1];
                if (x1 == x && y1 == y) continue;
                if ((1 << state) & ~stones[x1][y1]) {
                    stones[x1][y1] |= (1 << state);
                    path[x1][y1] = t + 1;
                    tmp.x = x1; tmp.y = y1; tmp.state = state;
                    que.push(tmp);
                }
            }
        }
        que.pop();
    }
    return 0;
}

int main() {
    int n, i, j, startx = 0, starty = 0, rst;
    char g[MAX_LEN];
    cin >> n;
    while (n--) {
        cin >> r >> c >> k;
        cin.ignore(iginf, '\n');
        FIN(i,r) {
            cin.getline(g, c+1);
            FIN(j,c) {
                BossMap[i][j] = g[j];
                if (g[j] == 'S') { startx = i; starty = j; }
                if (g[j] == '$') { doors[cd][0] = i; doors[cd][1] = j; ++cd; }
            }
        }
        rst = bfs(startx, starty);
        if (rst) cout << rst << endl; else cout << "oop!" << endl;
        memset(BossMap,0,sizeof(BossMap));
        memset(doors,0,sizeof(doors));
        memset(path,0,sizeof(path));
        memset(stones,0,sizeof(stones));
        cd = 0;
    }
    
    return 0;
}
*/
/*
int BossMap[MAX_LEN][MAX_LEN] = {{0}};
int path[MAX_LEN][MAX_LEN] = {{0}};
// each element has 32 bits, the lowest 5 bits store the state which stones the hero has got
// the mid 4 bits store the direct the hero has visited
// and the other 23 bits store the time the hero used (<= 2^23-1 = 8388607)
//bool DirVisited[MAX_LEN][MAX_LEN] = {{0}};
int r, c, k, min_time = inf, doors[10][2]={{0}}, cd = 0;
const int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
queue<pair<int, int>> que;

int bfs(int x, int y) {
    int x1, y1, i, t0 = 0, state = 0;
    bool tp = false;
    pair<int, int> xy;
    que.push(pair<int, int>(x, y));
    while (!que.empty()) {
        xy = que.front();
        FIN(i,4) {
            state = path[xy.first][xy.second] & 31;
            t0 = path[xy.first][xy.second] >> 5;
            x1 = xy.first + dir[i][0];
            y1 = xy.second + dir[i][1];
            if (x1 >= 0 && y1 >= 0 && x1 < r && y1 < c && BossMap[x1][y1] != '#') {
                if ((path[x1][y1] >> 5) && (path[x1][y1] & 31) == state) continue;
                if (!state && x1 == x && y1 == y) continue;
                tp = false;
                switch (BossMap[x1][y1]) {
                    case 'E':
                    int oc;
                    for (oc = 0; state; ++oc) {
                        state &= (state - 1); // count '1's in state
                    }
                    if (oc >= k) {
                        return (t0 + 1);
                    }
                    break;
                    case '.': case'S': break;
                    case '$': break;
                    default: path[x1][y1] |= (1<<(BossMap[x1][y1]-'0'));
                }
                path[x1][y1] = ((t0 + 1) << 5) + state;
                que.push(pair<int, int>(x1, y1));
            }e
        }
        que.pop();
    }
    return 0;
}

int main() {
    
    int n, i, j, startx = 0, starty = 0;
    char g[MAX_LEN];
    cin >> n;
    while (n--) {
        cin >> r >> c >> k;
        cin.ignore(iginf, '\n');
        FIN(i,r) {
            cin.getline(g, c+1);
            FIN(j,c) {
                BossMap[i][j] = g[j];
                if (g[j] == 'S') { startx = i; starty = j; }
                if (g[j] == '$') { doors[cd][0] = i;
                    doors[cd][1] = j; ++cd; }
            }
        }
        //dps(startx, starty, 0, "");
        //min_time = bfs(startx, starty);
        //if (min_time) cout << min_time << endl; else cout << "oop!" << endl;
        memset(BossMap,0,sizeof(BossMap));
        memset(doors,0,sizeof(doors));
        memset(path,0,sizeof(path));
        min_time = inf;
        cd = 0;
    }
    return 0;
}
*/
/*
 
 void dps(int x, int y, int t, string s) {
 if (t >= min_time) return;
 int i, j, x1, y1;
 char m;
 string ms;
 FIN(i,4) {
 //if (DirVisited[x][y][i]) continue;
 x1 = x + dir[i][0];
 y1 = y + dir[i][1];
 //DirVisited[x][y][i] = true;
 if (x1 >= 0 && y1 >= 0 && x1 < r && y1 < c && BossMap[x1][y1] != '#') {
 //cout << x1 << " " << y1 << endl;
 switch (BossMap[x1][y1]) {
 case '.': case 'S':
 dps(x1, y1, t + 1, s);
 break;
 case '0': case '1': case '2': case '3': case '4':
 m = BossMap[x1][y1]; ms = &m;
 if (s.find(m)) {
 dps(x1, y1, t + 1, s + ms);
 } else {
 dps(x1, y1, t + 1, s);
 }
 break;
 case '$':
 FIN(j,cd) {
 if (doors[j][0] == x1 && doors[j][1] == y1) continue;
 dps(doors[j][0], doors[j][1], t + 1, s);
 }
 break;
 case 'E':
 if (s.length() >= k) {
 if ((t + 1) < min_time) min_time = (t + 1);
 return;
 } else {
 dps(x1, y1, t + 1, s);
 }
 break;
 }
 }
 }
 }
*/
