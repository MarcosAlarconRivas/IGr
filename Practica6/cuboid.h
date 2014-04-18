#ifndef CUBOID_H
#define CUBOID_H
#include "model.h"
#include "GL/glu.h"

class Cuboid: public Model{
protected:
    float color[4]={1,1,1,0};
    double x=1, y=1, z=1;
public:
    Cuboid(){}
    Cuboid(double width, double height, double depth, float r=1, float g=1, float b=1, float a=1);
    Cuboid(double width, double height, double depth, float color[4]);

    void paint(bool fill=1)const;
};

#endif // CUBOID_H
