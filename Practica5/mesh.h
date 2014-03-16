#ifndef MESH_H
#define MESH_H
#include "face.h"

class Mesh{
    public:
        void paint(bool fill=1)const;

    protected:
        vector<Face> face;
        vector<vtx_p> vertex;
};

#endif // MESH_H
