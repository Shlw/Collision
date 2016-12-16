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

const float po[2][4][3]={
    {{R,L,-H},{R,-L,-H},{-R,-L,-H},{-R,L,-H}},
    {{R,L,H},{R,-L,H},{-R,-L,H},{-R,L,H}}
};

FILE* os=fopen("cube.txt","w");
void prt(int i,int j,float x,float y){
    fprintf(os,"%.10f %.10f %.10f %.10f %.10f ",po[i][j][0],po[i][j][1],po[i][j][2],x,y);
}

int main(){
    fprintf(os,"12\n");

    prt(1,0,1,0); prt(1,1,0,0); prt(0,1,0,1); fprintf(os,"\n");
    prt(1,0,1,0); prt(0,1,0,1); prt(0,0,1,1); fprintf(os,"\n");

    prt(1,1,1,0); prt(1,2,0,0); prt(0,2,0,1); fprintf(os,"\n");
    prt(1,1,1,0); prt(0,2,0,1); prt(0,1,1,1); fprintf(os,"\n");

    prt(1,2,1,0); prt(1,3,0,0); prt(0,3,0,1); fprintf(os,"\n");
    prt(1,2,1,0); prt(0,3,0,1); prt(0,2,1,1); fprintf(os,"\n");

    prt(1,3,1,0); prt(1,0,0,0); prt(0,0,0,1); fprintf(os,"\n");
    prt(1,3,1,0); prt(0,0,0,1); prt(0,3,1,1); fprintf(os,"\n");
//top
    prt(1,2,1,0); prt(1,1,0,0); prt(1,0,0,1); fprintf(os,"\n");
    prt(1,2,1,0); prt(1,0,0,1); prt(1,3,1,1); fprintf(os,"\n");
//button
    prt(0,2,1,0); prt(0,0,0,0); prt(0,1,0,1); fprintf(os,"\n");
    prt(0,2,1,0); prt(0,3,0,1); prt(0,0,1,1); fprintf(os,"\n");

    fclose(os);
}
