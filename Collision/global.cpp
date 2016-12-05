/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Rev : 2016.12.05.13.06
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

bool Object::Init(int model_type,int material_type,GLfloat vx,GLfloat vy,GLfloat vz){
	if (model_type>nModeltot || material_type>nMaterialtot ||
		model_type<1 || material_type<1) {
			printf("Unknown Model or Material\n");
			return 0;
		}
	vSpeed=glm::vec3(vx,vy,vz);
	mFrame=glm::mat4(1.0);
	mStill=Model(mMateriallist[model_type]);
	mStill.fMass=mStill.fVolume*fMateriallist[material_type][0];
	mStill.fElastic=fMateriallist[material_type][1];
	mStill.fMomentInertia=0;//need to calculate,later update
}

Point::Point(){
	vpCoordinate=glm::vec4(0,0,0,0);
	vpColor=glm::vec4(0,0,0,0);
}

Point::Point(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b,GLfloat alpha){
	vpCoordinate=glm::vec4(x,y,z,1.0);
	vpColor=glm::vec4(r,g,b,alpha);
}

Triangle::Triangle(){
	pVertex[0]=pVertex[1]=pVertex[2]=Point();
	vNormal_vector=glm::vec4(0,0,0,0);
}

Triangle::Triangle(Point* a,Point* b,Point* c){
	pVertex[0]=*a; pVertex[1]=*b; pVertex[2]=*c;
	vNormal_vector=v4Cross(b->vpCoordinate - a->vpCoordinate,c->vpCoordinate - b->vpCoordinate);
}

Model::Model(){
	nLength=0;
	fMass=fMomentInertia=fElastic=fVolume=0;
	tCone=NULL;
}

Model::Model(Model* example){
	nLength=example->nLength;
	fMass=example->fMass;
	fMomentInertia=example->fMomentInertia;
	fElastic=example->fElastic;
	fVolume=example->fVolume;
	tCone=new Triangle[nLength];
	for (int i=0;i<nLength;++i) tCone[i]=example->tCone[i];
}
