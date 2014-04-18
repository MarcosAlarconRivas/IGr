#ifndef SPHERE_H
#define SPHERE_H
#include "model.h"
#include "GL/glu.h"
class Sphere : public Model{
protected:
    double radius;
    unsigned slices, stacks;
    GLUquadric* quad;
    float color[4]={1,1,1,0};

public:
    Sphere(double radius, unsigned slices, unsigned stacks, float *color=0);
    Sphere(double radius=1, unsigned slices=30, unsigned stacks=30,
           float r=1, float g=1, float b=1, float a=0);
   ~Sphere();

    void paint(bool fill)const;

};

#endif // SPHERE_H
