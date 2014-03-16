#include "mesh.h"


void Mesh::paint(bool fill)const{
    for(auto f= face.begin(); f != face.end(); f++)
        f->paint(fill);
}
