#ifndef EXTRUSION_H
#define EXTRUSION_H
#include "mesh.h"

class Extrusion : public Mesh{
public:
    Extrusion(vector<vtx> cut, V3D(*curve)(float), unsigned numOfCuts);
    Extrusion(unsigned raduis, unsigned sides, V3D(*curve)(float), unsigned numOfCuts);
};

#endif // EXTRUSION_H
