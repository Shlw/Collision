//getchar()需判断是否为eof或'\n'。
//while(cin.getline(s,length))可以成立，到末位自会break。另外实际输入的字符为length-1。
//在前一个cin后立刻getline会得到一个空行，这是因为cin不处理换行符。请使用cin.ignore(0x7fffffff,'\n')，无视之前的换行符。
//%0xd == 前导零#include <iostream>
//map如果访问了未包含的key，会自动创建一个。
//两个iterator不可以用大于／小于号比较。
//链表在用iterator遍历时，如果erase了元素，原来的iterator就不可用了，若要继续遍历必须使用it=list.erase(...)语句重置iterator（删除后就不用++it了）。

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
#define inf 1000000000 // 2*inf<2^31
#define iginf 0x7fffffff // 2147483647
#define MAX_LEN 5010
using namespace std;
typedef long long int ll;

int c[MAX_LEN]={0};
ll x[MAX_LEN], y[MAX_LEN], u[MAX_LEN], l[MAX_LEN];
ll X1,Y1,X2,Y2;
double t[MAX_LEN]={0};

int main() {
    int n,m,i,j;
    int begin, mid, end;
    
    while(scanf("%d", &n)) {
        if (!n) break;
        scanf("%d%lld%lld%lld%lld", &m, &X1, &Y1, &X2, &Y2);
        FIN1(i,n) {
            scanf("%lld%lld", u+i, l+i);
        }
        FIN(i,m) {
            scanf("%lld%lld", x+i, y+i);
        }
        FIN(i,m) {
            FIN1(j,n) {
                t[j] = (y[i] * (l[j] - u[j]) + Y2 * u[j] - l[j] * Y1) / (double)(Y2 - Y1);
            }
            t[0] = X1; t[n+1] = X2;
            begin = 0; end = n; mid = n >> 1;
            //begin = 1; end = n + 1; mid = (n >> 1) + 1;
            // 这里的算法太渣了，应该用向量叉乘判断点在直线左侧还是右侧，再用二分（这里的二分写的也很渣）
            while (end > begin) {
                if (x[i] > t[mid + 1]) {
                    if (begin != mid) begin = mid; else { mid = end; break; }
                    //begin = mid + 1;
                } else if (x[i] < t[mid]) {
                    if (begin != mid) end = mid; else { mid = begin; break; }
                    //end = mid;
                } else {
                    break;
                }
                mid = (begin + end) >> 1;
            }
            ++c[mid];
        }
        FIN(i,n+1) {
            printf("%d: %d\n", i, c[i]);
        }
        memset(t,0,sizeof(t));
        memset(c,0,sizeof(c));
        printf("\n");
    }
    return 0;
}

/*
 1 5 0 20 20 0
 5 15
 20 20
 0 20
 20 0
 18 18
 17 17
 1 5 0 20 20 0
 5 15
 2 1
 1 1
 1 2
 0 16
 0 0
 5 6 0 10 60 0
 3 1
 4 3
 6 8
 10 10
 15 30
 1 5
 2 1
 2 8
 5 5
 40 10
 7 9
 4 10 0 10 100 0
 20 20
 40 40
 60 60
 80 80
 5 10
 15 10
 25 10
 35 10
 45 10
 55 10
 65 10
 75 10
 85 10
 95 10
*/
