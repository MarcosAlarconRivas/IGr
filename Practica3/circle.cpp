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

V2d Circle::find_center(V2d A, V2d B, V2d C){
//code from: http://stackoverflow.com/questions/4103405
    float yDelta_a = B.y - A.y;
    float xDelta_a = B.x - A.x;
    float yDelta_b = C.y - B.y;
    float xDelta_b = C.x - B.x;
    V2d center = V2d(0,0);
    float aSlope = yDelta_a/xDelta_a;
    float bSlope = yDelta_b/xDelta_b;

    V2d AB_Mid = V2d((A.x+B.x)/2, (A.y+B.y)/2);
    V2d BC_Mid = V2d((B.x+C.x)/2, (B.y+C.y)/2);

    if(!yDelta_a){
        center.x = AB_Mid.x;
        if (!xDelta_b)center.y = BC_Mid.y;
        else center.y = BC_Mid.y + (BC_Mid.x-center.x)/bSlope;
    }else if (!yDelta_b){
        center.x = BC_Mid.x;
        if (!xDelta_a) center.y = AB_Mid.y;
        else center.y = AB_Mid.y + (AB_Mid.x-center.x)/aSlope;
    }else if (!xDelta_a) {
        center.y = AB_Mid.y;
        center.x = bSlope*(BC_Mid.y-center.y) + BC_Mid.x;
    }else if (!xDelta_b){
        center.y = BC_Mid.y;
        center.x = aSlope*(AB_Mid.y-center.y) + AB_Mid.x;
    }else{
        center.x = (aSlope*bSlope*(AB_Mid.y-BC_Mid.y) - aSlope*BC_Mid.x + bSlope*AB_Mid.x)/(bSlope-aSlope);
        center.y = AB_Mid.y - (center.x - AB_Mid.x)/aSlope;
    }

    return center;
}
