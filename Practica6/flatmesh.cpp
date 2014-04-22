#include "flatmesh.h"

void FlatMesh::paint(bool fill)const{
    //glShadeModel(GL_FLAT);
    for(auto face= vertex.begin(); face != vertex.end(); face++){
        glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
        auto v= face->begin();
        glNormal3fv((*v)->v);
        for( v++; v!=face->end(); v++)
            glVertex3fv((*v)->v);
        glEnd();
    }
}
