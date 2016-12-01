//  main.cpp
//  GL_test
//
//  Created by  WhitePhosphorus on 16/11/14.
//  Copyright © 2016年  WhitePhosphorus. All rights reserved.
//

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <Carbon/Carbon.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;


#define FRAME_PITCH 33 // time(ms) between two frames
#define MAX_OBJ_NUM 3
#define DIMENSION 3
#define G 100.0
#define LACOE 0.1 // the coefficient of gluLookAt, affecting the speed of view adjustment
#define MAX_Y 1.0/LACOE // the limit of the view

GLfloat WindowWidth = 800.0, WindowHeight = 600.0, nRange = 600.0,
        rotateX, rotateY = rotateX = 0;
int beginX, beginY;
bool Pause = false, plus_one_second = false,
     hit[MAX_OBJ_NUM][MAX_OBJ_NUM] = {0};

class vec3 {
protected:
    GLfloat x, y, z;
public:
    
    vec3() {}
    vec3(GLfloat x, GLfloat y, GLfloat z): x(x), y(y), z(z) {}
    vec3(const vec3 &a): x(a.x), y(a.y), z(a.z) {}
    
    GLfloat getX() const { return x; }
    GLfloat getY() const { return y; }
    GLfloat getZ() const { return z; }
    
    const vec3 &operator =(const vec3 &a) {
        x=a.x; y=a.y; z=a.z;
        return *this;
    }
    
    bool operator ==(const vec3 &a) {
        if (x==a.x && y==a.y && z==a.z) return true;
        return false;
    }
    
    vec3 operator +(const vec3 &a) {
        return vec3(x+a.x, y+a.y, z+a.z);
    }
    const vec3 &operator +=(const vec3 &a) {
        x+=a.x; y+=a.y; z+=a.z;
        return *this;
    }
    vec3 operator -(const vec3 &a) {
        return vec3(x-a.x, y-a.y, z-a.z);
    }
    const vec3 &operator -=(const vec3 &a) {
        x-=a.x; y-=a.y; z-=a.z;
        return *this;
    }
    GLfloat dot(const vec3 &a) {
        return x*a.x+y*a.y+z*a.z;
    }
    vec3 operator *(const vec3 &a) {
        return vec3(y*a.z-z*a.y, z*a.x-x*a.z, x*a.y-y*a.x);
    }
    vec3 operator *(GLfloat a) {
        return vec3(a*x,a*y,a*z);
    }
    friend vec3 operator *(GLfloat a, const vec3 &b) {
        return vec3(a*b.x,a*b.y,a*b.z);
    }
    const vec3 &operator *=(GLfloat a) {
        x*=a; y*=a; z*=a;
        return *this;
    }
    vec3 operator /(GLfloat a) {
        return vec3(x/a,y/a,z/a);
    }
    const vec3 &operator /=(GLfloat a) {
        x/=a; y/=a; z/=a;
        return *this;
    }
    
    GLfloat len(bool square = true) const {
        if (square) return (x*x+y*y+z*z);
        return sqrt(x*x+y*y+z*z);
    }
    vec3 normoalize() {
        GLfloat l = this->len(false);
        return vec3(x/l, y/l, z/l);
    }
    
    // for test
    friend ostream & operator <<(ostream &out, const vec3 &a) {
        out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
        return out;
    }
    friend istream & operator >>(istream &in, vec3 &a) {
        printf("please input a vector (x, y, z) in order of x, y and z:\n");
        in >> a.x >> a.y >> a.z;
        return in;
    }
};

class obj {
protected:
    GLfloat m, size;
    vec3 pos, vel, acc;
    GLfloat energy; // kinetic, potential energy
public:
    
    obj() {}
    obj(vec3 p, vec3 v, vec3 a, GLfloat m, GLfloat s): pos(p), vel(v), acc(a), m(m), size(s) {}
    
    GLfloat getMass() { return m; }
    GLfloat getSize() { return size; }
    const vec3 &getPos() { return pos; }
    const vec3 &getVel() { return vel; }
    const vec3 &getAcc() { return acc; }
    void setPos(const vec3 &delta) { pos = delta; }
    void setVel(const vec3 &delta) { vel = delta; }
    void setAcc(const vec3 &delta) { acc = delta; }
    void changePos(const vec3 &delta) { pos += delta; }
    void changeVel(const vec3 &delta) { vel += delta; }
    void changeAcc(const vec3 &delta) { acc += delta; }
    GLfloat calEk() { // calculate kinetic energy
        return 0.5 * m * vel.len();
    }
    
