#ifndef DISK_H
#define DISK_H
#include "solid.h"
#include "GL/glu.h"

class Disk : public Solid{
protected:
    double inR, outR;
    unsigned slices, loops;
    float color[4]={1,1,1,1};
    GLUquadric* quad;
public:
    Disk(double inner, double outer, unsigned slices=15, unsigned loops=15);
    Disk(double raduis):Disk(0, raduis){}
   ~Disk();

    void paint(bool fill)const;
    Disk* setColor(float r, float g, float b, float a=1);
};

#endif // DISC_H
