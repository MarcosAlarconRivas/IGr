#ifndef CONE_H
#define CONE_H
#include "model.h"
#include "GL/glu.h"

class Cone : public Model{
protected:
    double base, top, height;
    unsigned slices, stacks;
    float color[4]={1,1,1,1};
    GLUquadric* quad;
public:
    Cone(double base, double top, double height, unsigned slices=10, unsigned stacks=10);
   ~Cone();

    void paint(bool fill)const;
    Cone* setColor(float r, float g, float b, float a=1);
};

#endif // CONE_H
