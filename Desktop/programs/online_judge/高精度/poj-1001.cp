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
#define MAX_LEN 210

using namespace std;
typedef long long int ll;

struct a{
    int x[MAX_LEN];
    int dot; // 0 => integer
    bool operator ==(a num2) {
        int i;
        FIN(i, MAX_LEN) {
            if (num2.x[i] != this->x[i]) return false;
        }
        return true;
    }
    bool operator ==(int num2) {
        int i;
        FIN(i, this->dot) {
            if (this->x[i]) return false;
        }
        char st[MAX_LEN];
        sprintf(st, "%d", num2);
        for (i = this->dot; i < strlen(st) + this->dot; ++i) {
            if (st[strlen(st) + this->dot - i - 1] - '0' != this->x[i]) return false;
        }
        for (i = (int)strlen(st) + this->dot; i < MAX_LEN; ++i) {
            if (this->x[i]) return false;
        }
        return true;
    }
    bool operator !() {
        return (*this == 0);
    }
    a operator *(a num2) {
        a rst;
        int i, j;
        memset(rst.x, 0, sizeof(rst.x));
        rst.dot = 0;
        FIN(i, MAX_LEN / 2) {
            FIN(j, MAX_LEN / 2) {
                rst.x[i + j] += this->x[i] * num2.x[j];
            }
        }
        FIN(i, MAX_LEN - 1) {
            rst.x[i+1] += rst.x[i] / 10;
            rst.x[i] %= 10;
        }
        rst.dot = this->dot + num2.dot;
        return rst;
    }
    a operator ^(int exp) {
        a rst;
        int i;
        memset(rst.x, 0, sizeof(rst.x));
        rst.dot = 0;
        if (*this == 0) return rst;
        rst.x[0] = 1;
        if (*this == 1) return rst;
        switch (exp) {
            case 0:
                break;
            case 1:
                memcpy(rst.x, this->x, sizeof(this->x));
                rst.dot = this->dot;
                break;
            default:
                FIN1(i, exp) {
                    rst = rst * (*this);
                }
        }
        return rst;
    }
}r,m;

int main() {
    string s;
    int i, j, k, fzero_count, bzero_count;
    bool to_print_dot = false, ignore_zero = true;
    a num1, rst;
    while(cin >> s >> k){
        j = bzero_count = fzero_count = to_print_dot = 0; ignore_zero = 1;
        memset(num1.x, 0, sizeof(num1.x));
        num1.dot = 0;
        FINM(i, (int)s.length()) {
            if(s[i] != '.') { num1.x[j++] = s[i] - '0'; } else { num1.dot = j; };
        }
        rst = num1 ^ k;
        if (!rst) {
            cout << "0" << endl;
        } else {
            FINM(i, MAX_LEN - 1) {
                if (rst.dot <= i) { // before the dot
                    if (rst.x[i]) {
                        if (ignore_zero) {
                            ignore_zero = false;
                        } else while (fzero_count--) cout << "0";
                        fzero_count = 0; to_print_dot = false;
                        cout << rst.x[i];
                    } else {
                        if (ignore_zero) ++fzero_count; else cout << "0";
                    }
                    if (rst.dot == i && i) {
                        to_print_dot = true;
                    }
                } else {
                    if (rst.x[i]) {
                        if (to_print_dot) { cout << "."; to_print_dot = false; }
                        while (bzero_count--) cout << "0";
                        bzero_count = 0;
                        cout << rst.x[i];
                    } else {
                        ++bzero_count;
                    }
                }
            }
            cout << endl;
        }
    }
    return 0;
}
/*
int BossMap[MAX_LEN][MAX_LEN] = {{0}}, path[MAX_LEN][MAX_LEN] = {{0}},
stones[MAX_LEN][MAX_LEN] = {{0}};
int r, c, k, cd = 0;
int doors[10][2] = {{0}};
const int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

struct pos {
    int x;
    int y;
    string stone;
    //int state; // stone
} tmp;

int bfs(int x0, int y0) {
    int i, x1, y1, x, y, t = 0, state, ts, oc;
    string stone = "", st = ""; char ct[8];
    queue<pos> que;
    tmp.x = x0; tmp.y = y0; tmp.stone = "";//tmp.state = 0;
    que.push(tmp);
    while (!que.empty()) {
        x = que.front().x; y = que.front().y; //state = que.front().state;
        t = path[x][y];
        FIN(i,4) {
            stone = que.front().stone;
            x1 = x + dir[i][0]; y1 = y + dir[i][1];
            if (x1 < r && x1 >= 0 && y1 < c && y1 >= 0 &&
                BossMap[x1][y1] != '#' && stone != "") { // && ((1 << state) & ~stones[x1][y1])) {
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
                        tmp.x = x1; tmp.y = y1; //tmp.state = state;
                        que.push(tmp);
                        break;
                    default:
                        sprintf(ct, "%d" ,x1);
                        st = ct;
                        stone.append(st); st += " ";
                        sprintf(ct, "%d" ,y1);
                        st = ct;
                        stone.append(st); st += " ";
                        //path[x1][y1] |= (1 << (BossMap[x1][y1] - '0'));
                        tmp.x = x1; tmp.y = y1; //tmp.state = state | (1 << (BossMap[x1][y1] - '0'));
                        tmp.stone = stone;
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
                    tmp.x = x1; tmp.y = y1; //tmp.state = state;
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
//00000000 00000000 00000000 00000000
//tttttttt tttttttt tttttttt ttt43210
/*
int BossMap[MAX_LEN][MAX_LEN] = {{0}}, path[MAX_LEN][MAX_LEN] = {{0}};
// 00000000 0_______
int r, c, k;
const int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

struct pos {
    int x;
    int y;
    int state; // time % k
} tmp;

int bfs(int x0, int y0) {
    int i, x1, y1, x, y, t = 0, state, ts;
    queue<pos> que;
    tmp.x = x0; tmp.y = y0; tmp.state = 0;
    que.push(tmp);
    while (!que.empty()) {
        x = que.front().x; y = que.front().y; state = que.front().state; t = path[x][y];
        FIN(i,4) {
            ts = (state + 1) == k ? 0 : state + 1;
            x1 = x + dir[i][0]; y1 = y + dir[i][1];
            if (x1 < r && x1 >= 0 && y1 < c && y1 >= 0 &&
                (!ts || (BossMap[x1][y1] & 127) != '#') &&
                ((1 << ts) & ~BossMap[x1][y1] >> 7)) {
                BossMap[x1][y1] |= (1 << (ts + 7));
                path[x1][y1] = t + 1;
                switch (BossMap[x1][y1] & 127) {
                    case 'E':
                        return (t + 1);
                        break;
                    case '.': case 'S': case '#':
                        tmp.x = x1; tmp.y = y1; tmp.state = ts;
                        que.push(tmp);
                        break;
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
            }
        }
        rst = bfs(startx, starty);
        if (rst) cout << rst << endl; else cout << "oop!" << endl;
        memset(BossMap,0,sizeof(BossMap));
        memset(path,0,sizeof(path));
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
