//Marcos Alarcon Rivas
#pragma hdrstop

#include "Triangle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Triangle::Triangle(Vector v0, Vector v1, Vector v2):Obstacle(3){
       vertex[0]= v0;
       vertex[1]= v1;
       vertex[2]= v2;

       norm[0]= ++(v1-v0).unitario();
       norm[1]= ++(v2-v1).unitario();
       norm[2]= ++(v0-v2).unitario();

       centro= Vector((v0.x+v1.x+v2.x)/3, (v0.y+v1.y+v2.y)/3);
       radio= (v0 - centro).mod();
}
//---------------------------------------------------------------------------
void Triangle::paint()const {
    glBegin(GL_TRIANGLES);
    for(int i=0;i<3;i++)
        glVertex2f(vertex[i].x, vertex[i].y);
    glEnd();
}
//---------------------------------------------------------------------------
bool Triangle::intersection(/*Input*/ Vector p, Vector v, float speed,
/*Output*/ double& tIn, Vector& normalIn)const {

    //descartar los lejanos
    //NO TIENE EN CUENTA EL RADIO DE LA PELOTA, HAY QUE SUMARLO
    if((p -centro).mod2() > (radio+speed)*(radio+speed))return 0;

   //Compute the vectors dist, proj and sign;
   float proj[3], dist[3]; short sign[3];
   Vector vT = ++Vector(v);
   for(int i=0; i<3; i++){
      Vector p_pi = Vector((vertex[i]- p));
      proj[i]= p_pi * v;
      dist[i]= p_pi * vT;
      sign[i]= dist[i]>0?1:dist[i]?-1:0;
      //sign[i]= dist[i]>=(-zero)?(dist[i]<zero?0:1):-1;
   }

  if(abs(sign[0]+sign[1]+sign[2])==3) return false;//Trivial failure
  int nHits= 0; double hit[3]; Vector n[3]; //For recording tHits and normals

  for(int i=0; i<3; i++){ //Intersections edge-line
      int j=(i+1)%3;
      if(sign[i]*sign[j] < 0){
        hit[nHits] = (proj[i]*dist[j]-dist[i]*proj[j])/(dist[j]-dist[i]);
        n[nHits]= norm[i];
        nHits++;
     }
  }
  //if(!nHits) return 0;
  if(nHits<2)  //Intersections vertex-line
  for(int i=0; i<3; i++){
    if(sign[i])continue;
    hit[nHits]= proj[i];
    n[nHits]= bisectriz(i);
    nHits++;
  }

  int m= min(hit, nHits); //index of the minimum value inside vector hit; 
  tIn= hit[m]/speed;
  normalIn= n[m];
  return (tIn <=1 );
}
//---------------------------------------------------------------------------
int Triangle::min(double vect[], int leng){
        double m = vect[0];
        int idx=0;
        for(int i=1;i<leng;i++)
            if(vect[i] < m){
              m= vect[i];
              idx=i;
            }
        return idx;
}
//---------------------------------------------------------------------------

