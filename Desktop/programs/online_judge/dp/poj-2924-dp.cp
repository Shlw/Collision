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
#include <map>
//#include <queue>
//#include <stack>
#include <vector>
// *** OpenGL *** //
//#include <Carbon/Carbon.h>
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
//#include <GLUT/glut.h>

//#define MATH_PI 3.141592653589793
#define MAX_LEN 111
#define MAX_N 20
//#define BITS_PER_INT 32
#define INF 0x3f3f3f3f
// ****** bored with 'for(foo; foo; foo)' ****** //
#define FIN(i,N) for(i=0;i<(N);++i)
//#define FIN1(i,N) for(i=1;i<=(N);++i)
//#define FINM(i,N) for(i=((N)-1);i>=0;--i)
//#define FINM1(i,N) for(i=(N);i>=1;--i)
// * bored with 'memset(foo, foo, foo)' either * //
#define CLM(arr,val) memset(arr,val,sizeof(arr))
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
    srand((unsigned int)time(0));
    for (int i = 0; i < 1000; ++i) {
        int len = rand() % 20 + 1;
        for (int j = 0; j < len; ++j)
            printf("%c", rand() % 26 + 'a');
        printf("\n");
    }
}
#else // TEST
int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE
    int n, i, j, k, ptr,
        x[MAX_N], y[MAX_N], s[MAX_LEN], area[MAX_LEN], dp[70000];
    while(scanf("%d", &n)!=EOF && n) {
        CLM(x, 0); CLM(y, 0); CLM(s, 0); CLM(area, 0); CLM(dp, INF);
        ptr = 0;
        FIN(i, n) scanf("%d %d", x+i, y+i);
        FIN(i, n) {
            for (j = i + 1; j < n; ++j) {
                s[ptr] = (1<<i) | (1<<j);
                FIN(k, n)
                    if ((x[i] - x[k]) * (x[j] - x[k]) <= 0 && (y[i] - y[k]) * (y[j] - y[k]) <= 0)
                        s[ptr] |= (1<<k);
                area[ptr++] = max(abs(x[i] - x[j]), 1) * max(abs(y[i] - y[j]), 1);
            }
        }
        dp[0] = 0;
        FIN(i, (1<<n) - 1) {
            FIN(j, ptr) {
                if (!(i ^ s[j])) continue;
                dp[i | s[j]] = min(dp[i | s[j]], dp[i] + area[j]);
            }
        }
        printf("%d\n", dp[(1<<n) - 1]);
    }
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}
#endif // TEST
