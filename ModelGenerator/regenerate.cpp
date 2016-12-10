#include <bits/stdc++.h>

#define st first
#define nd second
using namespace std;

const int N=10000;

FILE* input;
FILE* output;
int n,m;
float vol,elas,dens;
float x[N][3],y[N][3],z[N][3],vx[N],vy[N],vz[N];

void normv(int loca,float x,float y,float z,float xx,float yy,float zz){
    vx[loca]=y*zz-z*yy;
    vy[loca]=-x*zz+z*xx;
    vz[loca]=x*yy-y*xx;
}

float dot(float x,float y,float z,int loca){
    return x*vx[loca]+y*vy[loca]+z*vz[loca];
}

void prt(int i,int j){
    fprintf(output,"%.6f %.6f %.6f ",x[i][j],y[i][j],z[i][j]);
}

void trans(){
    fscanf(input,"%d",&n);
    for (int i=0;i<n;++i){
        for (int j=0;j<3;++j)
            fscanf(input,"%f%f%f",x[i]+j,y[i]+j,z[i]+j);
        normv(i,x[i][1]-x[i][0],y[i][1]-y[i][0],z[i][1]-z[i][0],
                x[i][2]-x[i][1],y[i][2]-y[i][1],z[i][2]-z[i][1]);
        vol+=dot(x[i][0],y[i][0],z[i][0],i)/6;
    }

    fprintf(output,"%d %.6f %.6f %.6f\n",n,vol,(rand()%100)/100.0,(rand()%100)/100.0);
    for (int i=0;i<n;++i){
        for (int j=0;j<3;++j)
            prt(i,j);
        fprintf(output,"%.6f %.6f %.6f\n",vx[i],vy[i],vz[i]);
    }
}

int main(){
    srand(time(0));
    char st[N],tst[N];
    scanf("%s",st);
    n=strlen(st);
    st[n++]='.'; st[n++]='t'; st[n++]='x'; st[n++]='t';
    st[n]='\0';
    tst[0]='M'; tst[1]='o'; tst[2]='d'; tst[3]='e'; tst[4]='l';
    for (int i=0;i<=n;++i) tst[5+i]=st[i];

    //printf("%s\n",st);
    //printf("%s\n",tst);
    input=fopen(st,"r");
    if (!input) {printf("error\n"); return 0;}
    output=fopen(tst,"w");

    trans();

    fclose(input);
    fclose(output);
}
