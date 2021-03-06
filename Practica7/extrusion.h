#ifndef EXTRUSION_H
#define EXTRUSION_H
#include "smoothmesh.h"
#include <math.h>

typedef struct{float x; float y;} v2d;

class Extrusion : public SmoothMesh{
public:
    Extrusion(double raduis, unsigned sides, V3D t0, V3D tf);

    Extrusion(vector<v2d> cut, V3D t0, V3D tf);

    Extrusion(vector<v2d> cut, V3D(*f)(double),unsigned numOfCuts, double from=0, double to=2*M_PI);

    Extrusion(double raduis, unsigned sides, V3D(*f)(double), unsigned numOfCuts, double from=0, double to=2*M_PI);

    Extrusion(vector<v2d> cut, V3D(*d0)(double),V3D(*d1)(double),V3D(*d2)(double),
              unsigned numOfCuts, double from=0, double to=2*M_PI);

    Extrusion(double raduis, unsigned sides, V3D(*d0)(double),V3D(*d1)(double),V3D(*d2)(double),
              unsigned numOfCuts, double from=0, double to=2*M_PI);

protected:
    Extrusion(){}
    static vector<v2d>& poligon(double rad, unsigned sides);
    static vector<v2d>& normals(const vector<v2d>& cut);
    static void frenet(float* M, V3D C, V3D dC, V3D ddC);
};

#endif // EXTRUSION_H
