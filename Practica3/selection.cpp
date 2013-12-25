#include "selection.h"
#include <GL/gl.h>

Selection::Selection(V2d centro):Ball(centro, V2d(0,0)) {
 p0=p1=p2 = centro;
}

void Selection::setV(V2d flecha, float ratio){
  p0= flecha;
  V2d movement= (flecha-center)*ratio;
  speed= movement.mod();
  direction= movement % 1;
  flecha = direction*radius;
  ++flecha;
  p1= center+ flecha;
  p2= center- flecha;
}

void Selection::paint()const{
 Circle::paint();
 glBegin(GL_LINE_LOOP);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x,p2.y);
    glVertex2f(p0.x,p0.y);
 glEnd();
}

