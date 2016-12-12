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
#define iginf 0x7fffffff
#define MAX_LEN 400
using namespace std;

char letters[20][20];
int r, c;
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int max_l = 1;

void dfs(int x, int y, int curl, string visited) {
    int i, x1, y1;
    string t;
    FIN(i,4){
        x1 = x + dir[i][0]; y1 = y + dir[i][1];
        t = letters[y1][x1];
        if (x1 >= 0 && y1 >= 0 && x1 < c && y1 < r && strstr(&visited[0], &t[0]) == NULL) {
            if (max_l < curl+1) max_l = curl+1;
            dfs(x1,y1,curl+1,visited+t);
        }
    }
}

int main(){
    char l;
    int i, j;
    string t;
    
    cin >> r >> c;
    FIN(i,r){
        FIN(j,c){
            cin >> l;
            letters[i][j] = l;
        }
    }
    t = letters[0][0];
    dfs(0,0,1,t);
    cout << max_l << endl;
    
    return 0;
}
