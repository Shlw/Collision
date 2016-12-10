/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw lzh Shlw lzh
 * Description : Implementation of fundamental things.
 ************************************************************************/

#include "global.hpp"

int nModelTot; // number of models
int nMaterialTot; // number of materials
int nObjectTot; // number of objects
PModel mppModelList[100];
PObject oppObjectList[100];
// first is density, second is elasticity
float fppMaterialList[100][2];

// Declarations of global variables
// int nWindowFlags = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE;
int nInitWindowWidth = 1024, nInitWindowHeight = 768;
int nTimerSpeed = 20;
const char* cpWindowTitle = "Collision Demo";

double dLastClock, dLastLastClock;
double dLastMouseX, dLastMouseY;
// Array to store the state of mouse buttons, where [0], [1], [2]
// represent left, middle and right button resepectively.
int npButtonState[3];
glm::mat4 mModelTransformMat;

float fRotateSpeed = 0.005;
float fTranslateSpeed = 0.005;
float fScrollSpeed = 0.10;

// glmvec4 cross product
glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b){
    glm::vec4 ret=glm::vec4(a[1]*b[2]-a[2]*b[1],
                            -a[0]*b[2]+a[2]*b[0],
                            a[0]*b[1]-a[1]*b[0],0);
    return ret;
}
// glmvec4 dot product
float v4Dots(glm::vec4 a,glm::vec4 b){
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}
// glmvec4 length
float v4Length(glm::vec4 a){
    return sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
}

// matrix multiplication left to a point
PPoint MultPoint(PMat4 matrix,PPoint p){
    Point* ret=new Point(p);
    *ret->vpCoordinate=(*matrix) * (*ret->vpCoordinate);
    return ret;
}
// matrix multiplication left to a triangle
PTriangle MultTriangle(PMat4 matrix,PTriangle cone){
    PTriangle ret=new Triangle;

    // calculate the global coordinate of vertices
    for (int i=0;i<3;++i)
        ret->pppVertex[i]=MultPoint(matrix,cone->pppVertex[i]);

    // rotate the normal vector
    ret->vpNormalVector=new glm::vec4((*matrix) * (*cone->vpNormalVector));
    return ret;
}

// initialize the point class
Point::Point(){
    vpCoordinate=NULL;
    vpColor=NULL;
    nFlag=0;
}
// initialize the point class by duplicating an example
Point::Point(PPoint example){
    vpColor=new glm::vec4(*example->vpColor);
    vpCoordinate=new glm::vec4(*example->vpCoordinate);
    nFlag=example->nFlag;
}
// initialize the point class according to all the data needed
Point::Point(
    float x,float y,float z,
    float r,float g,float b,float alpha){

    vpCoordinate=new glm::vec4(x,y,z,1.0);
    vpColor=new glm::vec4(r,g,b,alpha);
    nFlag=0;
}
// destroy the point class
Point::~Point(){
    delete vpCoordinate;
    delete vpColor;
}

// initialize the triangle class
Triangle::Triangle(){
    pppVertex[0]=pppVertex[1]=pppVertex[2]=NULL;
    vpNormalVector=NULL;
}
// initialize the triangle class with 3 given points(local coordinate system)
Triangle::Triangle(PPoint a,PPoint b,PPoint c){
    pppVertex[0]=new Point(a);
    pppVertex[1]=new Point(b);
    pppVertex[2]=new Point(c);
    vpNormalVector=new glm::vec4;
    *vpNormalVector=v4Cross(*b->vpCoordinate - *a->vpCoordinate,
                            *c->vpCoordinate - *b->vpCoordinate);
}
// initialize the triangle class with 3 given points(local coordinate system) and normal vector
Triangle::Triangle(PPoint a,PPoint b,PPoint c,PVec4 v){
    pppVertex[0]=new Point(a);
    pppVertex[1]=new Point(b);
    pppVertex[2]=new Point(c);
    vpNormalVector=new glm::vec4(*v);
}
// destroy the triangle class
Triangle::~Triangle(){
    delete pppVertex[0]; delete pppVertex[1]; delete pppVertex[2];
    delete vpNormalVector;
}

