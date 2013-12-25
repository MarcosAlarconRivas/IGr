#include "triangle.h"
#include <GL/gl.h>
#include <cmath>
#include <circle.h>

Triangle::Triangle(V2d v0, V2d v1, V2d v2){
       vertex[0]= v0;
       vertex[1]= v1;
       vertex[2]= v2;

       norm[0]= ++(v1-v0)%1;
       norm[1]= ++(v2-v1)%1;
       norm[2]= ++(v0-v2)%1;

       centro= Circle::find_center(v0,v1,v2);
       radio= (v0 - centro).mod();
}

void Triangle::paint()const {
    glBegin(GL_TRIANGLES);
    for(int i=0;i<3;i++)
        glVertex2f(vertex[i].x, vertex[i].y);
    glEnd();
}

bool Triangle::intersection(V2d p, V2d v, float speed, double& tIn, V2d& normalIn)const {

    //descartar los lejanos
    if((p -centro).mod2() > (radio+speed)*(radio+speed))return 0;

   //Compute the vectors dist, proj and sign;
   float proj[3], dist[3]; short sign[3];
   V2d vT = ++V2d(v);
   for(int i=0; i<3; i++){
      V2d p_pi = V2d((vertex[i]- p));
      proj[i]= p_pi * v;
      dist[i]= p_pi * vT;
      sign[i]= dist[i]>0?1:dist[i]?-1:0;
      //sign[i]= dist[i]>=(-zero)?(dist[i]<zero?0:1):-1;
   }

  if(std::abs(sign[0]+sign[1]+sign[2])==3) return 0;//Trivial failure
  int nHits= 0; double hit[3]; V2d n[3]; //For recording tHits and normals

  for(int i=0; i<3; i++){ //Intersections edge-line
      int j=(i+1)%3;
      if(sign[i]*sign[j] < 0){
        hit[nHits] = (proj[i]*dist[j]-dist[i]*proj[j])/(dist[j]-dist[i]);
        n[nHits]= norm[i];
        nHits++;
     }
  }

  if(nHits<2)  //Intersections vertex-line
  for(int i=0; i<3; i++){
    if(sign[i])continue;
    hit[nHits]= proj[i];
    n[nHits]= bisectriz(i);
    nHits++;
  }

  int m= hit[0]<hit[1]&&hit[0]<hit[2]? 0: hit[1]<hit[2] ? 1: 2;
  tIn= hit[m]/speed;
  normalIn= n[m];
  return (tIn <=1 );
}

