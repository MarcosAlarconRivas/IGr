//Marcos Alarcon Rivas

#pragma hdrstop

#include "Selection.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Selection::Selection(Vector centro): Ball(Vector(0,0), centro)
{
 p0=p1=p2 = centro;
}
//---------------------------------------------------------------------------
void Selection::setV(Vector flecha, float ratio){
  p0= flecha;
  movement= (flecha-center)*ratio;
  speed= movement.mod();
  direction= movement % 1;
  flecha = direction*radius;
  ++flecha;
  p1= center+ flecha;
  p2= center- flecha;
}
//---------------------------------------------------------------------------
void Selection::paint()const{
 Ball::paint();
 glBegin(GL_LINE_LOOP);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x,p2.y);
    glVertex2f(p0.x,p0.y);
 glEnd();

}
//---------------------------------------------------------------------------
