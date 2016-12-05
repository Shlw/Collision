/*************************************************************************
 * main.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw
 * Rev : 2016.12.05.18.43
 * Description : Source file to implement main, which calls functions and
 * enters glutMainLoop.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

int nModeltot;
int nMaterialtot;
Model mModellist[100];
GLfloat fMateriallist[100][2]; //first is density, second is elasticity
int nWindowFlags;
int nInitWindowWidth;
int nInitWindowHeight;
int nTimerSpeed;
const char* cpWindowTitle;
int nLastClock;

void preinput(){
	FILE* materialin=fopen("material.txt","r");
	FILE* modelin=fopen("model.txt","r");

	fscanf(materialin,"%d",&nMaterialtot);
	for (int i=1;i<=nMaterialtot;++i)
		fscanf(materialin,"%f%f",fMateriallist[i],fMateriallist[i]+1);

	fscanf(modelin,"%d",&nModeltot);
	for (int i=1;i<=nModeltot;++i){
		int len;
		GLfloat vol;
		fscanf(modelin,"%d%f",&len,&vol);
		mModellist[i].nLength=len;
		mModellist[i].fVolume=vol;
		mModellist[i].tCone=new PTriangle[len];
printf("hello\n");

		for (int j=0;j<len;++j){
			Point* p[3];
			for (int k=0;k<3;++k){
				GLfloat x,y,z;
				fscanf(modelin,"%f%f%f",&x,&y,&z);
				p[i]=new Point(x,y,z,
						   	   (rand()%100)/100.0,
						   	   (rand()%100)/100.0,
						   	   (rand()%100)/100.0,0);
			}
printf("hellonewtri\n");
			mModellist[i].tCone[j]=new Triangle(p[0],p[1],p[2]);
printf("hello\n");
			p[0]->~Point(); p[1]->~Point(); p[2]->~Point();
		}

	}

	fclose(materialin);
	fclose(modelin);
}

// The main function
int main(int argc, char *argv[])
{
	srand(time(0));
	preinput();
	int test;
	scanf("%d",&test);
	glm::vec4 hello=glm::vec4(1,2,3,4);
	printf("%lf\n",hello[test]);
	//printf("%lf\n",*((mModellist[test].tCone[0])->pVertex[0]->vpCoordinate)[0]);
    // Initialize function of glut
/*    glutInit(&argc, argv);
    glutInitDisplayMode(nWindowFlags);
    glutInitWindowSize(nInitWindowWidth, nInitWindowHeight);

    // Create a window and initialilze
    glutCreateWindow(cpWindowTitle);
    WindowInit();

    // Register display function
    glutDisplayFunc(Display);

    // Setup a timer to refresh
    glutTimerFunc(nTimerSpeed, OnTimer, 1);

    // Go on main loop until Quit is called
    glutMainLoop();
*/
    return 0;
}
