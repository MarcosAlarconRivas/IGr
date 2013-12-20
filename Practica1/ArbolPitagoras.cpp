//Marcos Alarcon Rivas

#pragma hdrstop

#include "ArbolPitagoras.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

const GLfloat ArbolPitagoras::colR[]={0.5,0.12,0};
const GLfloat ArbolPitagoras::colH[]={0,0.8,0};

ArbolPitagoras::ArbolPitagoras(Cuadrado root){
   vector<Cuadrado> rootLvl;
   rootLvl.push_back(root);
   push_back(rootLvl);
   unselect();
}
//---------------------------------------------------------------------------
/*ArbolPitagoras::~ArbolPitagoras(){
  //heredado de vector<>
}*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ArbolPitagoras::paint(){
  int nivel=0;
  vector< vector<Cuadrado> >::iterator deep;
  vector<Cuadrado>::iterator cuad;
  for (deep = begin(); deep != end(); deep++){
    glColor3fv( levelColor(++nivel) );
    for (cuad = deep->begin(); cuad != deep->end(); cuad++)
        cuad->paint();
    }

  if(selected){
    glColor3f(0,1,1);
    selected->paint();
  }
}
//---------------------------------------------------------------------------
void ArbolPitagoras::prune(){
    if(deep()<2)return;
    back().clear();
    pop_back();
    
    if(deep()<selected_lvl)unselect();
}
//---------------------------------------------------------------------------
void ArbolPitagoras::grow(){
    vector<Cuadrado> growingLvl= back();
    push_back(vector<Cuadrado>());
    for(vector<Cuadrado>::iterator i= growingLvl.begin(); i!= growingLvl.end(); i++){
       auto_ptr<Cuadrado> c1, c2;
       branch(*i, c1, c2);
       back().push_back(*c1);
       back().push_back(*c2);
       //delete c1, c2;
    }
}
//---------------------------------------------------------------------------
void ArbolPitagoras::select(GLfloat x, GLfloat y){
  unselect();
  int nivel=0;
  vector< vector<Cuadrado> >::iterator deep;
  vector<Cuadrado>::iterator cuad;
  for (deep = begin(); deep != end(); deep++){
    nivel++;
    for (cuad = deep->begin(); cuad != deep->end(); cuad++)
        if(cuad->contain(x,y)){
          selected= &*cuad;
          selected_lvl=nivel;
          break;
        }
    }
}
//---------------------------------------------------------------------------
void ArbolPitagoras::unselect(){
        selected=0;
        selected_lvl=0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ArbolPitagoras::branch(const Cuadrado& parent, auto_ptr<Cuadrado>& son1, auto_ptr<Cuadrado>& son2){
     //p1 y p2 son los vertices que se van a extender
     GLfloat p1[2]= {parent.getx(3), parent.gety(3)};
     GLfloat p2[2]= {parent.getx(2), parent.gety(2)};

     //m es el punto medio entre p1 y p2
     GLfloat m[2];
     m[0]=(p1[0]+p2[0])/2;
     m[1]=(p1[1]+p2[1])/2;

     //ahora lo transformo en el nuevo punto que compartrán los dos hijos
     GLfloat x= p2[0]-m[0];
     GLfloat y= p2[1]-m[1];
     m[0] -= y;
     m[1] += x;

     //ahora que tengo los lados inferiores, ya puedo construir los hijos
     son1.reset( new Cuadrado(m[0], m[1], p2[0], p2[1]) );
     son2.reset( new Cuadrado(p1[0], p1[1], m[0], m[1]) );
}
//---------------------------------------------------------------------------
const GLfloat* ArbolPitagoras::levelColor(unsigned int level){
 if(level==1) return colR;
 if(level==deep()) return colH;

 float dR= colH[0]-colR[0];
 float dG= colH[1]-colR[1];
 float dB= colH[2]-colR[2];
 float r= (level-1.0)/(deep()-1);

 static GLfloat col[3];
 col[0] =colR[0]+dR*r;
 col[1] =colR[1]+dG*r;
 col[2] =colR[2]+dB*r;
 return col;
}
//---------------------------------------------------------------------------

