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
#define FINM(i,N) for(i=((N)-1);i>=0;--i)
#define inf 1000000000 //2*inf<2^31
#define iginf 0x7fffffff
using namespace std;

int main(){
    int m,n,i,j=0,a[100];
    bool Zero = false, manyZeroes = false, EvenNeg = true;
    cin >> m;
    while(m--) {
        memset(a,0,sizeof(a)); Zero = false; manyZeroes = false; EvenNeg = true; j = 0;
        cin >> n;
        FIN(i,n) {
            cin >> a[i];
            if(a[i] < 0) EvenNeg = !EvenNeg;
            if(!a[i] && Zero) manyZeroes = true;
            if(!a[i]) Zero = true;
        }
        if(manyZeroes) {cout << a[0] << endl; continue;} // result must be 0, output a[0]
        if(Zero && EvenNeg) {cout << 0 << endl; continue;} // one 0 && even <0, output 0
        if(Zero && !EvenNeg) { // one 0 && odd <0, output the first number != 0
            while(!a[j]) {
                ++j;
            }
            cout << a[j] << endl;
            continue;
        }
        j=0;
        sort(a,a+n);
        if(EvenNeg) { // even <0, output a smallest >0
            while(a[j]<0) {
                ++j;
            }
            if(j>=n) j=0; // no >0, output a smallest <0
            cout << a[j] << endl;
            continue;
        }
        //odd <0, output a largest <0
        j=0;
        while(a[j]<0){
            ++j;
        }
        cout << a[j-1] << endl;
    }
    
    return 0;
}
