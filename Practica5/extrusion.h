#ifndef EXTRUSION_H
#define EXTRUSION_H
#include "mesh.h"
#include <math.h>

typedef struct{float x; float y;} v2d;

class Extrusion : public Mesh{
public:
    Extrusion(vector<v2d> cut, V3D(*curve)(float), unsigned numOfCuts, double from=0, double to=2*M_PI);
    Extrusion(unsigned raduis, unsigned sides, V3D(*curve)(float), unsigned numOfCuts, double from=0, double to=2*M_PI);
};

#endif // EXTRUSION_H
