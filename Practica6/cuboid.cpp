#include "cuboid.h"

Cuboid::Cuboid(double width, double height, double depth,
               float r, float g, float b, float a){
    x=width; y=height; z=depth;
    color[0]=r;
    color[1]=g;
    color[2]=b;
    color[3]=a;
}

Cuboid::Cuboid(double w, double h, double d, float *c){
    x=w; y=h; z=d;
    color[0]=c[0];
    color[1]=c[1];
    color[2]=c[2];
    if(sizeof(c) > sizeof(float)*3)
        color[3]=c[3];
}

void Cuboid::paint(bool fill)const{
    glShadeModel(GL_FLAT);
    glColor4fv(color);
    glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
        glNormal3f(0,0,-1);
        glVertex3d(0,0,0);
        glVertex3d(0,y,0);
        glVertex3d(x,y,0);
        glVertex3d(x,0,0);
    glEnd();
    glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
        glNormal3f(0,0,1);
        glVertex3d(0,0,z);
        glVertex3d(x,0,z);
        glVertex3d(x,y,z);
        glVertex3d(0,y,z);
    glEnd();

    glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
        glNormal3f(-1,0,0);
        glVertex3d(0,0,0);
        glVertex3d(0,0,z);
        glVertex3d(0,y,z);
        glVertex3d(0,y,0);
    glEnd();
    glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
        glNormal3f(1,0,0);
        glVertex3d(x,0,0);
        glVertex3d(x,y,0);
        glVertex3d(x,y,z);
        glVertex3d(x,0,z);
    glEnd();

    glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
        glNormal3f(0,-1,0);
        glVertex3d(0,0,0);
        glVertex3d(x,0,0);
        glVertex3d(x,0,z);
        glVertex3d(0,0,z);
    glEnd();
    glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
        glNormal3f(0,1,0);
        glVertex3d(0,y,0);
        glVertex3d(0,y,z);
        glVertex3d(x,y,z);
        glVertex3d(x,y,0);
    glEnd();
}
