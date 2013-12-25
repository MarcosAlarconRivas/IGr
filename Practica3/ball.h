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
    static constexpr double radius= 10;

    Ball(V2d center, V2d movement);

    bool hit(const Obstacle &toHit, double& tIn, V2d& normalIn);
    void advance(float how=1);
    void revota(V2d normal);
    void inv_mov();

    inline V2d p(){return center;}
    inline V2d d(){return direction;}
    inline V2d m(){return direction*speed;}
    inline float s(){return speed;}
    virtual void paint()const;

};

#endif // BALL_H
