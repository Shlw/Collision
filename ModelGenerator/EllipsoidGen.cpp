/*************************************************************************
 * EllipsoidGen.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Description : Generate Ellipsoid.
 ************************************************************************/
#include <bits/stdc++.h>

using namespace std;

const float A=0.3;
const float B=0.25;
const float C=0.2;
const int N=1000;
typedef long long LL;
typedef float SEQ[N];

float deltan,deltam;
SEQ x[N],y[N],z[N],thetan,thetam;
int n,m,parts; //n row, m column, parts images
float mm;
FILE* os;

void prt(int i,int j){
    fprintf(os,"%.10f %.10f %.10f ",x[i][j],y[i][j],z[i][j]);
    while (j>=mm) j-=mm;
    fprintf(os,"%.10f %.10f ",0.5+float(mm-2*j)/mm/2*sqrt(x[i][j]*x[i][j]+y[i][j]*y[i][j])/sqrt(A*B)
                             ,float(n-i)/n);
}

int main(){
    scanf("%d%d%d",&n,&m,&parts); mm=m/float(parts);
    deltan=M_PI/(n+1); deltam=2*M_PI/m;
    for (int i=0;i<n;++i) thetan[i]=(i+1)*deltan-M_PI/2;
    for (int i=0;i<m;++i) thetam[i]=i*deltam;

    for (int i=0;i<n;++i){
        for (int j=0;j<m;++j)
            x[i][j]=A*sin(thetam[j])*cos(thetan[i]),
            y[i][j]=B*cos(thetam[j])*cos(thetan[i]),
            z[i][j]=C*sin(thetan[i]);
        x[i][m]=x[i][0];
        y[i][m]=y[i][0];
        z[i][m]=z[i][0];
    }

    os=fopen("ellipsoid.txt","w");

//top
    fprintf(os,"%d\n",m+m+(n-1)*m*2);
    for (int i=0;i<m;++i){
        fprintf(os,"%.10f %.10f %.10f 0.5 0 ",0.0,0.0,C);
        prt(n-1,i+1); prt(n-1,i); fprintf(os,"\n");
    }

//button
    for (int i=0;i<m;++i){
        prt(0,i); prt(0,i+1);
        fprintf(os,"%.10f %.10f %.10f 0.5 1\n",0.0,0.0,-C);
    }

//middle
    for (int i=0;i<n-1;++i)
        for (int j=0;j<m;++j){
            prt(i+1,j); prt(i+1,j+1); prt(i,j+1); fprintf(os,"\n");
            prt(i+1,j); prt(i,j+1); prt(i,j); fprintf(os,"\n");
        }

    fclose(os);
}
