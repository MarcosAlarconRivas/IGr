#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "v2d.h"
#include "ball.h"

class Obstacle{
protected:
    Obstacle(){};
public:
    virtual void paint()const =0;
    virtual bool intersection(Ball& ball, double& tIn, V2d& normalIn)const =0;
};

#endif // OBSTACLE_H
