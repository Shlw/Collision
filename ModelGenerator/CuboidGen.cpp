/*************************************************************************
 * CuboidGen.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw lzh
 * Description : Generate Cuboid.
 ************************************************************************/
#include <bits/stdc++.h>

using namespace std;

const double L=0.2;
const double R=0.3;
const double H=0.25;
const int N=100;
int n;
double x[N][N],y[N][N],z[N][N];
FILE* os=fopen("cuboid.txt","w");

void prt(int i,int j){
    fprintf(os,"%.20lf %.20lf %.20lf %.20lf %.20lf ",x[i][j],y[i][j],z[i][j],double(j)/n,double(i)/n);
}

void prtsquare(double tx,double ty,double tz,double xx,double xy,double xz,double yx,double yy,double yz){
    xx/=n; xy/=n; xz/=n; yx/=n; yy/=n; yz/=n;
    for (int i=0;i<=n;++i)
        for (int j=0;j<=n;++j)
            x[i][j]=tx+yx*i+xx*j,
            y[i][j]=ty+yy*i+xy*j,
            z[i][j]=tz+yz*i+xz*j;
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j){
            prt(i,j); prt(i+1,j); prt(i+1,j+1); fprintf(os,"\n");
            prt(i,j); prt(i+1,j+1); prt(i,j+1); fprintf(os,"\n");
        }
}

int main(){
    printf("Please input 1 integer N:\n"
           "I will divide each surface of the cuboid into N*N subdivided square\n");
    scanf("%d",&n);
    fprintf(os,"%d\n",6*n*n*2);

    prtsquare(R,-L,H,0,2*L,0,0,0,-2*H);
    prtsquare(-R,-L,H,2*R,0,0,0,0,-2*H);
    prtsquare(-R,L,H,0,-2*L,0,0,0,-2*H);
    prtsquare(R,L,H,-2*R,0,0,0,0,-2*H);
    prtsquare(-R,-L,H,0,2*L,0,2*R,0,0);
    prtsquare(R,-L,-H,0,2*L,0,-2*R,0,0);

    fclose(os);
}
