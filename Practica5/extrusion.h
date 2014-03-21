#ifndef EXTRUSION_H
#define EXTRUSION_H
#include "mesh.h"
#include <math.h>

typedef struct{float x; float y;} v2d;

class Extrusion : public Mesh{
public:
    Extrusion(double raduis, unsigned sides, V3D t0, V3D tf);

    Extrusion(vector<v2d> cut, V3D t0, V3D tf);

    Extrusion(vector<v2d> cut, V3D(*f)(double),unsigned numOfCuts, double from=0, double to=2*M_PI);

    Extrusion(double raduis, unsigned sides, V3D(*f)(double), unsigned numOfCuts, double from=0, double to=2*M_PI);

    Extrusion(vector<v2d> cut, V3D(*d0)(double),V3D(*d1)(double),V3D(*d2)(double),
              unsigned numOfCuts, double from=0, double to=2*M_PI);

    Extrusion(double raduis, unsigned sides, V3D(*d0)(double),V3D(*d1)(double),V3D(*d2)(double),
              unsigned numOfCuts, double from=0, double to=2*M_PI);
};

#endif // EXTRUSION_H
