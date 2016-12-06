/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Description : Implementation of global.hpp
 ************************************************************************/

#include "global.hpp"

// glmvec4 cross product
glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b){
	glm::vec4 ret=glm::vec4(a[1]*b[2]-a[2]*b[1],
					  		-a[0]*b[2]+a[2]*b[0],
				  	   		a[0]*b[1]-a[1]*b[0],0);
	return ret;
}

// glmvec4 dot product
GLfloat v4Dot(glm::vec4 a,glm::vec4 b){
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

// glmvec4 length
GLfloat v4Length(glm::vec4 a){
	return sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
}

// matrix multiplication left to a point
Point* MultPoint(glm::mat4* matrix,Point* p){
	Point* ret=new Point(p);
	*ret->vpCoordinate=(*matrix) * (*ret->vpCoordinate);
	return ret;
}

// matrix multiplication left to a triangle
PTriangle MultTriangle(glm::mat4* matrix,PTriangle cone){
	PTriangle ret=new Triangle;

	// calculate the global coordinate of vertices
	for (int i=0;i<3;++i)
		ret->pVertex[i]=MultPoint(matrix,cone->pVertex[i]);

	// rotate the normal vector
	ret->vNormal_vector=new glm::vec4((*matrix) * (*cone->vNormal_vector));
	return ret;
}

// check whether the point is in the object,
// return NULL or the closest plane(in global coordinate system)
PTriangle Object::Is_inside(Point* tp){
	int len=mModellist[nModeltype].nLength;
	GLfloat mindist=INT_MAX;
	PTriangle ret=NULL;

	for (int i=0;i<len;++i){
		// get the Ith triangle's coordinates in global coordinate system
		// also rotate the normal vector
		PTriangle now=MultTriangle(mFrame,mModellist[nModeltype].tCone[i]);

		// calculate the volume of the cone formed by given point and the Ith triangle
		GLfloat vl=v4Dot(*now->vNormal_vector,
						  *tp->vpCoordinate - *now->pVertex[0]->vpCoordinate);

		// not inside the left half space , return not_inside
		if (vl>0){delete now; delete ret; return NULL;}

		// calculate the distance between the given point and the plane where triangle lies
		vl=-vl/v4Length(*now->vNormal_vector);

		// update the mindist
		if (vl<mindist) {mindist=vl; delete ret; ret=now;}
	}

	return ret;
}

// initialize the object class
Object::Object(){
	nModeltype=0;
	fMomentInertia=fElastic=fMass=0.0;
	mFrame=NULL;
	vSpeed=NULL;
}

// destroy the object class
Object::~Object(){
	delete mFrame;
	delete vSpeed;
}

// use specific model and material type to initialize the object
// also need to input the velocity
// return whether the object created successfully
bool Object::Init(int model_type,int material_type,GLfloat vx,GLfloat vy,GLfloat vz){
	if (model_type>nModeltot || material_type>nMaterialtot ||
		model_type<1 || material_type<1) {
			printf("Unknown Model or Material\n");
			return 0;
		}

	vSpeed=new glm::vec3(vx,vy,vz);
	mFrame=new glm::mat4(1.0); // load the identity matrix into mFrame

	nModeltype=model_type;
	fMass=mModellist[model_type].fVolume*fMateriallist[material_type][0];
	fElastic=fMateriallist[material_type][1];
	fMomentInertia=0; 			//////////////// ATTENTION!!! need to calculate,later update

	return 1;
}

// initialize the point class
Point::Point(){
	vpCoordinate=NULL;
	vpColor=NULL;
}

// initialize the point class by duplicating an example
Point::Point(Point* example){
	vpColor=new glm::vec4(*example->vpColor);
	vpCoordinate=new glm::vec4(*example->vpCoordinate);
}

// initialize the point class according to all the data needed
Point::Point(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b,GLfloat alpha){
	vpCoordinate=new glm::vec4(x,y,z,1);
	vpColor=new glm::vec4(r,g,b,alpha);
}

// destroy the point class
Point::~Point(){
	delete vpCoordinate;
	delete vpColor;
}

// initialize the triangle class
Triangle::Triangle(){
	pVertex[0]=pVertex[1]=pVertex[2]=NULL;
	vNormal_vector=NULL;
}

// initialize the triangle class with 3 given points(local coordinate system)
Triangle::Triangle(Point* a,Point* b,Point* c){
	pVertex[0]=new Point(a);
	pVertex[1]=new Point(b);
	pVertex[2]=new Point(c);
	vNormal_vector=new glm::vec4;
	*vNormal_vector=v4Cross(*b->vpCoordinate - *a->vpCoordinate,
							*c->vpCoordinate - *b->vpCoordinate);
}

// destroy the triangle class
Triangle::~Triangle(){
	delete pVertex[0]; delete pVertex[1]; delete pVertex[2];
	delete vNormal_vector;
}

// initialize the model class
Model::Model(){
	nLength=0;
	fVolume=0.0;
	tCone=NULL;
}

// destroy the model class
Model::~Model(){
	for (int i=0;i<nLength;++i) delete tCone[i];
	delete[] tCone;
}
