//Marcos Alarcon Rivas

#pragma hdrstop

#include "ArbolPitagoras.h"
#include <cmath>

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
void ArbolPitagoras::grow(bool randomBranching){
    vector<Cuadrado> growingLvl= back();
    push_back(vector<Cuadrado>());
    for(vector<Cuadrado>::iterator i= growingLvl.begin(); i!= growingLvl.end(); i++){
       auto_ptr<Cuadrado> c1, c2;
       branch(randomBranching, *i, c1, c2);
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
void ArbolPitagoras::branch(bool randBranch, const Cuadrado& parent, auto_ptr<Cuadrado>& son1, auto_ptr<Cuadrado>& son2){
     //p1 y p2 son los vertices que se van a extender
     GLfloat p1[2]= {parent.getx(3), parent.gety(3)};
     GLfloat p2[2]= {parent.getx(2), parent.gety(2)};

     //m es el punto medio entre p1 y p2
     GLfloat m[2], n[2];
     m[0]=(p1[0]+p2[0])/2;
     m[1]=(p1[1]+p2[1])/2;

     //n es el nuevo punto que compartrán los dos hijos
     n[0] = m[0]-(p2[1]-m[1]);
     n[1] = m[1]+(p2[0]-m[0]);

     //si es aleatoria, muevo el punto n con centro en m
     if(randBranch)
        divert(m,n);

     //ahora que tengo los lados inferiores, ya puedo construir los hijos
     son1.reset( new Cuadrado(n[0], n[1], p2[0], p2[1]) );
     son2.reset( new Cuadrado(p1[0], p1[1], n[0], n[1]) );
}
//---------------------------------------------------------------------------
void ArbolPitagoras::divert(const float (&o)[2], float (&p)[2]){
   float k = 2.0f * rand() / RAND_MAX - 1.0f; //k= random[-1,1]
   k= k<0 ? -k*k : k*k; // k^2

   float op[2]= {p[0]-o[0], p[1]-o[1]};
   float r[2]= {op[0]+(op[1]*k), op[1]+(-op[0]*k)};

   float correction = sqrt((op[0]*op[0]+op[1]*op[1]) / (r[0]*r[0]+ r[1]*r[1]));

   r[0]*= correction;
   r[1]*= correction;

   p[0]= o[0]+r[0];
   p[1]= o[1]+r[1];

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

