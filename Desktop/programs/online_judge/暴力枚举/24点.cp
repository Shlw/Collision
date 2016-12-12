#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#define FIN(i,N) for(i=0;i<(N);i++)
#define TAR 24
using namespace std;

bool di(int a,int b){
    if(!b)return false;
    return !(a%b);
}

bool cal(int a,int b,int c=0,int d=0){
    if(!d){
        if(!c){
            return (TAR==a+b)||(TAR==a-b)||(TAR==b-a)||(TAR==a*b)||(di(a,b)&&TAR==a/b)||(di(b,a)&&TAR==b/a);
        }
        return
        cal(a+b,c)||cal(a-b,c)||cal(b-a,c)||cal(a*b,c)||(di(a,b)&&cal(a/b,c))||(di(b,a)&&cal(b/a,c))||
        cal(a+c,b)||cal(a-c,b)||cal(c-a,b)||cal(a*c,b)||(di(a,c)&&cal(a/c,b))||(di(c,a)&&cal(c/a,b))||
        cal(c+b,a)||cal(c-b,a)||cal(b-c,a)||cal(c*b,a)||(di(c,b)&&cal(c/b,a))||(di(b,c)&&cal(b/c,a));
    }
    return
    cal(a+b,c,d)||cal(a-b,c,d)||cal(b-a,c,d)||cal(a*b,c,d)||(di(a,b)&&cal(a/b,c,d))||(di(b,a)&&cal(b/a,c,d))||
    cal(a+c,b,d)||cal(a-c,b,d)||cal(c-a,b,d)||cal(a*c,b,d)||(di(a,c)&&cal(a/c,b,d))||(di(c,a)&&cal(c/a,b,d))||
    cal(c+b,a,d)||cal(c-b,a,d)||cal(b-c,a,d)||cal(c*b,a,d)||(di(c,b)&&cal(c/b,a,d))||(di(b,c)&&cal(b/c,a,d))||
    cal(a+d,c,b)||cal(a-d,c,b)||cal(d-a,c,b)||cal(a*d,c,b)||(di(a,d)&&cal(a/d,c,b))||(di(d,a)&&cal(d/a,c,b))||
    cal(d+c,b,a)||cal(d-c,b,a)||cal(c-d,b,a)||cal(d*c,b,a)||(di(d,c)&&cal(d/c,b,a))||(di(c,d)&&cal(c/d,b,a))||
    cal(d+b,a,c)||cal(d-b,a,c)||cal(b-d,a,c)||cal(d*b,a,c)||(di(d,b)&&cal(d/b,a,c))||(di(b,d)&&cal(b/d,a,c));
}

int main(){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    cout << (cal(a,b,c,d)?"YES":"NO") << endl;
    return 0;
}
