#include "pitagorast.h"
#include <GL/gl.h>

const float PitagorasT::colR[]={0.5,0.12,0};
const float PitagorasT::colH[]={0,0.8,0};

PitagorasT::PitagorasT(float x0, float y0, float x1, float y1){
    vector<cuadrado> rootLvl;
    rootLvl.push_back(*new_cuadrado(x0, y0, x1, y1));
    push_back(rootLvl);
}

void PitagorasT::paint() const{
    int nivel=0;
    //vector< vector<cuadrado> >::iterator deep;
    //vector<cuadrado>::iterator cuad;
    for (auto deep = begin(); deep != end(); deep++){
      glColor3fv( levelColor(++nivel) );
      for (auto cuad = deep->begin(); cuad != deep->end(); cuad++){
          glBegin(GL_QUADS);
          for(int i=0;i<4;i++)
              glVertex2f(cuad->x[i],cuad->y[i]);
          glEnd();
      }
    }
}

void PitagorasT::grow(unsigned levels){
    for(unsigned i=0;i<levels; i++){
        vector<cuadrado> growingLvl= back();
        push_back(vector<cuadrado>());
        for(vector<cuadrado>::iterator i= growingLvl.begin(); i!= growingLvl.end(); i++){
           cuadrado *c1=0, *c2=0;
           branch(*i, c1, c2);
           back().push_back(*c1);
           back().push_back(*c2);
        }
    }
}

void PitagorasT::branch(const cuadrado& p, cuadrado*&s1, cuadrado*&s2){
    GLfloat p1[2]= {p.x[3], p.y[3]};
    GLfloat p2[2]= {p.x[2], p.y[2]};

    GLfloat m[2], n[2];
    m[0]=(p1[0]+p2[0])/2;
    m[1]=(p1[1]+p2[1])/2;
    n[0] = m[0]-(p2[1]-m[1]);
    n[1] = m[1]+(p2[0]-m[0]);

    //delete s1, s2;
    s1 = new_cuadrado(n[0], n[1], p2[0], p2[1]);
    s2 = new_cuadrado(p1[0], p1[1], n[0], n[1]);
}

float* PitagorasT::levelColor(unsigned int level)const{
    if(level==1) return (float*)colR;
    if(level==size()) return (float*)colH;

    float dR= colH[0]-colR[0];
    float dG= colH[1]-colR[1];
    float dB= colH[2]-colR[2];
    float r= (level-1.0)/(size()-1);

    static float col[3];
    col[0] =colR[0]+dR*r;
    col[1] =colR[1]+dG*r;
    col[2] =colR[2]+dB*r;
    return col;
}

cuadrado* PitagorasT::new_cuadrado(float x0, float y0, float x1, float y1){
    cuadrado* c = new cuadrado;
      c->x[0]= x0;
      c->y[0]= y0;
      c->x[1]= x1;
      c->y[1]= y1;

      float dx = x1-x0;
      float dy = y1-y0;

      c->x[2]=x1-dy;
      c->y[2]=y1+dx;
      c->x[3]=x0-dy;
      c->y[3]=y0+dx;
      return c;
}