    bool hitTest(obj &a) {
        vec3 m(a.pos - pos);
        return (m.len() <= a.getSize() + size);
    }
};
obj object[] = {
    /*
     两颗行星绕恒星圆周运动: G*M == v*v*R*/
    obj(vec3(0.0,-100.0,0.0), vec3(10.0,0.0,0.0), vec3(0.0,0.0,0.0), 0.0, 5.0),
    obj(vec3(0.0,100.0,0.0), vec3(-10.0,0.0,0.0), vec3(0.0,0.0,0.0), 0.0, 5.0),
    obj(vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), 100.0, 15.0)
    
    /*
     椭圆
    obj(vec3(0.0,-100.0,0.0), vec3(12.0,0.0,0.0), vec3(0.0,0.0,0.0), 0.0, 5.0),
    obj(vec3(0.0,100.0,0.0), vec3(-12.0,0.0,0.0), vec3(0.0,0.0,0.0), 0.0, 5.0),
    obj(vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), 100.0, 15.0)
    */
    /*
     进动的椭圆
    obj(vec3(0.0,-100.0,0.0), vec3(7.0,0.0,0.0), vec3(0.0,0.0,0.0), 0.0, 5.0),
    obj(vec3(0.0,100.0,0.0), vec3(-7.0,0.0,0.0), vec3(0.0,0.0,0.0), 0.0, 5.0),
    obj(vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), 100.0, 15.0)
    */
    /*
     迟早药丸的椭圆
    obj(vec3(0.0,-100.0,0.0), vec3(7.0,0.0,0.0), vec3(0.0,0.0,0.0), 0.0, 5.0),
    obj(vec3(0.0,100.0,0.0), vec3(-8.0,0.0,0.0), vec3(0.0,0.0,0.0), 0.0, 5.0),
    obj(vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), 100.0, 15.0)
     */
    /* G*M == sqrt(3)*v*v*R，理论上是三个恒星圆周运动，实际上误差不能忍
    obj(vec3(0.0,-100.0*sqrt(3),0.0), vec3(-10.0,0.0,0.0), vec3(0.0,0.0,0.0), 300.0, 15.0),
    obj(vec3(150.0,50.0*sqrt(3),0.0), vec3(5.0,-5.0*sqrt(3),0.0), vec3(0.0,0.0,0.0), 300.0, 15.0),
    obj(vec3(-150.0,50.0*sqrt(3),0.0), vec3(5.0,5.0*sqrt(3),0.0), vec3(0.0,0.0,0.0), 300.0, 15.0)
     */
};

void ranGen() {
    int large = rand() % MAX_OBJ_NUM / 2 + 1;
    for (int i = 0; i < MAX_OBJ_NUM; ++i) {
        if (i < large) {
            object[i] = obj(vec3(rand() % (int)WindowWidth-WindowWidth/2,
                                rand() % (int)WindowHeight-WindowHeight/2, rand() % 100),
                           vec3(i * 30.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0),
                           rand() % 300 + 100, rand() % 10 + 20);
            
        } else {
            object[i] = obj(vec3(rand() % (int)WindowWidth-WindowWidth/2,
                                rand() % (int)WindowHeight-WindowHeight/2, rand() % 100),
                           vec3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10),
                           vec3(0.0, 0.0, 0.0), rand() % 100 / 10.0, rand() % 10 + 5);
        }
    }
}

void show_text(char *text_toshow, GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b) {
    /* There are 7 bitmap fonts available in GLUT. They are
     GLUT_BITMAP_8_BY_13
     GLUT_BITMAP_9_BY_15
     GLUT_BITMAP_TIMES_ROMAN_10
     GLUT_BITMAP_TIMES_ROMAN_24
     GLUT_BITMAP_HELVETICA_10
     GLUT_BITMAP_HELVETICA_12
     GLUT_BITMAP_HELVETICA_18 */
    void * font = GLUT_BITMAP_HELVETICA_18;
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    for (int i=0; i<=strlen(text_toshow); ++i) {
        char c = text_toshow[i];
        glutBitmapCharacter(font, c);
    }
}

void drawArrow(vec3 start, vec3 end, vec3 color, GLfloat theta = M_PI/6) {
    glColor3f(color.getX(), color.getY(), color.getZ());
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
        glVertex3d(start.getX(), start.getY(), start.getZ());
        glVertex3d(end.getX(), end.getY(), end.getZ());
    glEnd();
    glTranslatef(end.getX(), end.getY(), end.getZ());
    glutSolidCone(10, 10, 100, 100);
    glTranslatef(-end.getX(), -end.getY(), -end.getZ());
    glDisable(GL_LINE_SMOOTH);
}

int clearLoop = 0;
void renderScene() {
    if (++clearLoop % 5 == 1) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
    glRectf(-WindowWidth, WindowHeight, WindowWidth, -WindowHeight);
    //show_text("Hello world!", 30, 30, 0, 0.0, 0.0, 1.0);
    if (plus_one_second) show_text("EXCITED!!!",-10,-10,-10,1,1,1);
    for (int i = 0; i < MAX_OBJ_NUM; ++i) {
        glColor3f(0.0f, (float)i / (MAX_OBJ_NUM-1), 1.0f - (float)i / (MAX_OBJ_NUM-1));
        vec3 t = object[i].getPos();
        glTranslatef(t.getX(), t.getY(), t.getZ());
        glutSolidSphere(object[i].getSize(), 100, 100);
        glTranslatef(-t.getX(), -t.getY(), -t.getZ());
    }
    
    drawArrow(vec3(0,0,0), vec3(WindowWidth,0,0), vec3(1,1,1));
    drawArrow(vec3(0,0,0), vec3(0,WindowWidth,0), vec3(1,1,1));
    drawArrow(vec3(0,0,0), vec3(0,0,WindowHeight), vec3(1,1,1));
    glutSwapBuffers();
}

