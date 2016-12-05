/*************************************************************************
 * global.cpp for project Collision
 * Author : Shlw
 * Modifier : Shlw
 * Rev : 2016.12.05.13.06
 * Description : Global function for the whole project.
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b){
	glm::vec4 ret=glm::vec4(a[1]*b[2]-a[2]*b[1],
					  		-a[0]*b[2]+a[2]*b[0],
				  	   		a[0]*b[1]-a[1]*b[0],1.0);
	return ret;
}

GLfloat v4Dots(glm::vec4 a,glm::vec4 b){
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}
