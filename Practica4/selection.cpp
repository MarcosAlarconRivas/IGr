#include "selection.h"
#include <GL/gl.h>

Selection::Selection(V2d centro){
 this->centro = p0 = pf = centro;
}

void Selection::setV0(V2d v0){
  p0= v0;
}

void Selection::setVf(V2d vf){
  pf= vf;
}

void Selection::paint()const{
 glBegin(GL_LINE_LOOP);
    glVertex2f(centro.x,centro.y);
    glVertex2f(p0.x,p0.y);
    glVertex2f(pf.x,pf.y);
 glEnd();
}

