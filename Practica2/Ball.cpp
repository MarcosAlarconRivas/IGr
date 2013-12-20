//Marcos Alarcon Rivas
#pragma hdrstop
#include <math.h>
#include "Ball.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Ball::Ball(Vector v, Vector center, float radius, unsigned int nVert):
Polygon(nVert){
    //Circle constructor
        float theta = 2 * M_PI / nVert;
	float c = cos(theta), s = sin(theta);//precalculate the sine and cosine
	float t;
	float x = radius, y = 0;//we start at angle = 0
	for(unsigned int i=0; i<nVert; i++){
                vertex[i]=Vector(x, y);

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}

        this->radius=radius;
        this->center= Vector(0,0);
        move(center);
   //end of Circle constructor

        movement=v;
        speed= v.mod();
        direction= v.unitario();
}
//---------------------------------------------------------------------------
void Ball::paint()const {
int num_segments= nVertex();
 glBegin(GL_LINE_LOOP);
 for(int i=0; i<num_segments; i++)
        glVertex2f(vertex[i].x, vertex[i].y);
 glEnd();
}
//---------------------------------------------------------------------------
void Ball::revota(Vector normal){
 //normal %= 1;
 normal = normal * -(normal * movement);
 movement += (normal*2);
 direction = movement.unitario();
}
//---------------------------------------------------------------------------
void Ball::avanza(float recorrido){//recorrodo € (0,1]
  move(movement*recorrido);
}
//---------------------------------------------------------------------------
void Ball::inv_mov(){
  direction.x = -direction.x;
  direction.y = -direction.y;
  movement.x = -movement.x;
  movement.y = -movement.y;
}
//---------------------------------------------------------------------------
