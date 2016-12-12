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
#define MAX_N 111
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
inline
bool check(int qx, int qy, int tx, int ty, int kx, int ky) {
    // in some cases the black king will kill the white queen,
    // so need further check, set qx and qy very large (but DO NOT let abs(qx-qy)<=7)
    if (kx==qx&&ky==qy) return check(10086,23333,tx,ty,qx,qy);
    // queen: in the same column, row or diagonal line; king: in neighbouring squares
    return (qx==kx||qy==ky||qx-kx==qy-ky||qx-kx==ky-qy||(abs(tx-kx)<=1&&abs(ty-ky)<=1));
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE
    char a[9], b[9], c[9];
    // q, t, k is for white queen, white king, black king respectively
    int i,j,k,qx, qy, tx, ty, kx, ky;
    bool flag, ok = false;
    scanf("%s%s%s", a, b, c);
    // index from 0 to 7 (including)
    tx = a[0]-'a'; ty = a[1]-'1'; qx = b[0]-'a'; qy = b[1]-'1'; kx = c[0]-'a'; ky = c[1]-'1';
    for (i = 0; i < 8&&!ok; ++i) {
        for (j = 0; j < 8&&!ok; ++j) {
            if (i==qx&&j==qy) continue;
            // check if queen can reach there (set tx and ty = 10086 to ignore the white king)
            if (!check(qx,qy,10086,10086,i,j)) continue;
            flag = true;
            // check the neibouring squares (9 positions)
            for (k = 0; k < 9&&flag; ++k) {
                if (kx+k/3-1<0||kx+k/3-1>7||ky+k%3-1<0||ky+k%3-1>7) continue;
                if (!check(i,j,tx,ty,kx+k/3-1,ky+k%3-1)) flag = false;
            }
            if (flag) ok = true;
        }
    }
    // when the program finds ok == true, it has already excuted ++i and ++j, so minus 1 respectively
    if (ok) printf("%c%d\n",i+'a'-1,j); else printf("no\n");
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}
#endif // TEST
