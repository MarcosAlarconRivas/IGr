#ifndef FACE_H
#define FACE_H
#include <memory>
#include <vector>
#include <GL/gl.h>
#include "v3d.h"
using namespace std;

typedef struct{
    V3D vert;
    V3D norm;
}vtx;

typedef shared_ptr<vtx> vtx_p;

class Face : public vector<vtx_p>{
public:
    Face(){}
    Face(unsigned numVert):vector<vtx_p>(numVert){}

    void paint(bool fill)const{
        glShadeModel(GL_SMOOTH);
        glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
            for(auto v= begin(); v != end(); v++){
                vtx p= **v;
                glNormal3fv(p.norm.v);
                glVertex3fv(p.vert.v);
            }
        glEnd();
    }
};

#endif // FACE_H
