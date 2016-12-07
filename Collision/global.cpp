/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Description : Fundamental implementation of global.hpp
 ************************************************************************/

#include "global.hpp"

glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b){
	glm::vec4 ret=glm::vec4(a[1]*b[2]-a[2]*b[1],
					  		-a[0]*b[2]+a[2]*b[0],
				  	   		a[0]*b[1]-a[1]*b[0],0);
	return ret;
}

GLfloat v4Dots(glm::vec4 a,glm::vec4 b){
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

GLfloat v4Length(glm::vec4 a){
	return sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
}

Point* MultPoint(glm::mat4* matrix,Point* p){
	Point* ret=new Point(p);
	*ret->vpCoordinate=(*matrix) * (*ret->vpCoordinate);
	return ret;
}

PTriangle MultTriangle(glm::mat4* matrix,PTriangle cone){
	PTriangle ret=new Triangle;
	for (int i=0;i<3;++i)
		ret->pVertex[i]=MultPoint(matrix,cone->pVertex[i]);
	ret->vNormal_vector=new glm::vec4((*matrix) * (*cone->vNormal_vector));
	return ret;
}

PTriangle Object::Is_inside(Point* tp){
	glm::vec4* plocat=tp->vpCoordinate;
	int len=mModellist[nModeltype].nLength;
	GLfloat dist=INT_MAX;
	PTriangle ret=NULL;

	for (int i=0;i<len;++i){
		PTriangle now=MultTriangle(mFrame,mModellist[nModeltype].tCone[i]);
		GLfloat vl=v4Dots(*now->vNormal_vector,
						  *tp->vpCoordinate - *now->pVertex[0]->vpCoordinate);
		if (vl>0){delete now; delete ret; return NULL;}
		vl=-vl/v4Length(*now->vNormal_vector);
		if (vl<dist) {dist=vl; delete ret; ret=now;}
	}

	return ret;
}

Object::Object(){
	nModeltype=0;
	fMomentInertia=fElastic=fMass=0.0;
	mFrame=NULL;
	vSpeed=NULL;
}

Object::~Object(){
	delete mFrame;
	delete vSpeed;
}

bool Object::Init(int model_type,int material_type,GLfloat vx,GLfloat vy,GLfloat vz){
	if (model_type>nModeltot || material_type>nMaterialtot ||
		model_type<1 || material_type<1) {
			printf("Unknown Model or Material\n");
			return 0;
		}
	vSpeed=new glm::vec3(vx,vy,vz);
	mFrame=new glm::mat4(1.0);
	nModeltype=model_type;
	fMass=mModellist[model_type].fVolume*fMateriallist[material_type][0];
	fElastic=fMateriallist[material_type][1];
	fMomentInertia=0; 						//need to calculate,later update
	return 1;
}

Point::Point(){
	vpCoordinate=NULL;
	vpColor=NULL;
}

Point::Point(Point* example){
	vpColor=new glm::vec4(*example->vpColor);
	vpCoordinate=new glm::vec4(*example->vpCoordinate);
}

Point::Point(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b,GLfloat alpha){
	vpCoordinate=new glm::vec4(x,y,z,1);
	vpColor=new glm::vec4(r,g,b,alpha);
}

Point::~Point(){
	delete vpCoordinate;
	delete vpColor;
}

Triangle::Triangle(){
	pVertex[0]=pVertex[1]=pVertex[2]=NULL;
	vNormal_vector=NULL;
}

Triangle::Triangle(Point* a,Point* b,Point* c){
	pVertex[0]=new Point(a);
	pVertex[1]=new Point(b);
	pVertex[2]=new Point(c);
	vNormal_vector=new glm::vec4;
	*vNormal_vector=v4Cross(*b->vpCoordinate - *a->vpCoordinate,
							*c->vpCoordinate - *b->vpCoordinate);
}

Triangle::~Triangle(){
	delete pVertex[0]; delete pVertex[1]; delete pVertex[2];
	delete vNormal_vector;
}

Model::Model(){
	nLength=0;
	fVolume=0.0;
	tCone=NULL;
}

Model::~Model(){
	for (int i=0;i<nLength;++i) delete tCone[i];
	delete[] tCone;
}

//int main(int argc,char* argv[]){}
