/*************************************************************************
 * regenerate for project Collision
 * Author : Shlw
 * Modifier : Shlw lzh Shlw
 * Description : Calculate normal-vector, volumes and so on.
 ************************************************************************/
#include <bits/stdc++.h>

using namespace std;

struct ppp{
    double x;double y;double z;
};

struct cmp{
    bool operator()(ppp a,ppp b){
        return a.x<b.x || (a.x==b.x && a.y<b.y) || (a.x==b.x && a.y==b.y && a.z<b.z);
    }
};

const int N=10000;

FILE* input;
FILE* output;
int n,m;
double vol,elas,dens;
double x[N][3],y[N][3],z[N][3],vx[N],vy[N],vz[N],texx[N][3],texy[N][3];
set<ppp,cmp> a;

// calculate normal vector
void normv(int loca,double x,double y,double z,double xx,double yy,double zz){
    vx[loca]=y*zz-z*yy;
    vy[loca]=-x*zz+z*xx;
    vz[loca]=x*yy-y*xx;
}

// dot calculate
double dot(double x,double y,double z,int loca){
    return x*vx[loca]+y*vy[loca]+z*vz[loca];
}

// square calculate
double sqr(double a){return a*a;}

// dist calculate
double dist(double a,double b,double c,double x,double y,double z){
    return sqrt(sqr(a-x)+sqr(b-y)+sqr(c-z));
}

// calculate part of inertia
double calc(double ax,double ay,double bx,double by,double cx,double cy){
    return 2*(ax*ay+bx*by+cx*cy)+(ax*by+ay*bx+ax*cy+ay*cx+bx*cy+by*cx);
}

void prt(int i,int j){
    fprintf(output,"%.20lf %.20lf %.20lf %.20lf %.20lf ",x[i][j],y[i][j],z[i][j],texx[i][j],texy[i][j]);
}

void trans(){
    double maxdist=0,ixx=0,iyy=0,izz=0,ixy=0,ixz=0,iyz=0;

    fscanf(input,"%d",&n);
    for (int i=0;i<n;++i){
        for (int j=0;j<3;++j){
            fscanf(input,"%lf%lf%lf%lf%lf",x[i]+j,y[i]+j,z[i]+j,texx[i]+j,texy[i]+j);
            maxdist=max(maxdist,dist(x[i][j],y[i][j],z[i][j],0,0,0));
        }
        normv(i,x[i][1]-x[i][0],y[i][1]-y[i][0],z[i][1]-z[i][0],
                x[i][2]-x[i][1],y[i][2]-y[i][1],z[i][2]-z[i][1]);
        double tv=dot(x[i][0],y[i][0],z[i][0],i);
        vol+=tv/6;
        ixy+=tv/120*calc(x[i][0],y[i][0],x[i][1],y[i][1],x[i][2],y[i][2]);
        ixz+=tv/120*calc(x[i][0],z[i][0],x[i][1],z[i][1],x[i][2],z[i][2]);
        iyz+=tv/120*calc(y[i][0],z[i][0],y[i][1],z[i][1],y[i][2],z[i][2]);
        ixx+=tv/120*calc(x[i][0],x[i][0],x[i][1],x[i][1],x[i][2],x[i][2]);
        iyy+=tv/120*calc(y[i][0],y[i][0],y[i][1],y[i][1],y[i][2],y[i][2]);
        izz+=tv/120*calc(z[i][0],z[i][0],z[i][1],z[i][1],z[i][2],z[i][2]);
    }

    double dens=(rand()%100)/100.0;
    fprintf(output,"%d %.20lf %.20lf %.20lf %.10lf\n",n,vol,dens+10,10+(rand()%100)/100.0,maxdist);
    for (int i=0;i<n;++i){
        for (int j=0;j<3;++j){
            prt(i,j);

            // check whether it has ocurred
            ppp now={x[i][j],y[i][j],z[i][j]};
            if (a.find(now)==a.end()) {a.insert(now); fprintf(output,"1 ");}
                else fprintf(output,"0 ");
        }
        fprintf(output,"%.20lf %.20lf %.20lf\n",vx[i],vy[i],vz[i]);
    }
    fprintf(output,"%.20lf %.20lf %.20lf %.20lf %.20lf %.20lf %.20lf %.20lf %.20lf",
                    ixx,ixy,ixz,ixy,iyy,iyz,ixz,iyz,izz);
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

    input=fopen(st,"r");
    if (!input) {printf("error\n"); return 0;}
    output=fopen(tst,"w");

    trans();

    fclose(input);
    fclose(output);
}
