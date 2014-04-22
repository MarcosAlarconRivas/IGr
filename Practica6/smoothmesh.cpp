#include "smoothmesh.h"

void SmoothMesh::paint(bool fill)const{
    for(auto f= face.begin(); f != face.end(); f++)
        f->paint(fill);
}

void SmoothMesh::paintNormals()const{
    for(auto v= vertex.begin(); v != vertex.end(); v++){
        vtx_p vt= (*v);
        V3D p= vt->vert;
        glBegin(GL_LINES);
            glVertex3fv(p.v);
            glVertex3fv((p+vt->norm).v);
        glEnd();
    }
}
