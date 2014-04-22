#ifndef CUBOID_H
#define CUBOID_H
#include "flatmesh.h"
#include "GL/glu.h"

class Cuboid: public FlatMesh{
protected:
    float color[4]={1,1,1,1};
public:
    Cuboid(double width=1, double height=1, double depth=1, unsigned xdiv=0, unsigned ydiv=0, unsigned zdiv=0);

    Cuboid* setColor(float r, float g, float b, float a=1);
    Cuboid* setColor(float color[3],float alpha=1);

    inline void paint(bool fill)const{
        glColor4fv(color);
        FlatMesh::paint(fill);
    }
};

#endif // CUBOID_H
