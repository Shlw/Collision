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

//void my_sort(void * base, size_t length, size_t width, int (* _Nonnull)(const void *, const void *));

#include <iostream>
//#include <cmath>
//#include <cstdlib>
#include <cstring>
//#include <fstream>
//#include <iomanip>
//#include <string>
// *** STL - algorithm *** //
//#include <algorithm>
// *** STL - continer *** //
//#include <deque>
//#include <list>
//#include <map>
//#include <queue>
//#include <stack>
//#include <vector>
// *** OpenGL *** //
//#include <Carbon/Carbon.h>
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
//#include <GLUT/glut.h>

//#define MATH_PI 3.141592653589793
#define MAX_LEN 99
#define MAX_N 16
#define DIV   4
//#define BITS_PER_INT 32
#define INF 0x3f3f3f3f
// ****** bored with 'for(foo; foo; foo)' ****** //
//#define FIN(i,N) for(i=0;i<(N);++i)
//#define FIN1(i,N) for(i=1;i<=(N);++i)
//#define FINM(i,N) for(i=((N)-1);i>=0;--i)
//#define FINM1(i,N) for(i=(N);i>=1;--i)
// * bored with 'memset(foo, foo, foo)' either * //
#define CLM(arr,val) memset(arr,val,sizeof(arr))
// ****** count the code's execution time ****** //
#define INITICK clock_t ___START___, ___END___, ___DUR___
#define TICK ___START___ = clock()
#define COUNT(str) ___END___ = clock(); ___DUR___ = ___END___ - ___START___; printf(#str" used %f ms\n",(double)___DUR___/CLOCKS_PER_SEC * 1000)

using namespace std;

bool ok;
int check(int r, int c, int mp[][MAX_N], bool valid[]) {
    int i, count = 0;
    if (mp[r][c]) return 0;
    for (i = 0; i < MAX_N; ++i) {
        valid[mp[r][i]] = true;
        valid[mp[i][c]] = true;
        valid[mp[r/DIV*DIV+i/DIV][c/DIV*DIV+i%DIV]] = true;
    }
    for (i = 1; i <= MAX_N; ++i)
        if (valid[i]) ++count;
    return MAX_N-count;
}

void dfs(int mp[][MAX_N]) {
    if (ok) return;
    bool valid[MAX_N+1] = {0};
    int mi, mj = mi = -1, mc = INF, tmp;
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            if (mp[i][j]) continue;
            CLM(valid, 0);
            if ((tmp = check(i, j, mp, valid)) && tmp < mc) {
                mi = i; mj = j; mc = tmp;
            } else if (!tmp)
                return;
        }
    }
    if (mi == -1 && mj == -1) {
        ok = true;
        for (int i = 0; i < MAX_N; ++i) {
            for (int j = 0; j < MAX_N; ++j)
                printf("%c", mp[i][j]+'A'-1);
            printf("\n");
        }
        return;
    }
    CLM(valid, 0);
    check(mi, mj, mp, valid);
    for (int i = 1; i <= MAX_N; ++i) {
        if (valid[i]) continue;
        mp[mi][mj] = i;
        dfs(mp);
    }
    mp[mi][mj] = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE
    int mp[MAX_N][MAX_N];
    char tmp[MAX_LEN];
    CLM(mp, 0); ok = false;
    for (int j = 0; j < MAX_N; ++j) {
        scanf("%s", tmp);
        for (int i = 0; i < MAX_N; ++i) {
            if (tmp[i] == '-')
                mp[j][i] = 0;
            else
                mp[j][i] = tmp[i] - 'A' + 1;
        }
        dfs(mp);
    }
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}
