#include "circle.h"
#include <cmath>
#include <GL/gl.h>

Circle::Circle(V2d center, float radius){
    this->center= center; this->radius= radius;
}

void Circle::paint()const{
    glPushMatrix();
    glTranslatef(center.x, center.y, 0);
    //glScalef(raduis, radius, 1);
    glBegin(GL_POLYGON);
        circle_vertex(radius);
    glEnd();
    glPopMatrix();
}

bool Circle::intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const{

    //descartar los lejanos
    //NO TIENE EN CUENTA EL RADIO DE LA PELOTA, HAY QUE SUMARLO
    V2d c_p= p -center;
    double lng= radius + s/* + pelota.r */;
    if( c_p.mod2()> lng*lng)return false;

    V2d v = d *s;
    //(v·v)t2 +2(c_p·v)t + c_p·c_p -r2= 0
    double a = v*v;
    double b = c_p*v*2;
    double c = c_p*c_p - radius*radius;
    double det = b*b-4*a*c;

    if(det < - zero) return false;
    if(det >   zero) {
      double t1, t2;
      t1 = ( -b -std::sqrt(det) ) / (2*a);
      t2 = ( -b +std::sqrt(det) ) / (2*a);
      tIn =(t1<t2)?t1:t2;
    }
    else tIn = (-b) / (2*a);

    normalIn = ((p + v*tIn) - center)%1;

    return true;
}

void Circle::circle_vertex(float radius, unsigned numVertex){
    float theta = 2 * M_PI / numVertex;
    //precalculate the sine and cosine
    float c = cos(theta), s = sin(theta);
    float t;
    //we start at angle = 0
    float x = radius, y = 0;
    for(unsigned i=0; i<numVertex; i++){
        glVertex2f(x,y);
        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
}
