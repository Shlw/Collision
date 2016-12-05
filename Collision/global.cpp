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

Triangle* Object::is_inside(Point* tp){




	return NULL;
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

Point::Point(Point* prttp){
printf("hellopoint\n");
	vpColor=new glm::vec4;
	*vpColor=*(prttp->vpColor);
printf("midpoint\n");
	vpCoordinate=new glm::vec4;
	*vpCoordinate=*(prttp->vpCoordinate);
printf("byepoint\n");
}

Point::Point(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b,GLfloat alpha){
	vpCoordinate=new glm::vec4(x,y,z,1.0);
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
printf("hello\n");

	pVertex[0]=new Point(a);
printf("hello0\n");
	pVertex[1]=new Point(b);
printf("hello1\n");
	pVertex[2]=new Point(c);
printf("hello2\n");
	vNormal_vector=new glm::vec4;
	*vNormal_vector=v4Cross(*(b->vpCoordinate) - *(a->vpCoordinate),
							*(c->vpCoordinate) - *(b->vpCoordinate));
printf("hello\n");
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
