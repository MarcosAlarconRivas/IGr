#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "v2d.h"

class Obstacle{
public:
    virtual void paint()const =0;
    virtual bool intersection(V2d p, V2d d, float s,  double& tIn, V2d& normalIn)const =0;
};

#endif // OBSTACLE_H
