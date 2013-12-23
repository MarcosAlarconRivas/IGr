#ifndef CIRCLE_H
#define CIRCLE_H

#include "v2d.h"
#include "obstacle.h"
#include "ball.h"

class Circle : public Obstacle{
protected:
     float radius;
     V2d center;
public:
    Circle(V2d center, float radius);
    virtual void paint()const;
    virtual bool intersection(Ball& ball, double& tIn, V2d& normalIn)const;

    static void circle_vertex(float radius=1, unsigned numVertex=100);
};

#endif // CIRCLE_H
