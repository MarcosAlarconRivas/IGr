#include "ball.h"
#include <GL/gl.h>

Ball::Ball(V2d center, V2d movement):Circle(center, radius){
    speed = movement.mod();
    direction = movement % 1;
    phase = rotation = 0;
}
void Ball::advance(float t){
    center+= direction*speed*t;
    phase += rotation ? rot_speed : -rot_speed;
}

bool Ball::hit(const Obstacle &toHit, double& tIn, V2d& normalIn){
    return toHit.intersection(center, direction, speed, tIn, normalIn);
}

void Ball::revota(V2d normal){
 //normal %= 1;
 normal = normal * -(normal * direction);
 direction += (normal*2);//% 1;
 phase += rotation ? rot_speed : -rot_speed;
}

void Ball::inv_mov(){
  direction.x = -direction.x;
  direction.y = -direction.y;
  phase += rotation ? rot_speed : -rot_speed;
}

void Ball::paint()const{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(center.x, center.y, 0);
    glScalef(radius, radius, 1);
    glBegin(GL_LINE_LOOP);
        Circle::circle_vertex();
    glEnd();
    glRotatef(phase, 0, 0, 1);
    glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(0,1);
    glEnd();
    glPopMatrix();
}

