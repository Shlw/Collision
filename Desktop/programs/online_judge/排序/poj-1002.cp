#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#define FIN(i,N) for(i=0;i<(N);i++)
#define FINM(i,N) for(i=((N)-1);i>=0;i--)
#define INF 0x7fffffff
using namespace std;

int t[100000]={0};

int main(){
    //printf("%03d-%04d\n",10023/10000,10023%10000);
    int i,j,k=0,l,m=1,n;
    string s;
    char z;
    bool f=true;
    cin >> n;
    cin.ignore(INF,'\n');
    FIN(i,n){
        getline(cin,s);
        k=7;
        FIN(j,s.length()){
            z=s.at(j);
            if(z>='0'&&z<='9'){
                t[i]+=(z-'0')*pow(10,--k);
            }else if(z>='a'&&z<='z'){
                t[i]+=((z-'a'-(z>'q'))/3+2)*pow(10,--k);
            }else if(z>='A'&&z<='Z'){
                t[i]+=((z-'A'-(z>'Q'))/3+2)*pow(10,--k);
            }
        }
    }
    sort(t,t+n);
    l=t[0];
    for(i=1;i<n;i++){
        if(l==t[i]){
            ++m;
        }else{
            if(m>1){
                printf("%03d-%04d %d\n",l/10000,l%10000,m);
                f=false;
                m=1;
            }
            l=t[i];
        }
    }
    if(m>1){
        printf("%03d-%04d %d\n",l/10000,l%10000,m);
        f=false;
        m=1;
    }
    if(f)cout << "No duplicates." << endl;
    return 0;
}
