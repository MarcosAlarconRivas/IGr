#ifndef LAMP_H
#define LAMP_H
#include <GL/glu.h>
#include "composite.h"
#include "cone.h"

class Lamp: public Composite{
protected:
    bool on=0;
    unsigned lightN;
public:
    Lamp(unsigned lightN=GL_LIGHT1){
       push((new Cone(1.5,3.5,2.5))->setColor(.1,.9,.02));
       this->lightN=lightN;
    }
    void lightSwich(){
        if(on= !on){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
                glLoadMatrixd(MMatrix);
                GLfloat LuzDifusa[]={1,.6,.2,1};
                glLightfv(lightN, GL_DIFFUSE, LuzDifusa);
                GLfloat PosLuz[]={0, 0, 0, 1};
                glLightfv(lightN, GL_POSITION, PosLuz);
                GLfloat DirLuz[]={0, 0, 1, 1};
                glLightfv(lightN, GL_SPOT_DIRECTION, DirLuz);
            glPopMatrix();
            glEnable(lightN);
        }else
             glDisable(lightN);
    }

};
#endif // LAMP_H
