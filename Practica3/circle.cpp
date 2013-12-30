#include "circle.h"
#include <cmath>
#include <GL/gl.h>

Circle::Circle(V2d center, float radius){
    this->center= center; this->radius= radius;
}

void Circle::paint()const{
    glMatrixMode(GL_MODELVIEW);
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

V2d Circle::find_center(V2d v0, V2d v1, V2d v2){
    V2d l= v0|v1;
    V2d m= ++(v1-l);
    double k;
    // dist(v0, (l+m*k)) == dist(v2, (l+m*k))
    // ===>
    //[v0.x-(l.x+m.x*k)]² + [v0.y-(l.y+m.y*k)]² - [v2.x-(l.x+m.x*k)]² - [v2.y-(l.y+m.y*k)]² = 0
    // ===>
    // (m.x²)k² +(2*m.x*(l.x-v0.x))k + (v0.x-l.x)² +
    // (m.y²)k² +(2*m.y*(l.y-v0.y))k + (v0.y-l.y)² +
    //-(m.x²)k² -(2*m.x*(l.x-v2.x))k - (v2.x-l.x)² +
    //-(m.y²)k² -(2*m.y*(l.y-v2.y))k - (v2.y-l.y)² = 0
    // ===>
    // 0*k² + 2*(m.x*[(l.x-v0.x)-(l.x-v2.x)] +m.y[(l.y-v0.y)-(l.y-v2.y)])*k =
    // (v2.x-l.x)²-(v0.x-l.x)²+(v2.y-l.y)²-(v0.y-l.y)²
    // ===>
    // k= [(v2.x-l.x)²-(v0.x-l.x)²+(v2.y-l.y)²-(v0.y-l.y)²]/( 2*(m.x*[(l.x-v0.x)-(l.x-v2.x)]+m.y[(l.y-v0.y)-(l.y-v2.y)]) )

    double div= 2*(m.x*((l.x-v0.x)-(l.x-v2.x)) + m.y*((l.y-v0.y)-(l.y-v2.y)));

    if(!div)return V2d((v0.x+v1.x+v2.x)/3, (v0.y+v1.y+v2.y)/3);

    k= ((v2.x-l.x)*(v2.x-l.x) -(v0.x-l.x)*(v0.x-l.x) +(v2.y-l.y)*(v2.y-l.y) -(v0.y-l.y)*(v0.y-l.y)) / div;

    return l + (m*k);
}
