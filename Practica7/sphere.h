#ifndef SPHERE_H
#define SPHERE_H
#include "solid.h"
#include "GL/glu.h"
class Sphere : public Solid{
protected:
    double radius;
    unsigned slices, stacks;
    GLUquadric* quad;
    float color[4];

public:
    Sphere(double radius, unsigned slices, unsigned stacks, float color[3], float alpha=1);
    Sphere(double radius=1, unsigned slices=10, unsigned stacks=10,
           float r=1, float g=1, float b=1, float a=1);
   ~Sphere();

    void paint(bool fill)const;
    Sphere* setColor(float r, float g, float b, float a=1);

};

#endif // SPHERE_H
