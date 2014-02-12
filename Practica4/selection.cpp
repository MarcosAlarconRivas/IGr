#include "selection.h"
#include <GL/gl.h>
#include <cmath>

Selection::Selection(V2d c){
 centro = pib= curr = c;
 rad=0;
}

void Selection::setV(V2d v){
  curr= v;
  rad= (centro-curr).mod();
  pib= centro; pib.x += rad;
}

float Selection::angle()const{
    return std::abs(360* atan2(curr.x - pib.x, curr.y - pib.y)/ M_PI);
}

V2d Selection::pibt()const{
    return pib;
}

V2d Selection::cent()const{
    return centro;
}

void Selection::paint()const{
 glBegin(GL_LINES);
    glVertex2f(centro.x,centro.y);
    glVertex2f(pib.x,pib.y);
    glVertex2f(centro.x,centro.y);
    glVertex2f(curr.x,curr.y);
 glEnd();
 if(!rad)return;
 glBegin(GL_LINE_LOOP);
     float theta = 2 * M_PI / 50;
     //precalculate the sine and cosine
     float c = cos(theta), s = sin(theta);
     float t;
     //we start at angle = 0
     float x =rad, y = 0;
     for(unsigned i=0; i<50; i++){
         glVertex2f(centro.x+x,centro.y+y);
         //apply the rotation matrix
         t = x;
         x = c * x - s * y;
         y = s * t + c * y;
     }
 glEnd();
}

