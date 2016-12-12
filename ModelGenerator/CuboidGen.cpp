/*************************************************************************
 * CuboidGen.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Description : Generate Cuboid.
 ************************************************************************/
#include <bits/stdc++.h>

using namespace std;

const float L=0.2;
const float R=0.3;
const float H=0.25;

const float po[2][4][3]={
    {{R,L,-H},{R,-L,-H},{-R,-L,-H},{-R,L,-H}},
    {{R,L,H},{R,-L,H},{-R,-L,H},{-R,L,H}}
};

FILE* os=fopen("cuboid.txt","w");
void prt(int i,int j){
    fprintf(os,"%.10f %.10f %.10f ",po[i][j][0],po[i][j][1],po[i][j][2]);
}

int main(){
    fprintf(os,"12\n");

    prt(1,0); prt(1,1); prt(0,1); fprintf(os,"\n");
    prt(1,0); prt(0,1); prt(0,0); fprintf(os,"\n");

    prt(1,1); prt(1,2); prt(0,2); fprintf(os,"\n");
    prt(1,1); prt(0,2); prt(0,1); fprintf(os,"\n");

    prt(1,2); prt(1,3); prt(0,3); fprintf(os,"\n");
    prt(1,2); prt(0,3); prt(0,2); fprintf(os,"\n");

    prt(1,3); prt(1,0); prt(0,0); fprintf(os,"\n");
    prt(1,3); prt(0,0); prt(0,3); fprintf(os,"\n");
//top
    prt(1,2); prt(1,1); prt(1,0); fprintf(os,"\n");
    prt(1,2); prt(1,0); prt(1,3); fprintf(os,"\n");
//button
    prt(0,2); prt(0,0); prt(0,1); fprintf(os,"\n");
    prt(0,2); prt(0,3); prt(0,0); fprintf(os,"\n");

    fclose(os);
}