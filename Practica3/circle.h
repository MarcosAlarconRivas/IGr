#ifndef CIRCLE_H
#define CIRCLE_H

#include "v2d.h"
#include "obstacle.h"

class Circle : public Obstacle{
protected:
     float radius;
     V2d center;
public:
    Circle(V2d center, float radius);
    virtual void paint()const;
    virtual bool intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const;

    static void circle_vertex(float radius=1, unsigned numVertex=50);
    //paints glVertex for a circle in (0,0)

    static V2d find_center(V2d p1, V2d p2, V2d p3);
    //finds the center for a circunference that containis 3 points

};

#endif // CIRCLE_H
