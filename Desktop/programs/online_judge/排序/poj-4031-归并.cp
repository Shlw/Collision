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

//#define MAX_N 233333
struct competitor {
    int score, strength, id;
    friend ostream & operator <<(ostream &out, const competitor &a) {
        out << "player id: " << a.id << "; score: " << a.score << "; strength: " << a.strength;
        return out;
    }
} players[MAX_N], tmp[MAX_N];
int win[MAX_N/2], lose[MAX_N/2];

inline
int my_cmp(const void *a, const void *b) {
    const competitor *m = (const competitor *)a, *n = (const competitor *)b;
    if (m->score == n->score)
        return m->id - n->id;
    return n->score - m->score;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/whitephosphorus/Desktop/in.txt", "r", stdin);
    INITICK;
    TICK;
#endif // ONLINE_JUDGE
    int n, r, q, i, j, k, l, p;
    scanf("%d%d%d",&n,&r,&q);
    FIN(i, 2*n) {
        scanf("%d", &players[i].score);
        players[i].id = i+1;
    }
    FIN(i, 2*n)
        scanf("%d", &players[i].strength);
    
    qsort(players, 2*n, sizeof(competitor), my_cmp);
    FIN(i, r) {
        p=-1; CLM(win, 0); CLM(lose, 0);
        FIN(j, n) {
            if (players[j*2].strength > players[j*2+1].strength) {
                win[++p] = j*2; lose[p] = j*2+1; ++players[j*2].score;
            } else {
                win[++p] = j*2+1; lose[p] = j*2; ++players[j*2+1].score;
            }
        }
        p=-1;l=k=0;
        while (l<n && k<n) {
            if (my_cmp((const void *)(players+win[k]), (const void *)(players+lose[l])) > 0)
                tmp[++p] = players[lose[l++]];
            else
                tmp[++p] = players[win[k++]];
        }
        while (l<n)
            tmp[++p] = players[lose[l++]];
        while (k<n)
            tmp[++p] = players[win[k++]];
        memcpy(players, tmp, sizeof(players));
     /*
#ifndef ONLINE_JUDGE
        FIN(j, 2*n) cout << "rank " << j+1 << ": " << players[j] << endl;
#endif // ONLINE_JUDGE
      */
    }
    printf("%d\n", players[q-1].id);
#ifndef ONLINE_JUDGE
    COUNT(the program);
#endif // ONLINE_JUDGE
}
#endif // TEST
