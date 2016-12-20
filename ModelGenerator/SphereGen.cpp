/*************************************************************************
 * SphereGen.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Description : Generate Sphere.
 ************************************************************************/
#include <bits/stdc++.h>

using namespace std;

const double R=0.2;
const int N=1000;
typedef long long LL;
typedef double SEQ[N];

double deltan,deltam;
SEQ x[N],y[N],z[N],thetan,thetam;
int n,m,parts; //n row, m column, parts images
double mm;
FILE* os;

double modmm(double x){return x-floor(x/mm)*mm;}

void prt_coord(int i,int j){
    fprintf(os,"%.20lf %.20lf %.20lf ",x[i][j],y[i][j],z[i][j]);
}

void prt_texture(int i,int j){
    j=modmm(j);
    fprintf(os,"%.20lf %.20lf ",0.48+double(mm+1-2*j)/(mm+1)/2*sqrt(x[i][j]*x[i][j]+y[i][j]*y[i][j])/R
                             ,double(n-i)/n);
}

void prt_two(int i1,int j1,int i2,int j2){
    int tj1=j1,tj2=j2;
    if (fabs(modmm(j1)-modmm(j2))>mm-2) tj2=tj1;
    prt_coord(i1,j1); prt_texture(i1,tj1);
    prt_coord(i2,j2); prt_texture(i2,tj2);
}

void prt_three(int i1,int j1,int i2,int j2,int i3,int j3){
    int tj1=j1,tj2=j2,tj3=j3;
    if (fabs(modmm(j1)-modmm(j2))>mm-2){
        tj2=tj3=tj1;
    }
    prt_coord(i1,j1); prt_texture(i1,tj1);
    prt_coord(i2,j2); prt_texture(i2,tj2);
    prt_coord(i3,j3); prt_texture(i3,tj3);
}

int main(){
    printf("Please input 3 integers N, M, P:\n"
           "I will divide the sphere into N rows and M columns with P faces\n"
           "Also, M should be aliquot by P\n"
           "Or, the result can not be guaranteed:)\n");


    scanf("%d%d%d",&n,&m,&parts); mm=m/double(parts);
    deltan=M_PI/(n+1); deltam=2*M_PI/m;
    for (int i=0;i<n;++i) thetan[i]=(i+1)*deltan-M_PI/2;
    for (int i=0;i<m;++i) thetam[i]=i*deltam;

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

//top
    for (int i=0;i<m;++i){
        fprintf(os,"%.20lf %.20lf %.20lf 0.5 0 ",0.0,0.0,R);
        prt_two(n-1,i+1,n-1,i); fprintf(os,"\n");
    }

//button
    for (int i=0;i<m;++i){
        prt_two(0,i,0,i+1);
        fprintf(os,"%.20lf %.20lf %.20lf\n 0.5 1 ",0.0,0.0,-R);
    }

//middle
    for (int i=0;i<n-1;++i)
        for (int j=0;j<m;++j){
            prt_three(i+1,j,i+1,j+1,i,j+1); fprintf(os,"\n");
            prt_three(i+1,j,i,j+1,i,j); fprintf(os,"\n");
        }

    fclose(os);
}
