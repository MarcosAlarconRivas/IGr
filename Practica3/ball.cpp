#include "ball.h"

Ball::Ball(V2d center, V2d movement):Circle(center, radius){
    speed = movement.mod();
    direction = movement % 1;
}

void Ball::advance(float t){
    center+= direction*speed*t;
}

