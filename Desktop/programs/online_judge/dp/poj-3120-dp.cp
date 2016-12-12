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
#define FIN(i,N) for(i=0;i<(N);++i)
//#define FIN1(i,N) for(i=1;i<=(N);++i)
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
    printf("5040\n");
    int i, t[]={0,1,2,3,4,5,6};
    //srand((unsigned int)time(0));
    FIN(i, 5040) {printf("%d%d%d%d%d%d%d\n",t[0],t[1],t[2],t[3],t[4],t[5],t[6]); next_permutation(t,t+7);}
}
#else // TEST
#define poj_3120


#ifdef poj_1080

int score[128][128] = {{0}};

inline
void init() {
    score['A']['A'] = score['G']['G'] = score['C']['C'] = score['T']['T'] = 5;
    score['A']['C'] = score['C']['A'] = score['-']['T'] = score['T']['-'] = -1;
    score['A']['T'] = score['T']['A']                                     = -1;
    score['A']['G'] = score['G']['A'] = score['-']['G'] = score['G']['-'] = -2;
    score['T']['C'] = score['C']['T'] = score['G']['T'] = score['T']['G'] = -2;
    score['G']['C'] = score['C']['G'] = score['-']['A'] = score['A']['-'] = -3;
    score['C']['-'] = score['-']['C']                                     = -4;
}

// assume that m >= n
int solve(char *a, char *b, int m, int n) {
    int i, j, dp[111][111] = {{0}};
    dp[0][0] = score[a[0]][b[0]];
    dp[0][1] = score[a[0]]['-'];
    for (i = 1; i < m; ++i)
        for (j = (i < n ? 0 : i-n+1); j <= (i < m-n ? i+1 : m-n); ++j)
            dp[i][j] = (j ? max(dp[i-1][j-1] + score[a[i]]['-'], dp[i-1][j] + score[a[i]][b[i-j]]) : (dp[i-1][0] + score[a[i]][b[i]]));
    return dp[m-1][m-n];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE

    int t; scanf("%d", &t);
    init();
    while (t--) {
        int n, m;
        char a[111], b[111];
        scanf("%d %s %d %s", &n, a, &m, b);
        printf("%d\n", n >= m ? solve(a, b, n, m) : solve(b, a, m, n));
    }
    
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}

#elif defined poj_3120

inline
bool valid(int x1, int y1, int x2, int y2, int d) {
    return (sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)) <= d);
}

inline
bool OutOfRange(int x, int y) {
    return (x<0||y<0||x>32||y>32);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE
    
    int n, d, m, i, x, y, fx, fy, xstep, ystep, t, mt=0;
    while (scanf("%d%d%d",&n,&d,&m) != EOF && n && d && m) {
        int mp[33][33][11]={0}, dp[33][33][11]={0};
        for (i = 0; i < m; ++i) {
            scanf("%d%d%d",&x,&y,&t);
            // record the max t appeared in input and it will sharply make the program faster
            mt = (mt < t ? t : mt);
            // negative coordinates are possible, so add 5 to avoid negative index
            mp[x+5][y+5][t] = 1;
        }
        // DP: when t time steps passed, the point P's score equals to the maximum of
        // P0's score + mice between the path from P0 to P, where |P0P| <= d
        for (t = 1; t <= mt; ++t) {
            // n+5 results WA, n+6 results AC, i don't know why!!!?????
            for (x = 0; x <= n+6; ++x) {
                for (y = 0; y <= n+6; ++y) {
                    // deal with the case xstep == ystep == 0
                    dp[x][y][t] = dp[x][y][t-1] + mp[x][y][t];
                    // visit all integer coordinates
                    for (fx = x, fy = y, xstep = -d; xstep <= d; ++xstep) {
                        for (ystep = -d; ystep <= d; ++ystep) {
                            // if xstep == ystep == 0, the program will loop forever,
                            // so deal with it outside (vide supra)
                            if (!xstep && !ystep) continue;
                            int mice = 0;
                            // visit the path
                            while (valid(fx, fy, x, y, d) && !OutOfRange(fx, fy)) {
                                // note that the mice will accumulate,
                                // and this is exactly what we want -- count all the mice in the path
                                mice += mp[fx][fy][t];
                                dp[x][y][t] = (dp[x][y][t] > dp[fx][fy][t-1] + mice ?
                                               dp[x][y][t] : dp[fx][fy][t-1] + mice);
                                fx += xstep; fy += ystep;
                            }
                            fx = x; fy = y;
                        }
                    }
                }
            }
        }
        // search the max score
        int rst = 0;
        for (x = 0; x <= n+6; ++x)
            for (y = 0; y <= n+6; ++y)
                rst = (rst > dp[x][y][mt] ? rst : dp[x][y][mt]);
        printf("%d\n", rst);
    }
    
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}

#elif defined poj_test
#define MO 10000
#define BASE 2011
#define MAX_I 23333

