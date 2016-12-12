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
#define INF 0x3f3f3f3f
// ****** bored with 'for(foo; foo; foo)' ****** //
//#define FIN(i,N) for(i=0;i<(N);++i)
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
    printf("100 100\n");
    int i;
    srand((unsigned int)time(0));
    FIN(i, 100) printf("%d\n", rand()%100+1);
}
#else // TEST
#define poj_2333


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
#elif defined poj_2333

int fuck = 1;

struct mdzz {
    int a[40010] = {0};
    mdzz() {}
    mdzz(const mdzz &m) {
        for (int i = 0; i < 40010; ++i) a[i] = m.a[i];
    }
    mdzz (int i) {
        int k = -1;
        while (i) {
            a[++k] = i % 10;
            i /= 10;
        }
    }
    mdzz operator --(int) {
        mdzz r(*this);
        int i = 0;
        while (!a[i]) a[i++] = 9;
        --a[i];
        return r;
    }
    const mdzz & operator *=(const mdzz &m) {
        int tmp[40010]={0};
        for (int i = 0; i < 40005; ++i) {
            if (!a[i]) continue;
            for (int j = 0; j < 5; ++j)
                tmp[i+j] += a[i] * m.a[j];
        }
        for (int i = 0; i < 40009; ++i) {
            if (tmp[i]>9) { tmp[i+1]+=tmp[i]/10; tmp[i]%=10; }
            a[i] = tmp[i];
        }
        return *this;
    }
    // m <= 10000
    const mdzz & operator *=(int m) {
        int tmp[40010]={0}; char mm[9]; sprintf(mm, "%d", m); reverse(mm,mm+strlen(mm));
        for (int i = 0; i < fuck; ++i) {
            if (!a[i]) continue;
            for (int j = 0; j < 5; ++j)
                tmp[i+j] += a[i] * (mm[j] ? mm[j] - '0' : 0);
            if (tmp[i]>9) { tmp[i+1]+=tmp[i]/10; tmp[i]%=10; }
        }
        memcpy(a, tmp, sizeof(a));
        return *this;
    }
    
};
#define MO 1000000000000000
int main() {
    INITICK;
    TICK;
    /*
    int n, i; scanf("%d", &n);
    mdzz t(1);//, b(n);
    //for (int i = 1; i < n; ++i)
        //t *= b--;
    
    for (i = 2; i < n; ++i) { t*=i; fuck+=int(log10(i))+1; }
    bool eat_zero = true;
    for (int i = fuck; i >= 0; --i) {
        if (t.a[i]) eat_zero = false;
        else if (eat_zero) continue;
        printf("%d", t.a[i]);
    }
    if (eat_zero) printf("0");
    printf("\n");
    */
    
    
    unsigned long long int a[3333]={1};
    int n, i, j, len=0; scanf("%d", &n);
    for (i = 2; i <= n; ++i) {
        for (j = 0; j <= len; ++j) a[j] *= i;
        for (j = 0; j < len; ++j) {
            a[j+1] += a[j] / MO;
            a[j] %= MO;
        }
        while (a[len] >= MO) {
            a[len+1] = a[len] / MO;
            a[len++] %= MO;
        }
    }
    printf("%lld", a[len]);
    for (i = len-1; i >= 0; --i) printf("%015lld", a[i]);
    printf("\n");
    
    
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
