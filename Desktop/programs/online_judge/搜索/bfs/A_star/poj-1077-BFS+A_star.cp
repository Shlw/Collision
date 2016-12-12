//getchar()需判断是否为eof或'\n'。
//while(cin.getline(s,length))可以成立，到末位自会break。另外实际输入的字符为length-1。
//在前一个cin后立刻getline会得到一个空行，这是因为cin不处理换行符。请使用cin.ignore(0x7fffffff,'\n')，无视之前的换行符。
//%0xd == 前导零#include <iostream>
//map如果访问了未包含的key，会自动创建一个。
//两个iterator不可以用大于／小于号比较。
//链表在用iterator遍历时，如果erase了元素，原来的iterator就不可用了，若要继续遍历必须使用it=list.erase(...)语句重置iterator（删除后就不用++it了）。
//cin.peek()观测输入的第一个字符（返回char） cin.peek() == '\n' 判断输入了换行符
//unsigned int 1<<32及以上为什么等于3520 / 3504？
//memset是按字节赋值的！对int数组a用memset(a, 1, sizeof(a))会导致数组a中的值变为0x0101！！
//dijkstra（以及其他图论的题）的时候小心输入数据有重边：1 2 3\n1 2 4\n应该取1 2 3
//sprintf()要保证char足够大（别忘了\0），否则写地址就会写到之前的变量里。
//不要随便操作循环变量！！！！

//void my_sort(void * base, size_t length, size_t width, int (* _Nonnull)(const void *, const void *));

//#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>
// *** STL - algorithm *** //
#include <algorithm>
// *** STL - continer *** //
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>
// *** OpenGL *** //
#include <Carbon/Carbon.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

//#define MATH_PI 3.141592653589793
//#define MAX_LEN 111
//#define MAX_N 233333
//#define BITS_PER_INT 32
//#define INF 0x3f3f3f3f
// ****** bored with 'for(foo; foo; foo)' ****** //
//#define FIN(i,N) for(i=0;i<(N);++i)
#define FIN1(i,N) for(i=1;i<=(N);++i)
//#define FINM(i,N) for(i=((N)-1);i>=0;--i)
//#define FINM1(i,N) for(i=(N);i>=1;--i)
// * bored with 'memset(foo, foo, foo)' either * //
//#define CLM(arr,val) memset(arr,val,sizeof(arr))
// ****** count the code's execution time ****** //
#define INITICK clock_t ___START___, ___END___, ___DUR___
#define TICK ___START___ = clock()
#define COUNT(str) ___END___ = clock(); ___DUR___ = ___END___ - ___START___; printf(#str" used %f ms\n",(double)___DUR___/CLOCKS_PER_SEC * 1000)
typedef long long int ll;
using namespace std;
//#define TEST
#ifdef TEST
int main() {
    freopen("/Users/whitephosphorus/Desktop/in.txt", "w", stdout);
    printf("100 100\n");
    int i;
    srand((unsigned int)time(0));
    FIN(i, 100) printf("%d\n", rand()%100+1);
}
#else // TEST
#define poj_1077


#ifdef poj_1077

// 1 2 3
// 4 5 6
// 7 8 9
// target: 1 2 3 4 5 6 7 8 x
// 876543210
// example: 2 3 4 1 5 x 7 6 8 => 978532140

const int minlen[][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,1,2,1,2,3,2,3,4},
    {0,1,0,1,2,1,2,3,2,3},
    {0,2,1,0,3,2,1,4,3,2},
    {0,1,2,3,0,1,2,1,2,3},
    {0,2,1,2,1,0,1,2,1,2},
    {0,3,2,1,2,1,0,3,2,1},
    {0,2,3,4,1,2,3,0,1,2},
    {0,3,2,3,2,1,2,1,0,1},
    {0,4,3,2,3,2,1,2,1,0}
},       dir[] = { 1 ,-1 , 3 ,-3 };
string dir_s[] = {"r","l","d","u"};

struct state {
    string path;
    int st[10], score, sx;
    state() {}
    state(string p, int *s, int c, int x): path(p), score(c), sx(x) {
        memcpy(st, s, sizeof(st));
    }
    
    // 用greater的pque要重载大于号，用less的pque要重载小于号
    friend bool operator >(const state &a, const state &b) {
        if (a.score == b.score)
            return (a.path.length() > b.path.length());
        return (a.score > b.score);
    }
};

// 判断某个状态是否访问过
map<ll, bool> visited;

// 将数组中存放的当前状态用一个九位数表示，第i位表示第i个位置是几，x所在位为0
inline
ll arrtoll(int *mp) {
    int i; ll r=0;
    FIN1(i, 9) { r+=mp[i]; r*=10; }
    return r/10;
}

