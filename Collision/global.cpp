/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw lzh Shlw lzh Shlw lzh Shlw
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
const char* cpWindowTitle = "Collision Demo";

double dLastClock, dLastLastClock;
int nLastSecond;
double dLastMouseX, dLastMouseY;
// Array to store the state of mouse buttons, where [0], [1], [2]
// represent left, middle and right button resepectively.
int npButtonState[3];
glm::mat4 mModelTransformMat;

float fRotateSpeed = 0.005;
float fTranslateSpeed = 0.005;
float fScrollSpeed = 0.10;

float fpBoxLimit[6] = {-1.0, 1.0, -1.0, 1.0, -1.0, 1.0};

int nTextureLength = 5;
const char* cpTextureName = "Texture.txt";
int* npPicWidth, * npPicHeight;
unsigned char** ucppPicContent;
int* npTextureIndex;

// matrix multiplication left to a point
PPoint MultPoint(PMat4 matrix,PPoint p){
    PPoint ret=new Point(p);
    *ret->vpCoordinate=(*matrix) * (*ret->vpCoordinate);
    ret->nFlag = p->nFlag;
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
    vpTexture=NULL;
    nFlag=0;
}
// initialize the point class by duplicating an example
Point::Point(PPoint example){
    vpColor=new glm::vec4(*example->vpColor);
    vpCoordinate=new glm::vec4(*example->vpCoordinate);
    vpTexture=new glm::vec2(*example->vpTexture);
    nFlag=example->nFlag;
}
// initialize the point class according to all the data needed
Point::Point(
    float x,float y,float z,
    float r,float g,float b,float alpha){

    vpCoordinate=new glm::vec4(x,y,z,1.0);
    vpColor=new glm::vec4(r,g,b,alpha);
    vpTexture=new glm::vec2(0,0);
    nFlag=0;
}
// destroy the point class
Point::~Point(){
    delete vpCoordinate;
    delete vpColor;
    delete vpTexture;
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
    vpNormalVector=new glm::vec4(
        glm::cross(glm::vec3(*b->vpCoordinate - *a->vpCoordinate),
        glm::vec3(*c->vpCoordinate - *b->vpCoordinate)),
        0.0
    );
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
    fVolume=fElastic=fMass=fMaxRadius=0.0;
    tppCone=NULL;
    mMomentOfInertia=NULL;
}
// destroy the model class
Model::~Model(){
    for (int i=0;i<nLength;++i) delete tppCone[i];
    delete[] tppCone;
    delete mMomentOfInertia;
}

// initialize the object class
Object::Object(){
    nModelType=0;
    fMomentInertia=0.0;
    mpFrame=NULL;
    vpSpeed=NULL;
    vpAngularMomentum=NULL;
}
// destroy the object class
Object::~Object(){
    delete mpFrame;
    delete vpSpeed;
    delete vpAngularMomentum;
}
// use specific model and material type to initialize the object
// also need to input the velocity
Object::Object(int model,float vx,float vy,float vz,float mx,float my,float mz){
    // lzh : use throw to handle exceptions
    if (model>=nModelTot || model<0)
        throw ERROR_UNKNOWN_MODEL;
    vpSpeed=new glm::vec3(vx,vy,vz);
    vpAngularMomentum=new glm::vec3(mx,my,mz);
    mpFrame=new glm::mat4(1.0); // load the identity matrix into mFrame

    nModelType=model;
    // need to calculate, later update
    fMomentInertia=0;
}

// check if the point is in the triangle
bool IsInArea(PTriangle a,PVec4 tp){
    float tots=0;
    glm::vec3 now1(*a->pppVertex[1]->vpCoordinate - *a->pppVertex[0]->vpCoordinate);
    glm::vec3 now2(*tp- *a->pppVertex[0]->vpCoordinate);
    tots=glm::length(glm::cross(now1,now2));

    now1=glm::vec3(*a->pppVertex[2]->vpCoordinate - *a->pppVertex[1]->vpCoordinate);
    now2=glm::vec3(*tp- *a->pppVertex[1]->vpCoordinate);
    tots+=glm::length(glm::cross(now1,now2));

    now1=glm::vec3(*a->pppVertex[0]->vpCoordinate - *a->pppVertex[2]->vpCoordinate);
    now2=glm::vec3(*tp- *a->pppVertex[2]->vpCoordinate);
    tots+=glm::length(glm::cross(now1,now2));

    if (abs(tots-glm::length(*a->vpNormalVector))<1E-5) return 1;
        else return 0;
}

