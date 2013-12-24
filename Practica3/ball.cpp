#include "ball.h"

void Ball::advance(float t){
    center+= direction*speed*t;
}

bool Ball::hit(const Obstacle &toHit, double& tIn, V2d& normalIn){
    return toHit.intersection(center, direction, speed, tIn, normalIn);
}

