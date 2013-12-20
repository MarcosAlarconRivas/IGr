//Marcos Alarcon Rivas

#pragma hdrstop

#include "Cuadrado.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Cuadrado::Cuadrado(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1){
     //input are the position of the square´s "base" 
     /*        3*------*2
                |      |
                |      |
                *------*
                0      1
     */
      x[0]= x0;
      x[1]= x1;
      y[0]= y0;
      y[1]= y1;

      //this is the "base" vector 0-->1
      float dx = x1-x0;
      float dy = y1-y0;

      x[2]=x1-dy;
      y[2]=y1+dx;
      x[3]=x0-dy;
      y[3]=y0+dx;
}
//---------------------------------------------------------------------------
void Cuadrado::paint()const{
    glBegin(GL_QUADS);//start primitive
    for(int i=0;i<4;i++)//for each vertex
        glVertex2f(x[i],y[i]);//paint
    glEnd();//end primitive
}
//---------------------------------------------------------------------------
point* Cuadrado::get(unsigned int vert)const throw(std::bad_alloc){
       //if(vert > 3) throw new std::bad_alloc("Asked for "+vert+"th vertex in a shape of 4.");
       point p = {x[vert], y[vert]};
       point * r= &p;
       return r;
}
//---------------------------------------------------------------------------
bool Cuadrado::contain(GLfloat px, GLfloat py){
//code form http://stackoverflow.com/questions/2752725

  GLfloat x01=x[1]-x[0];
  GLfloat y01=y[1]-y[0];

  if( (px-x[0])*x01+(py-y[0])*y01 <0 )return false;
  if( (px-x[1])*x01+(py-y[1])*y01 >0 )return false;

  GLfloat x03=x[3]-x[0];
  GLfloat y03=y[3]-y[0];

  if( (px-x[0])*x03+(py-y[0])*y03 <0 )return false;
  if( (px-x[3])*x03+(py-y[3])*y03 >0 )return false;

  return true;
}
//---------------------------------------------------------------------------


