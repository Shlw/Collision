//getchar()需判断是否为eof或'\n'。
//while(cin.getline(s,length))可以成立，到末位自会break。另外实际输入的字符为length-1。
//在前一个cin后立刻getline会得到一个空行，这是因为cin不处理换行符。请使用cin.ignore(0x7fffffff,'\n')，无视之前的换行符。
//%0xd == 前导零#include <iostream>
//map如果访问了未包含的key，会自动创建一个。
//两个iterator不可以用大于／小于号比较。
//链表在用iterator遍历时，如果erase了元素，原来的iterator就不可用了，若要继续遍历必须使用it=list.erase(...)语句重置iterator（删除后就不用++it了）。

#include <iostream>
#include <iomanip>
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
#define inf 1000000000 //2*inf<2^31
#define iginf 0x7fffffff //2147483647
#define MAX_LEN 100000
using namespace std;

int a[MAX_LEN+10]={0};

int main() {
    int n,c,i,max,min,mid,count=1,t;
    bool tooSmall = false;
    scanf("%d%d",&n,&c);
    FIN(i,n){
        scanf("%d",a+i);
    }
    sort(a,a+n);
    max = a[n-1] - a[0];
    min = 1;
    while (max > min) {
        mid = (min + max) >> 1;
        if (min == mid) { max = min; break; }
        if (max == mid) { min = max; break; }
        t = a[0];
        count = 1;
        tooSmall = false;
        FIN1(i,n-1){
            if (a[i] - t >= mid) { ++count; t = a[i]; }
            if (count >= c) { tooSmall = true; break; }
        }
        if (tooSmall) { // mid may be exactly the answer
            min = mid;
        } else {
            max = mid;
        }
    }
    cout << ((min + max) >> 1) << endl;
    return 0;
}
