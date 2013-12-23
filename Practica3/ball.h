#ifndef BALL_H
#define BALL_H

#include "circle.h"
#include "v2d.h"

class Ball: public Circle{
protected:
      V2d direction;
      float speed;
public:
    static const double radius= 10;

    Ball(V2d center, V2d movement);
    void advance(float how);
    inline V2d p(){return center;}
    inline V2d d(){return direction;}
    inline V2d m(){return direction*speed;}
    inline float s(){return speed;}
};

#endif // BALL_H
