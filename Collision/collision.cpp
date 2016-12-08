/*************************************************************************
 * main.cpp for project Collision
 * Author : lzh
 * Modifier : Shlw
 * Description : Source file to implement main, which calls functions and
 * enters glutMainLoop.
 ************************************************************************/

// Inclusion of global header
<<<<<<< HEAD

#include "global.hpp"
=======
#include "global.hpp"

int nModeltot;
int nMaterialtot;
Model mModellist[100];
GLfloat fMateriallist[100][2]; // first is density, second is elasticity
int nWindowFlags;
int nInitWindowWidth;
int nInitWindowHeight;
int nTimerSpeed;
const char* cpWindowTitle;
int nLastClock;

//prepare for later usage, don't need to be extern
void preinput(){
	FILE* materialin=fopen("material.txt","r"); // 3 kinds of material
	FILE* modelin=fopen("model.txt","r"); // 3 kinds of model--Cube, Cuboid, Regular-Triangular-Pyramid

	fscanf(materialin,"%d",&nMaterialtot);
	for (int i=1;i<=nMaterialtot;++i)
		fscanf(materialin,"%f%f",fMateriallist[i],fMateriallist[i]+1); // frist is density, then the elasticity

	fscanf(modelin,"%d",&nModeltot);
	for (int i=1;i<=nModeltot;++i){
		int len;
		GLfloat vol;
		fscanf(modelin,"%d%f",&len,&vol);
		mModellist[i].nLength=len;  // number of surfaces of the model
		mModellist[i].fVolume=vol;  // volume of the model
		mModellist[i].tCone=new PTriangle[len];  // TriangularCone-Divide the model, coordinate-origin is the center

		for (int j=0;j<len;++j){
			Point* p[3];
			for (int k=0;k<3;++k){  // 3 points form a triangle
				GLfloat x,y,z;
				fscanf(modelin,"%f%f%f",&x,&y,&z);
				p[k]=new Point(x,y,z,
						   	   (rand()%100)/100.0,		// generate random RGBcolor, no transparency
						   	   (rand()%100)/100.0,
						   	   (rand()%100)/100.0,0);
			}
			mModellist[i].tCone[j]=new Triangle(p[0],p[1],p[2]);  // one triangle forms a triangular-cone
			delete p[0]; delete p[1]; delete p[2];
		}

	}

	fclose(materialin);
	fclose(modelin);
}

// print the Triangle, for test ,ought to be removed
void printTri(PTriangle t){
	for (int i=0;i<3;++i){
		for (int j=0;j<3;++j)
			printf("%f ",(*t->pVertex[i]->vpCoordinate)[j]);
		printf("\n");
	}
}
>>>>>>> refs/remotes/origin/master

// The main function
int main(int argc, char *argv[])
{
<<<<<<< HEAD
    srand(time(NULL));
    
    ReadFiles();
    
    GameInit();
    
=======
	srand(time(0));

	// input pre-set models and materials
	preinput();

	/* test part, ought to be removed, you can use it as a test example

	Object* testobj=new Object;
	testobj->Init(1,1,0,0,0);
	Point* testp=new Point(0.9,0.99,0.95,1,1,1,0);

	PTriangle testinside=testobj->Is_inside(testp);

	if (!testinside) printf("Not inside!\n");
		else {
			printf("Inside!\nClosest Plane is\n");
			printTri(testinside);
		}
	*/

>>>>>>> refs/remotes/origin/master
    // Initialize function of glut
    glutInit(&argc, argv);
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
    
    CleanUp();
    
    return 0;
}
