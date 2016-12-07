/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw lzh
 * Description : Fundamental implementation of global.hpp
 ************************************************************************/

#include "global.hpp"

// Declarations of global variables
int nWindowFlags = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE;
int nInitWindowWidth = 1024, nInitWindowHeight = 768;
int nTimerSpeed = 20;
const char* cpWindowTitle = "Collision Demo";
int nLastClock;

int nModelTot;
int nMaterialTot;
int nObjectTot;
PModel mppModelList[100];
PObject oppObjectList[100];
// first is density, second is elasticity
float fppMaterialList[100][2];

glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b){
    glm::vec4 ret=glm::vec4(a[1]*b[2]-a[2]*b[1],
                            -a[0]*b[2]+a[2]*b[0],
                            a[0]*b[1]-a[1]*b[0],0);
    return ret;
}
float v4Dots(glm::vec4 a,glm::vec4 b){
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}
float v4Length(glm::vec4 a){
    return sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
}

PPoint MultPoint(PMat4 matrix,PPoint p){
    Point* ret=new Point(p);
    *ret->vpCoordinate=(*matrix) * (*ret->vpCoordinate);
    return ret;
}
PTriangle MultTriangle(PMat4 matrix,PTriangle cone){
    PTriangle ret=new Triangle;
    for (int i=0;i<3;++i)
        ret->pppVertex[i]=MultPoint(matrix,cone->pppVertex[i]);
    ret->vpNormalVector=new glm::vec4((*matrix) * (*cone->vpNormalVector));
    return ret;
}

Point::Point(){
    vpCoordinate=NULL;
    vpColor=NULL;
}
Point::Point(PPoint example){
    vpColor=new glm::vec4(*example->vpColor);
    vpCoordinate=new glm::vec4(*example->vpCoordinate);
}
Point::Point(
    float x,float y,float z,
    float r,float g,float b,float alpha
){
    vpCoordinate=new glm::vec4(x,y,z,1.0);
    vpColor=new glm::vec4(r,g,b,alpha);
}
Point::~Point(){
    delete vpCoordinate;
    delete vpColor;
}

Triangle::Triangle(){
    pppVertex[0]=pppVertex[1]=pppVertex[2]=NULL;
    vpNormalVector=NULL;
}
Triangle::Triangle(PPoint a,PPoint b,PPoint c){
    pppVertex[0]=new Point(a);
    pppVertex[1]=new Point(b);
    pppVertex[2]=new Point(c);
    vpNormalVector=new glm::vec4;
    *vpNormalVector=v4Cross(*b->vpCoordinate - *a->vpCoordinate,
                            *c->vpCoordinate - *b->vpCoordinate);
}
Triangle::~Triangle(){
    delete pppVertex[0]; delete pppVertex[1]; delete pppVertex[2];
    delete vpNormalVector;
}

Model::Model(){
    nLength=0;
    fVolume=0.0;
    tppCone=NULL;
}
Model::~Model(){
    for (int i=0;i<nLength;++i) delete tppCone[i];
    delete[] tppCone;
}

Object::Object(){
    nModelType=0;
    fMomentInertia=fElastic=fMass=0.0;
    mpFrame=NULL;
    vpSpeed=NULL;
}
Object::~Object(){
    delete mpFrame;
    delete vpSpeed;
}

Object::Object(int model,int material,float vx,float vy,float vz){
    if (model>nModelTot || model<1)
        throw ERROR_UNKNOWN_MODEL;
    else if(material>nMaterialTot || material<1)
        throw ERROR_UNKNOWN_MATERIAL;
    vpSpeed=new glm::vec3(vx,vy,vz);
    mpFrame=new glm::mat4(1.0);
    nModelType=model;
    fMass=mppModelList[model]->fVolume*fppMaterialList[material][0];
    fElastic=fppMaterialList[material][1];
    // need to calculate, later update
    fMomentInertia=0;
}

PTriangle Object::IsInside(PPoint tp){
    glm::vec4* plocat=tp->vpCoordinate;
    int len=mppModelList[nModelType]->nLength;
    float dist=INT_MAX;
    PTriangle ret=NULL;
    
    for (int i=0;i<len;++i){
        PTriangle now=MultTriangle(mpFrame,mppModelList[nModelType]->tppCone[i]);
        float vl=v4Dots(*now->vpNormalVector,
                          *tp->vpCoordinate - *now->pppVertex[0]->vpCoordinate);
        if (vl>0){delete now; delete ret; return NULL;}
        vl=-vl/v4Length(*now->vpNormalVector);
        if (vl<dist) {dist=vl; delete ret; ret=now;}
    }
    
    return ret;
}

void ReadFiles(){
    FILE* materialin=fopen("material.txt","r");
    FILE* modelin=fopen("model.txt","r");

    fscanf(materialin,"%d",&nMaterialTot);
    
    for (int i=1;i<=nMaterialTot;++i)
        fscanf(materialin,"%f%f",fppMaterialList[i],fppMaterialList[i]+1);

    fscanf(modelin,"%d",&nModelTot);
    for (int i=1;i<=nModelTot;++i){
        int len;
        GLfloat vol;
        fscanf(modelin,"%d%f",&len,&vol);
        mppModelList[i] = new Model;
        mppModelList[i]->nLength=len;
        mppModelList[i]->fVolume=vol;
        mppModelList[i]->tppCone=new PTriangle[len];

        for (int j=0;j<len;++j){
            PPoint p[3];
            for (int k=0;k<3;++k){
                GLfloat x,y,z;
                fscanf(modelin,"%f%f%f",&x,&y,&z);
                p[k]=new Point(x,y,z,
                               (rand()%100)/100.0,
                               (rand()%100)/100.0,
                               (rand()%100)/100.0,1.0);
            }
            mppModelList[i]->tppCone[j]=new Triangle(p[0],p[1],p[2]);
            delete p[0]; delete p[1]; delete p[2];
        }
    }

    fclose(materialin);
    fclose(modelin);
    return ;
}

void CleanUp()
{
    for (int i = 1; i <= nModelTot; i++)
        delete mppModelList[i];
    for (int i = 0; i < nObjectTot; i++)
        delete oppObjectList[i];
    return ;
}
