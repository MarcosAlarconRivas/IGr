#ifndef MESH_H
#define MESH_H
#include "face.h"
#include "model.h"

class Mesh: public Model{
public:
    void paint(bool fill=1)const;
    void paintNormals()const;
protected:
    vector<Face> face;
    vector<vtx_p> vertex;
};

#endif // MESH_H
