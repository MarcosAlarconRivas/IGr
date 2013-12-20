//Marcos Alarcon Rivas
#pragma hdrstop
#include <math.h>
#include "Circle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Circle::Circle(Vector center, float radius, unsigned int vertices):
Obstacle(vertices){

        float theta = 2 * M_PI / vertices;
	float c = cos(theta), s = sin(theta);//precalculate the sine and cosine
	float t;
	float x = radius, y = 0;//we start at angle = 0
	for(unsigned int i=0; i<vertices; i++){
                vertex[i]=Vector(x, y);

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}

        this->radius=radius;
        this->center=Vector(0,0);
        move(center);
}
//---------------------------------------------------------------------------
bool Circle::intersection(Vector p, Vector v, float speed,
                double& tIn, Vector& normalIn)const{

    //descartar los lejanos
    //NO TIENE EN CUENTA EL RADIO DE LA PELOTA, HAY QUE SUMARLO
    Vector c_p= p -center;
    double lng= radius+speed/* + pelota.r */;
    if( c_p.mod2()> lng*lng)return false;

    v *= speed;//v estaba unitario
    //(v·v)t2 +2(c_p·v)t + c_p·c_p -r2= 0
    double a = v*v;
    double b = c_p*v*2;
    double c = c_p*c_p - radius*radius;
    double det = b*b-4*a*c;
    
    if(det < -zero) return false;
    if(det > zero) {
      double t1, t2;
      t1 = ( -b -std::sqrt(det) ) / (2*a);
      t2 = ( -b +std::sqrt(det) ) / (2*a);
      tIn =(t1<t2)?t1:t2; 
    }
    else tIn = (-b) / (2*a);

    normalIn = ((p + v*tIn) - center).unitario();
    
    return true;
}
//---------------------------------------------------------------------------

