#ifndef MESH_H
#define MESH_H
#include "face.h"

class Mesh{
    public:
        void paint(bool fill=1)const;

    protected:
        vector<Face> face;
        vector<vtx> vertex;
        vector<vtx> normal;
};

#endif // MESH_H
