#include "disk.h"

Disk::Disk(double i, double o, unsigned s, unsigned l){
   inR=i; outR=o; slices=s; loops=l;  quad=gluNewQuadric();
}

Disk::~Disk(){
    gluDeleteQuadric(quad);
}

void Disk::paint(bool f)const{
    glShadeModel(GL_FLAT);
    glColor4fv(color);
    gluQuadricDrawStyle(quad, f?GLU_FILL:GLU_LINE);
    gluDisk(quad, inR, outR, slices, loops);
}

Disk* Disk::setColor(float r, float g, float b, float a){
    color[0]=r;
    color[1]=g;
    color[2]=b;
    color[3]=a;
    return this;
}
