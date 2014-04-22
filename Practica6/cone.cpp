#include "cone.h"

Cone::Cone(double b, double t, double h, unsigned sl, unsigned st){
    base=b; top=t; height=h; slices=sl; stacks=st; quad=gluNewQuadric();
}

Cone::~Cone(){
    gluDeleteQuadric(quad);
}

void Cone::paint(bool f)const{
    glShadeModel(GL_SMOOTH);
    glColor4fv(color);
    gluQuadricDrawStyle(quad, f?GLU_FILL:GLU_LINE);
    gluCylinder(quad, base, top, height, slices, stacks);
}

Cone* Cone::setColor(float r, float g, float b, float a){
    color[0]=r;
    color[1]=g;
    color[2]=b;
    color[3]=a;
    return this;
}
