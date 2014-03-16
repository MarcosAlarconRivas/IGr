#ifndef FACE_H
#define FACE_H
#include <memory>
#include <vector>
#include <GL/gl.h>
#include "v3d.h"
using namespace std;

typedef shared_ptr<V3D> vtx;

class Face : public vector<vtx>{
    public:
        vtx  normal;

        Face(unsigned numVert):vector<vtx>(numVert){normal=0;}

        void paint(bool fill)const{
            glBegin(fill?GL_POLYGON:GL_LINE_LOOP);
                for(auto v= begin(); v != end(); v++){
                    glNormal3fv(*normal);
                    glVertex3fv(**v);
                }
            glEnd();
        }
};

#endif // FACE_H
