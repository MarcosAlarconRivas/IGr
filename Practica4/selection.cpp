#include "selection.h"
#include <GL/gl.h>
#include <cmath>

Selection::Selection(V2d c){
 centro = p0 = pf = c;
 seted=0;
}

void Selection::setV0(V2d v0){
  p0= pf= v0;
  seted=1;
}

void Selection::setVf(V2d vf){
  pf= vf;
}

void Selection::paint()const{
 glBegin(GL_LINES);
    glVertex2f(centro.x,centro.y);
    glVertex2f(p0.x,p0.y);
    glVertex2f(centro.x,centro.y);
    glVertex2f(pf.x,pf.y);
 glEnd();
 if(!seted)return;
 glBegin(GL_LINE_LOOP);
     float theta = 2 * M_PI / 50;
     //precalculate the sine and cosine
     float c = cos(theta), s = sin(theta);
     float t;
     //we start at angle = 0
     float x =(centro-pf).mod(), y = 0;
     for(unsigned i=0; i<50; i++){
         glVertex2f(centro.x+x,centro.y+y);
         //apply the rotation matrix
         t = x;
         x = c * x - s * y;
         y = s * t + c * y;
     }
 glEnd();
}

