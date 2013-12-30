#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "circle.h"
#include "v2d.h"
#include <GL/gl.h>

class Ellipse : public Circle{
protected:
    //double width, height, rotation;
    GLdouble transf[16];
public:
    Ellipse(V2d center, double W, double H, double rot=0);
    virtual void paint()const;
    virtual bool intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const;
};

#endif // ELLIPSE_H