inline
bool check_ok(int *mp) {
    int i;
    FIN1(i, 8) if (mp[i]!=i) return false;
    return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE
    // sx: x所在位置； x: x将到达位置； sc: 父节点估分； sct: 子节点估分； mp: 存放每个状态，mp[i]为第i位是几，x为0
    int i, sx = 0, x, sc = 0, sct, mp[10]={0};
    ll tmp;
    char t;
    bool ok = false; // 是否已找到路径
    string pt; // 存放路径
    state hd; // 父节点
    priority_queue<state, vector<state>, greater<state>> que; // 按照估分从低到高的优先队列
    FIN1(i, 9) {
        scanf(" %c ", &t);
        t == 'x' ? sx = i : mp[i] = t - '0';
    }
    
    // 计算根节点的估分（规则见下）
    FIN1(i, 9) sc += abs(minlen[i][mp[i]]);
    que.push(state("",mp,sc,sx));
    visited[arrtoll(mp)] = true;
    while (!que.empty() && !ok) {
        hd = que.top(); pt = hd.path; sc = hd.score; sx = hd.sx; memcpy(mp, hd.st, sizeof(mp));
        que.pop();
        for (i = 0; i < 4; ++i) {
            // 除了下标越界和已访问过的情况外，类似3走到4、7走到6也是不合法的
            if ((x = sx + dir[i]) < 1 || x > 9 ||
                (sx % 3 == 0 && dir[i] == 1) || (sx % 3 == 1 && dir[i] == -1)) continue;
            // 暂时交换x和目的地数字
            mp[sx] = mp[x]; mp[x] = 0;
            if (!visited[(tmp = arrtoll(mp))]) {
                visited[tmp] = true;
                // A*，估价函数为已走过的路程+预计还要走的路程（用各数字到目的地的最短长度估计）
                // 这里只需要用父节点的估分计算即可
                sct = sc - minlen[mp[sx]][x] + minlen[mp[sx]][sx] + (int)pt.length()+1;
                // 找到了
                if (check_ok(mp)) {
                    cout << (pt + dir_s[i]) << endl;
                    ok = true; break;
                }
                que.push(state(pt + dir_s[i], mp, sct, x));
            }
            // 再换回来以继续搜索
            mp[x] = mp[sx]; mp[sx] = 0;
        }
    }
    if (!ok) printf("unsolvable\n");
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}
#elif defined poj_2823_3078_2999
struct state {
    int x, y, t;
    state() {}
    state(int x, int y, int t): x(x), y(y), t(t) {}
};

const int dir[][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int findMinRoad(int sx, int sy, int ex, int ey, char mp[][9], bool I = false) {
    queue<state> que;
    state head;
    int i, x0, y0, t, x, y;
    bitset<64> visited(0); visited[sx*8+sy] = 1;
    que.push(state(sx, sy, 0));
    while (!que.empty()) {
        head = que.front(); x0 = head.x; y0 = head.y; t = head.t;
        for (i = 0; i < 4; ++i) {
            x = x0 + dir[i][0]; y = y0 + dir[i][1];
            // prune when meeting an agent because 'I' will be eliminated
            // if the agent always stops at his/her place
            if (x < 0 || y < 0 || x > 7 || y > 7 || visited[x*8+y] ||
                mp[x][y] == '#' || (I && mp[x][y] == 'A')) continue;
            // find the shortest road for every phone
            if (x == ex && y == ey)
                return t+1;
            visited[x*8+y] = 1;
            que.push(state(x, y, t+1));
        }
        que.pop();
    }
    return INF;
}

// Floyd大法好！！！O(n^3)保平安！！！
void findMinRoad(char mp[][9], int m[][64]) {
    int i, j, k;
    for (i = 0; i < 64; ++i)
        for (j = 0; j < 64; ++j)
            for (k = 0; k < 64; ++k)
                m[i][j] = m[i][j] > mp[i/8][k]
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE
    int t, i, j, sx, sy, ex1, ex2, ey1, ey2, pnum, tmp, dis1, dis2; scanf("%d", &t);
    char mp[9][9]; int MinRoads[64][64];
    while (t--) {
        bool esc = false, trap = true;
        sx=sy=ex1=ex2=ey1=ey2=-1; pnum=dis1=dis2=0; memset(MinRoads, INF, sizeof(MinRoads));
        for (i = 0; i < 8; ++i) {
            cin.ignore();
            for (j = 0; j < 8; ++j) {
                MinRoads[i*8+j][i*8+j] = 0;
                scanf("%c", &mp[i][j]);
                if (mp[i][j] != '#') {
                    if (j) MinRoads[i*8+j][i*8+j-1] = MinRoads[i*8+j-1][i*8+j] = 1;
                    if (j < 7) MinRoads[i*8+j][i*8+j+1] = MinRoads[i*8+j+1][i*8+j] = 1;
                    if (i) MinRoads[i*8+j][i*8+j-8] = MinRoads[i*8+j-8][i*8+j] = 1;
                    if (i < 7) MinRoads[i*8+j][i*8+j+8] = MinRoads[i*8+j+8][i*8+j] = 1;
                    if (mp[i][j] == 'M') {
                        sx = i; sy = j;
                    } else if (mp[i][j] == 'A') {
                        if (ex1 == -1) {
                            ex1 = i; ey1 = j;
                        } else {
                            ex2 = i; ey2 = j;
                        }
                    } else if (mp[i][j] == 'P') ++pnum;
                }
            }
        }
        cin.ignore();
        for (int i = 0; i < 8 && !esc; ++i)
            for (int j = 0; j < 8 && !esc; ++j)
                if (mp[i][j] == 'P')
                    if ((tmp = findMinRoad(sx, sy, i, j, mp, true)) <
                        findMinRoad(ex1, ey1, i, j, mp) &&
                        tmp < findMinRoad(ex2, ey2, i, j, mp))
                        esc = true;
        
        if (esc) { printf("You can escape.\n"); continue; }
        
        if ((dis1 = findMinRoad(sx, sy, ex1, ey1, mp)) != INF ||
            (dis2 = findMinRoad(sx, sy, ex2, ey2, mp)) != INF)
            trap = false;
        
        
        
        if (trap) printf("You are trapped in the Matrix.\n");
        else printf("You are eliminated.\n");
    }
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}
#endif // poj_xxxx
#endif // TEST
/*
// 并查集模版
int parents[MAX_N], ranks[MAX_N];
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
*/
