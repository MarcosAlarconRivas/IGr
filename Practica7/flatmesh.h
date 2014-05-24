#ifndef FLATMESH_H
#define FLATMESH_H
#include "solid.h"
#include "v3d.h"
#include "vector"
#include "memory"
using namespace std;

class FlatMesh : public Solid{
protected:
     vector< vector<shared_ptr<V3D>> > vertex;
     void paint(bool fill)const;
};

#endif // FLATMESH_H
