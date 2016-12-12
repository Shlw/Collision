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
#define FINM1(i,N) for(i=(N);i>=1;--i)
#define inf 1000000000 // 2*inf<2^31
#define iginf 0x7fffffff // 2147483647
#define MAX_LEN 1010
using namespace std;

void merge(int a[], int tmp[], int begin, int mid, int end) {
    int i,j,k=-1;
    i = begin; j = mid + 1;
    while (i <= mid && j <= end) {
        if (a[i] >= a[j]) {
            tmp[++k] = a[j++];
        } else {
            tmp[++k] = a[i++];
        }
    }
    while (i <= mid) {
        tmp[++k] = a[i++];
    }
    while (j <= end) {
        tmp[++k] = a[j++];
    }
    FIN(i,k+1) {
        a[begin + i] = tmp[i];
    }
}

void mergeSort(int a[], int tmp[], int begin, int end) {
    if (begin < end) {
        int mid = (begin + end) >> 1;
        mergeSort(a, tmp, begin, mid);
        mergeSort(a, tmp, mid + 1, end);
        merge(a, tmp, begin, mid, end);
    }
}

int main() {
    int n, i, a[MAX_LEN]={0}; cin >> n;
    int begin = 0, end = n - 1;
    FIN(i,n) cin >> a[i];
    int *tmp = new int[end - begin + 1];
    mergeSort(a, tmp, begin, end);
    delete[] tmp;
    FIN(i,n) cout << a[i] << endl;
    return 0;
}
