/*************************************************************************
 * CubeGen.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Description : Generate Cube.
 ************************************************************************/
#include <bits/stdc++.h>

using namespace std;

const float L=0.2;
const float R=L;
const float H=R;
const int N=100;
int n;
float x[N][N],y[N][N],z[N][N];
FILE* os=fopen("cube.txt","w");

void prt(int i,int j){
    fprintf(os,"%.10f %.10f %.10f %.10f %.10f ",x[i][j],y[i][j],z[i][j],float(j)/n,float(i)/n);
}

void prtsquare(float tx,float ty,float tz,float xx,float xy,float xz,float yx,float yy,float yz){
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
           "I will divide each surface of the cube into N*N subdivided square\n");
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