// check if the vector intersects with the triangle plane
bool IsIntersect(PTriangle a,PVec4 tp,PVec3 vdir){
    glm::mat3 trans;
    float* hd=glm::value_ptr(trans);
    for (int i=0;i<3;++i){
        hd[3*i]=(*a->pppVertex[0]->vpCoordinate)[0]-(*tp)[0];
        hd[3*i+1]=(*a->pppVertex[1]->vpCoordinate)[1]-(*tp)[1];
        hd[3*i+2]=(*a->pppVertex[2]->vpCoordinate)[2]-(*tp)[2];
    }

    if (abs(glm::determinant(trans))<1E-5) return IsInArea(a,tp);

    glm::vec3 v=glm::inverse(trans)*(*vdir);
    if (v[0]<0 || v[1]<0 || v[2]<0) return 0;
        else return 1;
}

// check whether the point is in the object,
// return NULL or the closest plane(in global coordinate system)
PTriangle Object::IsInside(PVec4 tp,PVec3 vdir){
    if (!vdir) return NULL;

    // duplicate the vector
    glm::vec3 tvdir=-(*vdir);

    // ymw changed tp from PPoint to PVec4, pointing to the global coordinate
    int len=mppModelList[nModelType]->nLength;

    // lzh : I changed INT_MAX into FLT_MAX
    float dist=FLT_MAX;
    PTriangle ret=NULL;
    PTriangle now;
    float vl;
    int cnt=0;

    for (int i=0;i<len;++i){
        // get the Ith triangle's coordinates in global coordinate system
        // also rotate the normal vector
        now=MultTriangle(mpFrame,mppModelList[nModelType]->tppCone[i]);

        if (IsIntersect(now,tp,&tvdir)) ++cnt;

        // calculate the distance between the given point and the plane where triangle lies
        vl=glm::dot(*now->vpNormalVector,
                    *tp - *now->pppVertex[0]->vpCoordinate)
           /glm::length(*now->vpNormalVector);

        // update the dist
        if (abs(vl)<dist){dist=abs(vl); delete ret; ret=now;}
            else delete now;
    }

    return ret;
}

int ReadFiles(const char* str){
    FILE* modelin=fopen(str,"r");
    if (!modelin) throw FILE_NOT_FOUND;

    int len;
    float vol,dens,elas,radi;

    fscanf(modelin,"%d%f%f%f%f",&len,&vol,&dens,&elas,&radi);
    mppModelList[nModelTot]=new Model;
    mppModelList[nModelTot]->nLength=len;
    mppModelList[nModelTot]->fVolume=vol;
    mppModelList[nModelTot]->fMass=vol*dens;
    mppModelList[nModelTot]->fElastic=elas;
    mppModelList[nModelTot]->fMaxRadius=radi;
    mppModelList[nModelTot]->tppCone=new PTriangle[len];

    for (int j=0;j<len;++j){
        PPoint p[3];
        for (int k=0;k<3;++k){ // 3 points form a triangle
            float x,y,z,texx,texy;
            int isocur;

            fscanf(modelin,"%f%f%f%f%f%d",&x,&y,&z,&texx,&texy,&isocur);

            // generate random RGBcolor, no transparency
            p[k]=new Point(x,y,z,
                           (rand()%100)/100.0,
                           (rand()%100)/100.0,
                           (rand()%100)/100.0,1.0);
            p[k]->nFlag=isocur;
            (*p[k]->vpTexture)[0]=texx;
            (*p[k]->vpTexture)[1]=texy;
        }
        float x,y,z;
        fscanf(modelin,"%f%f%f",&x,&y,&z);

        glm::vec4 norm=glm::vec4(x,y,z,0);
        // one triangle forms a triangular-cone
        mppModelList[nModelTot]->tppCone[j]=new Triangle(p[0],p[1],p[2],&norm);
        delete p[0]; delete p[1]; delete p[2];
    }

    mppModelList[nModelTot]->mMomentOfInertia=new glm::mat3;
    float* col=glm::value_ptr(*mppModelList[nModelTot]->mMomentOfInertia);

    fscanf(modelin,"%f%f%f%f%f%f%f%f%f",
                    col,col+3,col+6,
                    col+1,col+4,col+7,
                    col+2,col+5,col+8);
    fclose(modelin);
    return nModelTot++;
}

void ModelCleanUp(){
    for (int i = 0; i < nModelTot; i++)
        delete mppModelList[i];
    for (int i = 0; i < nObjectTot; i++)
        delete oppObjectList[i];
    return ;
}
