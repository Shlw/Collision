#include <bits/stdc++.h>

#define st first
#define nd second
using namespace std;

const float R=0.3;
const int N=1000;
typedef long long LL;
typedef float SEQ[N];

float deltan,deltam;
SEQ x[N],y[N],z[N],thetan,thetam;
int n,m; //n row, m column
FILE* os;

void prt(int i,int j){
    fprintf(os,"%.6f %.6f %.6f ",x[i][j],y[i][j],z[i][j]);
}

int main(){
    scanf("%d%d",&n,&m);
    deltan=M_PI/(n+1); deltam=2*M_PI/m;
    for (int i=0;i<n;++i) thetan[i]=(i+1)*deltan-M_PI/2;
    for (int i=0;i<m;++i) thetam[i]=i*deltam;

//    for (int i=0;i<n;++i) printf("%.6lf ",thetan[i]); printf("\n");
//    for (int i=0;i<m;++i) printf("%.6lf ",thetam[i]); printf("\n");

    for (int i=0;i<n;++i){
        for (int j=0;j<m;++j)
            x[i][j]=R*sin(thetam[j])*cos(thetan[i]),
            y[i][j]=R*cos(thetam[j])*cos(thetan[i]),
            z[i][j]=R*sin(thetan[i]);
        x[i][m]=x[i][0];
        y[i][m]=y[i][0];
        z[i][m]=z[i][0];
    }

    os=fopen("sphere.txt","w");

    fprintf(os,"%d\n",m+m+(n-1)*m*2);
    for (int i=0;i<m;++i){
        fprintf(os,"%.6f %.6f %.6f ",0.0,0.0,R);
        prt(n-1,i+1); prt(n-1,i); fprintf(os,"\n");
    }
    for (int i=0;i<m;++i){
        prt(0,i); prt(0,i+1);
        fprintf(os,"%.6f %.6f %.6f\n",0.0,0.0,-R);
    }
    for (int i=0;i<n-1;++i)
        for (int j=0;j<m;++j){
            prt(i+1,j); prt(i+1,j+1); prt(i,j+1); fprintf(os,"\n");
            prt(i+1,j); prt(i,j+1); prt(i,j); fprintf(os,"\n");
        }

    fclose(os);
}
