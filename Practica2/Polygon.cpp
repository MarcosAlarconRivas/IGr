//Marcos Alarcon Rivas
#pragma hdrstop
#include "Polygon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Polygon::Polygon(unsigned int vertices){
        vertex = new Vector[vertices];
        nVert=vertices;
}
//---------------------------------------------------------------------------
Polygon::~Polygon(){
        delete[] vertex;
}
//---------------------------------------------------------------------------
void Polygon::move(Vector dir){
  for(int i=0; i<nVert; i++)
        vertex[i]+= dir;
}
//---------------------------------------------------------------------------
void Polygon::paint()const {
 glBegin(GL_POLYGON);
 for(int i=0; i<nVert; i++)
        glVertex2f(vertex[i].x, vertex[i].y);
 glEnd();
}
//---------------------------------------------------------------------------
