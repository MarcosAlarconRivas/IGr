#include "ball.h"
#include <GL/gl.h>

void Ball::advance(float t){
    center+= direction*speed*t;
}

bool Ball::hit(const Obstacle &toHit, double& tIn, V2d& normalIn){
    return toHit.intersection(center, direction, speed, tIn, normalIn);
}

void Ball::revota(V2d normal){
 //normal %= 1;
 normal = normal * -(normal * direction);
 direction += (normal*2)% 1;
}

void Ball::inv_mov(){
  direction.x = -direction.x;
  direction.y = -direction.y;
}

void Ball::paint(){
    glPushMatrix();
    glTranslatef(center.x, center.y, 0);
    glScalef(radius, radius, 1);
    glBegin(GL_LINE_LOOP);
        Circle::circle_vertex();
    glEnd();
    //glRotatef(rotation, 0, 0, 1);
    glBegin(GL_LINE);
        glVertex2f(center.x,center.y);
        glVertex2(center.x+1,center.y);
    glPopMatrix();
}

