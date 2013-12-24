#ifndef BALL_H
#define BALL_H

#include "circle.h"
#include "v2d.h"
#include "obstacle.h"

class Ball: public Circle{
protected:
      V2d direction;
      float speed;
public:
    static const double radius= 10;

    void advance(float how);
    bool hit(const Obstacle &toHit, double& tIn, V2d& normalIn);
    inline V2d p(){return center;}
    inline V2d d(){return direction;}
    inline V2d m(){return direction*speed;}
    inline float s(){return speed;}
    virtual void paint()const;

    Ball(V2d center, V2d movement):Circle(center, radius){
        speed = movement.mod();
        direction = movement % 1;
    }
};

#endif // BALL_H
