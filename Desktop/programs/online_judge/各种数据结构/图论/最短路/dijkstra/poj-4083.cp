#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <list>
#define FIN(i,N) for(i=0;i<(N);i++)
#define FINM(i,N) for(i=((N)-1);i>=0;i--)
#define inf 1000000000 //2*inf<2^31
using namespace std;

//Dijkstra 最短路算法

struct node{
    int myid;
    int dist;
}tempn;
map<string,int> id;
string place[99];
int p,q,r;
int dis[99]={0};
int pre[99];
bool checked[99]={0};
list<node> road[99];

int main(){
    int i,j,k,pid1,pid2,d,min,minp=0,now,temp=0;
    bool add=1;
    string p1,p2,ele="",rst="";
    list<node>::iterator en;
    cin >> p;
    FIN(i,p){
        cin >> place[i];
        id.insert(pair<string,int>(place[i],i));
        road[i].clear();
        //tempn.myid=i;tempn.dist=0;
        //road[i].push_back(tempn);
    }
    cin >> q;
    FIN(i,q){
        cin >> p1 >> p2 >> d;
        if(id[p1]==id[p2])continue;
        tempn.myid=id[p2];tempn.dist=d;
        en=road[id[p1]].end();
        for(list<node>::iterator it=road[id[p1]].begin();it!=en;++it){
            if((*it).myid==id[p2]){
                add=0;
                if((*it).dist>d)(*it).dist=d;
            }
        }
        if(add)road[id[p1]].push_back(tempn);
        add=1;
        tempn.myid=id[p1];tempn.dist=d; //the way is two-way!!!
        en=road[id[p2]].end();
        for(list<node>::iterator it=road[id[p2]].begin();it!=en;++it){
            if((*it).myid==id[p1]){
                add=0;
                if((*it).dist>d)(*it).dist=d;
            }
        }
        if(add)road[id[p2]].push_back(tempn);
        add=1;
    }
    cin >> r;
    FIN(i,r){
        memset(pre,-1,sizeof(pre));
        cin >> p1 >> p2;
        pid1=id[p1];pid2=id[p2];
        FIN(j,q){
            dis[j]=inf;
            if(j==pid1){dis[j]=0;checked[j]=1;continue;}
        }
        en=road[pid1].end();
        for(list<node>::iterator it=road[pid1].begin();it!=en;++it){
            dis[(*it).myid]=(*it).dist;
        }
        FIN(j,q-1){
            min=inf;
            FIN(k,q){
                if(!checked[k] && dis[k]<min){
                    min=dis[k];minp=k;
                }
            }
            en=road[minp].end();
            for(list<node>::iterator it=road[minp].begin();it!=en;++it){
                if(min+(*it).dist<dis[(*it).myid]){
                    dis[(*it).myid]=min+(*it).dist;
                    pre[(*it).myid]=minp;
                }
            }
            checked[minp]=1;
        }
        now=pid2;
        while(pre[now]!=-1){
            ele=place[now];
            reverse(ele.begin(),ele.end());
            rst+=ele;
            ele="->("+to_string(dis[now]-dis[pre[now]])+")->";
            reverse(ele.begin(),ele.end());
            rst+=ele;
            now=pre[now];
        }
        ele=place[now];
        reverse(ele.begin(),ele.end());
        rst+=ele;
        if(dis[now]>0){
            ele="->("+to_string(dis[now])+")->";
            reverse(ele.begin(),ele.end());
            rst+=ele;
            ele=place[pid1];
            reverse(ele.begin(),ele.end());
            rst+=ele;
        }
        reverse(rst.begin(),rst.end());
        cout << rst << endl;
        
        memset(dis,0,sizeof(dis));
        memset(checked,0,sizeof(checked));
        ele="";rst="";temp=0;
    }
    return 0;
}