// initialize the model class
Model::Model(){
    nLength=0;
    fVolume=fElastic=fMass=0.0;
    tppCone=NULL;
}
// destroy the model class
Model::~Model(){
    for (int i=0;i<nLength;++i) delete tppCone[i];
    delete[] tppCone;
}

// initialize the object class
Object::Object(){
    nModelType=0;
    fMomentInertia=0.0;
    mpFrame=NULL;
    vpSpeed=NULL;
}
// destroy the object class
Object::~Object(){
    delete mpFrame;
    delete vpSpeed;
}
// use specific model and material type to initialize the object
// also need to input the velocity
Object::Object(int model,float vx,float vy,float vz){
    // lzh : use throw to handle exceptions
    if (model>nModelTot || model<1)
        throw ERROR_UNKNOWN_MODEL;
    vpSpeed=new glm::vec3(vx,vy,vz);
    mpFrame=new glm::mat4(1.0); // load the identity matrix into mFrame

    nModelType=model;
    // need to calculate, later update
    fMomentInertia=0;
}

// check whether the point is in the object,
// return NULL or the closest plane(in global coordinate system)
PTriangle Object::IsInside(PPoint tp){
    glm::vec4* plocat=tp->vpCoordinate;
    int len=mppModelList[nModelType]->nLength;
    // lzh : I changed INT_MAX into FLT_MAX
    float dist=FLT_MAX;
    PTriangle ret=NULL;

    for (int i=0;i<len;++i){
        // get the Ith triangle's coordinates in global coordinate system
        // also rotate the normal vector
        PTriangle now=MultTriangle(mpFrame,mppModelList[nModelType]->tppCone[i]);

        // calculate the volume of the cone formed by given point and the Ith triangle
        float vl=v4Dots(*now->vpNormalVector,
                          *tp->vpCoordinate - *now->pppVertex[0]->vpCoordinate);

        // not inside the left half space , return not_inside
        if (vl>0){delete now; delete ret; return NULL;}

        // calculate the distance between the given point and the plane where triangle lies
        vl=-vl/v4Length(*now->vpNormalVector);

        // update the dist
        if (vl<dist) {dist=vl; delete ret; ret=now;}
    }

    return ret;
}

int ReadFiles(const char* str){
    FILE* modelin=fopen(str,"r");
    if (!modelin) throw FILE_NOT_FOUND;
    ++nModelTot;

    int len;
    float vol,dens,elas;

    fscanf(modelin,"%d%f%f%f",&len,&vol,&dens,&elas);
    mppModelList[nModelTot] = new Model;
    mppModelList[nModelTot]->nLength=len;
    mppModelList[nModelTot]->fVolume=vol;
    mppModelList[nModelTot]->fMass=vol*dens;
    mppModelList[nModelTot]->fElastic=elas;
    mppModelList[nModelTot]->tppCone=new PTriangle[len];

    for (int j=0;j<len;++j){
        PPoint p[3];
        for (int k=0;k<3;++k){ // 3 points form a triangle
            float x,y,z;
            int isocur;
            fscanf(modelin,"%f%f%f%d",&x,&y,&z,&isocur);

            // generate random RGBcolor, no transparency
            p[k]=new Point(x,y,z,
                           (rand()%100)/100.0,
                           (rand()%100)/100.0,
                           (rand()%100)/100.0,1.0);
            p[k]->nFlag=isocur;
        }
        float x,y,z;
        fscanf(modelin,"%f%f%f",&x,&y,&z);

        glm::vec4 norm=glm::vec4(x,y,z,0);
        // one triangle forms a triangular-cone
        mppModelList[nModelTot]->tppCone[j]=new Triangle(p[0],p[1],p[2],&norm);
        delete p[0]; delete p[1]; delete p[2];
    }

    fclose(modelin);
    return nModelTot;
}

void ModelCleanUp()
{
    for (int i = 1; i <= nModelTot; i++)
        delete mppModelList[i];
    for (int i = 0; i < nObjectTot; i++)
        delete oppObjectList[i];
    return ;
}
