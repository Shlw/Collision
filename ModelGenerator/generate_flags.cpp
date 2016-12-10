#include <bits/stdc++.h>

using namespace std;

struct ppp{
    float x;float y;float z;
};

struct cmp{
    bool operator()(ppp a,ppp b){
        return a.x<b.x || (a.x==b.x && a.y<b.y) || (a.x==b.x && a.y==b.y && a.z<b.z);
    }
};

const int N=10000;
int n;
float x,y,z;
FILE* input;
FILE* output;
set<ppp,cmp> a;

void hsh(){
    fscanf(input,"%d%f%f%f",&n,&x,&y,&z);
    fprintf(output,"%d %.6f %.6f %.6f\n",n,x,y,z);

    for (int i=0;i<n;++i){
        for (int j=0;j<3;++j){
            fscanf(input,"%f%f%f",&x,&y,&z);
            fprintf(output,"%.6f %.6f %.6f ",x,y,z);
            ppp now={x,y,z};
            if (a.find(now)==a.end()) {a.insert(now); fprintf(output,"1 ");}
                else fprintf(output,"0 ");
        }
        fscanf(input,"%f%f%f",&x,&y,&z);
        fprintf(output,"%.6f %.6f %.6f\n",x,y,z);
    }

}

int main(){
    char st[N],tst[N];
    scanf("%s",st);
    n=strlen(st);
    st[n++]='.'; st[n++]='t'; st[n++]='x'; st[n++]='t';
    st[n]='\0';
    tst[0]='M'; tst[1]='o'; tst[2]='d'; tst[3]='e'; tst[4]='l';
    for (int i=0;i<=n;++i) tst[5+i]=st[i];

    input=fopen(st,"r");
    output=fopen(tst,"w");

    hsh();

    fclose(input);
    fclose(output);
}
