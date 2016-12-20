/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw lzh Shlw lzh Shlw lzh Shlw lzh
 * Description : Implementation of fundamental things.
 ************************************************************************/

#include "global.hpp"

int nModelTot; // number of models
int nMaterialTot; // number of materials
int nObjectTot; // number of objects
PModel mppModelList[100];
PObject oppObjectList[100];
// first is density, second is elasticity
double dppMaterialList[100][2];

// Declarations of global variables
// int nWindowFlags = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE;
int nInitWindowWidth = 1024, nInitWindowHeight = 768;

#ifdef DEBUG
const char* cpWindowTitle = "Collision Demo";
#else
const char* cpWindowTitle = "Collision";
#endif

double dLastClock, dLastLastClock;
int nLastSecond;
double dLastMouseX, dLastMouseY;
// Array to store the state of mouse buttons, where [0], [1], [2]
// represent left, middle and right button resepectively.
int npButtonState[3];
glm::dmat4 mModelTransformMat;

double dRotateSpeed = 0.005;
double dTranslateSpeed = 0.005;
double dScrollSpeed = 0.10;

double dpBoxLimit[6] = {-1.0, 1.0, -1.0, 1.0, -1.0, 1.0};

int nTextureLength = 5;
const char* cpTextureName = "Texture.txt";
int* npPicWidth, * npPicHeight;
unsigned char** ucppPicContent;
int* npTextureIndex;

float fpLightPosition[4] = {0.0, 2.0, 0.0, 0.0};
float fpLightAmbient[4] = {0.2, 0.2, 0.2, 1.0};
float fpLightDiffuse[4] = {0.8, 0.6, 0.4, 1.0};
float fpLightSpecular[4] = {0.2, 0.15, 0.1, 1.0};
float fpMaterialShininess[1] = {24.0f};
float fpMaterialSpecular[4] = {1.0, 1.0, 1.0, 1.0};
float fpMaterialAmbientDiffuse[4] = {1.0, 1.0, 1.0, 1.0};

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
    ret->vpNormalVector=new glm::dvec4((*matrix) * (*cone->vpNormalVector));

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
    vpColor=new glm::dvec4(*example->vpColor);
    vpCoordinate=new glm::dvec4(*example->vpCoordinate);
    vpTexture=new glm::dvec2(*example->vpTexture);
    nFlag=example->nFlag;
}
// initialize the point class according to all the data needed
Point::Point(
    float x,float y,float z,
    float r,float g,float b,float alpha){

    vpCoordinate=new glm::dvec4(x,y,z,1.0);
    vpColor=new glm::dvec4(r,g,b,alpha);
    vpTexture=new glm::dvec2(0,0);
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
    vpNormalVector=new glm::dvec4(
        glm::cross(glm::dvec3(*b->vpCoordinate - *a->vpCoordinate),
        glm::dvec3(*c->vpCoordinate - *b->vpCoordinate)),
        0.0
    );
}
// initialize the triangle class with 3 given points(local coordinate system) and normal vector
Triangle::Triangle(PPoint a,PPoint b,PPoint c,PVec4 v){
    pppVertex[0]=new Point(a);
    pppVertex[1]=new Point(b);
    pppVertex[2]=new Point(c);
    vpNormalVector=new glm::dvec4(*v);
}
// destroy the triangle class
Triangle::~Triangle(){
    delete pppVertex[0]; delete pppVertex[1]; delete pppVertex[2];
    delete vpNormalVector;
}

