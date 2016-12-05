/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Rev : 2016.12.05.13.06
 * Description : Fundamental Math support and init implementation for global.hpp
 ************************************************************************/

#include "global.hpp"

glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b){
	glm::vec4 ret=glm::vec4(a[1]*b[2]-a[2]*b[1],
					  		-a[0]*b[2]+a[2]*b[0],
				  	   		a[0]*b[1]-a[1]*b[0],1.0);
	return ret;
}

GLfloat v4Dots(glm::vec4 a,glm::vec4 b){
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

std::pair<GLfloat,GLfloat> get_material(int which_type){
	FILE* input=fopen("material.txt","r");
	int tot;
	GLfloat x,y;
	std::pair<GLfloat,GLfloat> ret;
	fscanf(input,"%d",&tot);
	if (tot>which_type || which_type<1) x=y=0;
		else for (int i=1;i<=which_type) fscanf(input,"%f%f",&x,&y);
	ret=std::make_pair(x,y);
	fclose(input);
	return ret;
}

void fix_centroid(int num,GLfloat node[][3]){
	GLfloat cx=0,cy=0,cz=0;
	for (int i=0;i<num;++i)
		cx+=node[i][0],cy+=node[i][1],cz+=node[i][2];
	cx/=num; cy/=num; cz/=num;
	for (int i=0;i<num;++i)
		node[i][0]-=cx,node[i][1]-=cy,node[i][2]-=cz;
}

bool Object::init(int num,GLfloat node[][3],int which_type){
	std::pair<GLfloat,GLfloat> material=get_material(which_type);
	if (material.first==0){
		printf("Unknown Material!\n");
		return 0;
	}
	if (num<4){
		printf("Not a Polyhedron!\n");
		return 0;
	}

	fix_centroid(num,node);


}
