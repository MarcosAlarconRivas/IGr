//Marcos Alarcon Rivas

#pragma hdrstop

#include "Selection.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
Selection::Selection(GLfloat cX, GLfloat cY, GLfloat v1X, GLfloat v1Y):
Cuadrado(cX+(v1Y-cY), cY-(v1X-cY), v1X, v1Y)
{
  cx=cX; cy=cY;
}
//---------------------------------------------------------------------------
void Selection::paint()const{

    glBegin(GL_LINE_LOOP);//start primitive
    for(int i=0;i<4;i++)//for each vertex
        glVertex2f(x[i],y[i]);//paint
    glEnd();//end primitive

    glBegin(GL_TRIANGLES);
        glVertex2f(cx,cy);
        glVertex2f(x[1],y[1]);
        glVertex2f(x[0],y[0]);
    glEnd();
}
//---------------------------------------------------------------------------
void Selection::setV1(GLfloat x1, GLfloat y1){
   GLfloat dx=x1-cx, dy=y1-cy;
   x[0]=cx+dy;  y[0]=cy-dx;
   x[1]=x1;     y[1]=y1;
   x[2]=cx-dy;  y[2]=cy+dx;
   x[3]=cx-dx;  y[3]=cy-dy;
}
//---------------------------------------------------------------------------