int m(int a) {
    int r = 1, t = BASE;
    for (; a; a >>= 1) {
        if (a%2) { r *= t; r%=MO; }
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

#elif defined poj_1661
#define INF 0x3f3f3f3f
struct board {
    int x1, x2, y;
    int t1, t2;
    bool base;
} boards[2222];

int my_cmp(const void *a, const void *b) {
    return ((board *)b)->y - ((board *)a)->y;
}

int main() {
    INITICK;
    TICK;
    
    int t; scanf("%d",&t);
    while (t--) {
        memset(boards, 0, sizeof(boards));
        int i, j, n, x, y, m, dx1, dx2, dy, dt, rst=INF; scanf("%d%d%d%d",&n,&x,&y,&m);
        // add a virtual board for Jimmy's initial position
        boards[0].x1=boards[0].x2=x; boards[0].y=y; boards[0].t1 = boards[0].t2 = 0;
        for (i=1;i<=n;++i) {
            scanf("%d%d%d",&boards[i].x1,&boards[i].x2,&boards[i].y);
            boards[i].t1 = boards[i].t2 = INF;
        }
        // sort by the height of boards
        qsort(boards, n, sizeof(board), my_cmp);
        // DP
        // note that this occasion may occurs(case #1):
        //    __A__
        // _____B_____
        // _C_ _D_ _E_
        // in this case, it's impossible for Jimmy to jump directly from A to C,D,E or lower boards.
        // (in fact, he even cannot reach board C,D and E.)
        // and in this case(case #2):
        //     _A_
        //  __B__
        // __C__ _D_
        // Jimmy is unable to jump from A to C, but he can jump to D.
        for (i = 1; i <= n; ++i) {
            for (j = i-1; j >= 0; --j) {
                dy = boards[j].y - boards[i].y;
                dx1 = boards[j].x1 - boards[i].x1; dx2 = boards[i].x2 - boards[j].x2;
                // it is impossible to jump from boards[j] to boards[i]
                if (!dy || dy > m || (dx1 <= 0 && dx2 <= 0))
                    break;
                // Jimmy is able to jump from boards[j] to boards[i] on the left side ...
                if (dx1 > 0) {
                    dt = boards[j].t1 + dx1;
                    boards[i].t1 = (boards[i].t1 > dt ? dt : boards[i].t1);
                }
                // ... and so as the right side
                if (dx2 > 0) {
                    dt = boards[j].t2 + dx2;
                    boards[i].t2 = (boards[i].t2 > dt ? dt : boards[i].t2);
                }
            }
        }
        // deal with final result
        
        for (i = 0; i <= n && boards[i].y <= m; ++i) {
            bool base = true;
            for (j = i+1; j <= n && base; ++j) {
                dx1 = boards[j].x1 - boards[i].x1; dx2 = boards[i].x2 - boards[j].x2;
                if (dx1 <= 0 && dx2 <= 0)
                    base = false;
            }
            boards[i].base = base;
        }
        
        for (j = n; j > 0; --j) {
            if (boards[j].y > m || !boards[j].base) continue;
            // searching from both sides
            dt = (boards[j].t1 > boards[j].t2 ? boards[j].t2 : boards[j].t1);
            rst = (rst > dt ? dt : rst);
        }
        printf("%d\n", rst+y);
    }
    
    COUNT(the program);
}

#elif defined poj_2989

struct st {
    char n[8];
    int t, e, score;
    st(){}
    st(char *N, int t, int e, int s): t(t), e(e), score(s) { memcpy(n, N, sizeof(n)); }
    
    st &swap(int i, int j) {
        n[i] ^= n[j];
        n[j] ^= n[i];
        n[i] ^= n[j];
        return *this;
    }
    
    friend bool operator >(const st &a, const st &b) {
        return a.score>b.score;
    }
};

// len[i][j] == 1 <=> there is a road between i and j
const int len[][7] = {
    {0,2,1,2,1,2,1},
    {2,0,1,2,3,2,1},
    {1,1,0,1,2,3,2},
    {2,2,1,0,1,2,3},
    {1,3,2,1,0,1,2},
    {2,2,3,2,1,0,1},
    {1,1,2,3,2,1,0}
};

int par[6543211] = {0}, tim[6543211] = {0};
bool visited[6543211] = {0};

int main() {
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
    
    int n, i, t=0, s, tmpi, tmpj, start, em=0; scanf("%d", &n);
    st fr;
    while (n--) {
        memset(par, 0, sizeof(par)); memset(visited, 0, sizeof(visited));
        char state[8]; scanf("%s", state);
        start = tmpi = atoi(state); if (tim[tmpi]) { printf("%d\n", tim[tmpi]); continue; }
        if (start==123456) {printf("0\n");continue;} visited[start] = true;
        bool ok = false;
        for (i = 0; i < 7; ++i) if (state[i]=='0') em=i;
        priority_queue<st, vector<st>, greater<st>> que;
        // score!
        que.push(st(state, 0, em, 0));
        while (!que.empty() && !ok) {
            fr = que.top(); memcpy(state, fr.n, sizeof(state));
            tmpj=atoi(fr.n); em = fr.e; t = fr.t; s = fr.score;
            que.pop();
            for (i = 0; i < 7; ++i) {
                if (len[i][em]!=1 || visited[(tmpi=atoi(fr.swap(i, em).n))]) continue;
                visited[tmpi]=1; par[tmpi]=tmpj;
                if (tmpi == 123456) {
                    while (par[tmpi]) {
                        tim[par[tmpi]] = tim[tmpi] + 1;
                        tmpi = par[tmpi];
                    }
                    ok = true; break;
                }
                // score!
                que.push(st(fr.n, t+1, i, t+1));
                fr.swap(i, em);
            }
        }
        if (ok) printf("%d\n", t+1); else {printf("-1\n"); tim[start] = -1;}
    }
    
    COUNT(the program);
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
