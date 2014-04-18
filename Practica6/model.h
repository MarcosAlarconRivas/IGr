#ifndef MODEL_H
#define MODEL_H
#include "GL/gl.h"
class Model{
public:
    double MMatrix[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    void render(bool fill=1)const{
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glMultMatrixd(MMatrix);
            paint(fill);
        glPopMatrix();
    }
protected:
    virtual void paint(bool fill)const=0;
};

#endif // MODEL_H