void setupRC() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glFrontFace(GL_CW);
}

void changeSize(GLsizei w, GLsizei h) {
    GLfloat AspectRatio;
    
    if (!h) h = 1;
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    AspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange / AspectRatio, nRange / AspectRatio, nRange, -nRange);
    else
        glOrtho(-nRange * AspectRatio, nRange * AspectRatio, -nRange, nRange, nRange, -nRange);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

GLfloat dis(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, bool square = false) {
    if (square) return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int delay = 0;
void TimerFunction(int value) {
    glLoadIdentity();
    if (fabs(rotateY) > MAX_Y) rotateY = MAX_Y * (rotateY > 0 ? 1 : -1);
    gluLookAt(cos(rotateX*LACOE), sin(rotateX*LACOE), rotateY*LACOE, 0,0,0,0,0,1.0);
    if (Pause) {
        glutPostRedisplay();
        glutTimerFunc(FRAME_PITCH, TimerFunction, value);
        return;
    }
    for (int i = 0; i < MAX_OBJ_NUM; ++i) {
        vec3 pos = object[i].getPos(), vel = object[i].getVel();
        
        // update acceleration
        object[i].changeAcc(-1*object[i].getAcc());
        for (int j = 0; j < MAX_OBJ_NUM; ++j) {
            if (i == j) continue;
            vec3 dpos = pos - object[j].getPos();
            GLfloat coef = -G * object[j].getMass() / dpos.len();
            object[i].changeAcc(coef*dpos.normoalize());
        }
        
        // update v
        object[i].changeVel(object[i].getAcc());
        vel = object[i].getVel();
        
        // hit or not
        GLfloat sze = object[i].getSize();
        if (pos.getX() > WindowWidth - sze || pos.getX() < -WindowWidth + sze) {
            ranGen();
        }
        if (pos.getY() > WindowHeight - sze || pos.getY() < -WindowHeight + sze) {
            ranGen();
        }
        vel = object[i].getVel();
        // hit
        for (int j = 0; j < MAX_OBJ_NUM; ++j) {
             if (i!=j && object[i].hitTest(object[j])) {
                 ranGen();
            }
        }
        // update position
        object[i].changePos(vel);
        pos = object[i].getPos();
        
        if (pos.getX() > WindowWidth - sze + vel.getX())
            object[i].changePos(vec3(WindowWidth - sze - 1 - pos.getX(), 0, 0));
        else if (pos.getX() < -WindowWidth + sze - vel.getX())
            object[i].changePos(vec3(-WindowWidth + sze - 1 - pos.getX(), 0, 0));
        
        if (pos.getY() > WindowHeight - sze + vel.getY())
            object[i].changePos(vec3(0, WindowHeight - sze - 1 - pos.getY(), 0));
        else if (pos.getY() < -WindowHeight + sze - vel.getY())
            object[i].changePos(vec3(0, -WindowHeight + sze - 1 - pos.getY(), 0));
        pos = object[i].getPos();
        
        //cout << i << ": " << object[i].getPos().len() << endl;
    }
    glutPostRedisplay();
    glutTimerFunc(FRAME_PITCH, TimerFunction, value);
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        beginX = x;
        beginY = y;
        Pause = true;
    } else if (state == GLUT_UP)
        Pause = false;
}

void mouseDrag(int x, int y) {
    rotateX += (x-beginX);
    rotateY += (y-beginY);
    beginX = x;
    beginY = y;
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': case 'A': // left
            --rotateX; break;
        case 'd': case 'D': // right
            ++rotateX; break;
        case 'w': case 'W': // top
            ++rotateY; break;
        case 's': case 'S': // down
            --rotateY; break;
            
        case 'e': case 'E': // +1s
            plus_one_second = true;
    }
}

void specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            --rotateX; break;
        case GLUT_KEY_RIGHT:
            ++rotateX; break;
        case GLUT_KEY_UP:
            ++rotateY; break;
        case GLUT_KEY_DOWN:
            --rotateY; break;
    }
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WindowWidth * 2, WindowHeight * 2);
    glutCreateWindow("Three Body");
    setupRC();
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    srand((unsigned int)time(0));
    //ranGen();
    //Pause = true;
    glutMotionFunc(mouseDrag);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutTimerFunc(FRAME_PITCH, TimerFunction, 1);
    glutMainLoop();
}
