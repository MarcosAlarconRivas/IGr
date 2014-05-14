#ifndef SMOOTHMESH_H
#define SMOOTHMESH_H
#include "face.h"
#include "model.h"

class SmoothMesh: public Model{
public:
    void paint(bool fill=1)const;
    void paintNormals()const;
protected:
    vector<Face> face;
    vector<vtx_p> vertex;
};

#endif // SMOOTHMESH_H
