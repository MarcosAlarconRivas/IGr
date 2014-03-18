#ifndef EXTRUSION_H
#define EXTRUSION_H
#include "mesh.h"
#include <math.h>

typedef struct{float x; float y;} v2d;

class Extrusion : public Mesh{
public:
    Extrusion(unsigned raduis, unsigned sides, V3D t0, V3D tf);
    Extrusion(vector<v2d> cut, V3D t0, V3D tf);
    Extrusion(vector<v2d> cut, V3D(*curve)(double), unsigned numOfCuts, double from=0, double to=2*M_PI);
    Extrusion(unsigned raduis, unsigned sides, V3D(*curve)(double), unsigned numOfCuts, double from=0, double to=2*M_PI);
};

#endif // EXTRUSION_H
