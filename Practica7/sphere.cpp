#include "sphere.h"

Sphere::Sphere(double rd,unsigned sl,unsigned st,float r,float g,float b,float a){
    quad= gluNewQuadric();
    radius=rd;
    slices=sl;
    stacks=st;
    setColor(r,g,b,a);
}

Sphere::Sphere(double rd, unsigned sl, unsigned st, float c[3], float a)
    :Sphere(rd, sl, st, c[0], c[1], c[2], a){}

Sphere::~Sphere(){
    gluDeleteQuadric(quad);
}

void Sphere::paint(bool f)const{
    glShadeModel(GL_SMOOTH);
    glColor4fv(color);
    gluQuadricDrawStyle(quad, f?GLU_FILL:GLU_LINE);
    if(f && texture){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    gluSphere(quad, radius, slices, stacks);
    glDisable(GL_TEXTURE_2D);
}

Sphere* Sphere::setColor(float r, float g, float b, float a){
    color[0]=r;
    color[1]=g;
    color[2]=b;
    color[3]=a;
    return this;
}

Sphere* Sphere::setTexture(GLuint tex){
    texture=tex;
    if(tex)gluQuadricTexture(quad, GL_TRUE);
    else gluQuadricTexture(quad, GL_FALSE);
    return this;
}