// initialize the model class
Model::Model(){
    nLength=0;
    dVolume=dElastic=dMass=dMaxRadius=0.0;
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
    dMomentInertia=0.0;
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
Object::Object(int model,double vx,double vy,double vz,double mx,double my,double mz){
    // lzh : use throw to handle exceptions
    if (model>=nModelTot || model<0)
        throw ERROR_UNKNOWN_MODEL;
    vpSpeed=new glm::dvec3(vx,vy,vz);
    vpAngularMomentum=new glm::dvec3(mx,my,mz);
    mpFrame=new glm::dmat4(1.0); // load the identity matrix into mFrame

    nModelType=model;
    // need to calculate, later update
    dMomentInertia=0;
}

// check if the point is in the triangle
bool IsInArea(PTriangle a,PVec4 tp){
    double tots=0;
    glm::dvec3 now1(*a->pppVertex[1]->vpCoordinate - *a->pppVertex[0]->vpCoordinate);
    glm::dvec3 now2(*tp- *a->pppVertex[0]->vpCoordinate);
    tots=glm::length(glm::cross(now1,now2));

    now1=glm::dvec3(*a->pppVertex[2]->vpCoordinate - *a->pppVertex[1]->vpCoordinate);
    now2=glm::dvec3(*tp- *a->pppVertex[1]->vpCoordinate);
    tots+=glm::length(glm::cross(now1,now2));

    now1=glm::dvec3(*a->pppVertex[0]->vpCoordinate - *a->pppVertex[2]->vpCoordinate);
    now2=glm::dvec3(*tp- *a->pppVertex[2]->vpCoordinate);
    tots+=glm::length(glm::cross(now1,now2));

    if (abs(tots-glm::length(*a->vpNormalVector))<1E-5) return 1;
        else return 0;
}

// check if the vector intersects with the triangle plane
bool IsIntersect(PTriangle a,PVec4 tp,PVec3 vdir){
    glm::dmat3 trans;
    double* hd=glm::value_ptr(trans);
    for (int i=0;i<3;++i){
        hd[3*i]=(*a->pppVertex[0]->vpCoordinate)[0]-(*tp)[0];
        hd[3*i+1]=(*a->pppVertex[1]->vpCoordinate)[1]-(*tp)[1];
        hd[3*i+2]=(*a->pppVertex[2]->vpCoordinate)[2]-(*tp)[2];
    }

    if (fabs(glm::determinant(trans))<1E-5) return IsInArea(a,tp);

    glm::dvec3 v=glm::inverse(trans)*(*vdir);
    if (v[0]<0 || v[1]<0 || v[2]<0) return 0;
        else return 1;
}

/*
// check whether the point is in the object,
// return NULL or the closest plane(in global coordinate system)
PTriangle Object::IsInside(PVec4 tp,PVec3 vdir){
    if (!vdir) return NULL;

    // duplicate the vector
    glm::dvec3 tvdir=-(*vdir);

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
*/

// check whether the point is in the object,
// return NULL or the closest plane(in global coordinate system)
PTriangle Object::IsInside(PVec4 tp,PVec3 vdir){
    // ymw changed tp from PPoint to PVec4, pointing to the global coordinate
    int len=mppModelList[nModelType]->nLength;
    // lzh : I changed INT_MAX into FLT_MAX
    double dist=DBL_MAX;
    PTriangle ret=NULL;
    PTriangle now;
    double vl;

    for (int i=0;i<len;++i){
        // get the Ith triangle's coordinates in global coordinate system
        // also rotate the normal vector
        now=MultTriangle(mpFrame,mppModelList[nModelType]->tppCone[i]);

        // calculate the volume of the cone formed by given point and the Ith triangle
        vl=glm::dot(*now->vpNormalVector,
                          *tp - *now->pppVertex[0]->vpCoordinate);

        // not inside the left half space , return not_inside
        if (vl>0){delete now; delete ret; return NULL;}

        // calculate the distance between the given point and the plane where triangle lies
        vl=-vl/glm::length(*now->vpNormalVector);

        // update the dist
        if (vl<dist) {dist=vl; delete ret; ret=now;}
        else
            delete now;
    }

    return ret;
}

int ReadFiles(const char* str){
    FILE* modelin=fopen(str,"r");
    if (!modelin) throw FILE_NOT_FOUND;

    int len;
    double vol,dens,elas,radi;

    fscanf(modelin,"%d%lf%lf%lf%lf",&len,&vol,&dens,&elas,&radi);
    mppModelList[nModelTot]=new Model;
    mppModelList[nModelTot]->nLength=len;
    mppModelList[nModelTot]->dVolume=vol;
    mppModelList[nModelTot]->dMass=vol*dens;
    mppModelList[nModelTot]->dElastic=elas;
    mppModelList[nModelTot]->dMaxRadius=radi;
    mppModelList[nModelTot]->tppCone=new PTriangle[len];

    for (int j=0;j<len;++j){
        PPoint p[3];
        for (int k=0;k<3;++k){ // 3 points form a triangle
            double x,y,z,texx,texy;
            int isocur;

            fscanf(modelin,"%lf%lf%lf%lf%lf%d",&x,&y,&z,&texx,&texy,&isocur);

            // generate random RGBcolor, no transparency
            p[k]=new Point(x,y,z,
                           (rand()%100)/100.0,
                           (rand()%100)/100.0,
                           (rand()%100)/100.0,1.0);
            p[k]->nFlag=isocur;
            (*p[k]->vpTexture)[0]=texx;
            (*p[k]->vpTexture)[1]=texy;
        }
        double x,y,z;
        fscanf(modelin,"%lf%lf%lf",&x,&y,&z);

        glm::dvec4 norm=glm::dvec4(x,y,z,0);
        // one triangle forms a triangular-cone
        mppModelList[nModelTot]->tppCone[j]=new Triangle(p[0],p[1],p[2],&norm);
        delete p[0]; delete p[1]; delete p[2];
    }

    mppModelList[nModelTot]->mMomentOfInertia=new glm::dmat3;
    double* col=glm::value_ptr(*mppModelList[nModelTot]->mMomentOfInertia);

    fscanf(modelin,"%lf%lf%lf%lf%lf%lf%lf%lf%lf",
                    col,col+3,col+6,
                    col+1,col+4,col+7,
                    col+2,col+5,col+8);
    for (int i = 0; i < 9; i++)
        col[i] *= dens;
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
