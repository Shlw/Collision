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
//#define MAX_LEN 111
#define MAX_N 233333
//#define BITS_PER_INT 32
//#define INF 0x3f3f3f3f
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
    printf("100000 50 100000\n");
    int i, a[100000];
    srand((unsigned int)time(0));
    FIN(i, 100000) /*printf("%d ", rand()%100000001);*/printf("0 ");
    printf("\n");
    FIN(i, 100000) a[i] = i+1;
    for (i = 99999; i >= 0; --i) {
        int t = rand()%(i+1), r=a[t]^a[i];
        printf("%d ", a[t]);
        a[i]^=r; a[t]^=r;
    }
    printf("\n");
}
#else // TEST

#define MO 10007
inline
int qpow(int a, int b) {
    a %= MO;
    int r = 1;
    for (; b; b >>= 1) {
        if (b & 1) r = (r * a) % MO;
        a = (a * a) % MO;
    }
    return r;
}
inline
int C(int a, int b) {
    // a must be greater than b
    int r = 1;
    if (b > a / 2) b = a - b;
    for (int i = a; i > a-b; --i)
        r = (r * i) % MO;
    for (int i = b; i > 1; --i)
        r = (r * qpow(i, MO-2)) % MO;
    return r;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE
    int a, b, k, n, m;
    scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);
    printf("%d\n", qpow(a, n) * qpow(b, m) % MO * C(k, n) % MO);
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}
#endif // TEST

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
