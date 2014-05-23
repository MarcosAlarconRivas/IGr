#ifndef LAMP_H
#define LAMP_H
#include <GL/glu.h>
#include "composite.h"
#include "cone.h"
#include "sphere.h"

class Lamp: public Composite{
protected:
    bool on=0;
    unsigned lightN;
public:
    Lamp(unsigned lightN=GL_LIGHT1){
       push((new Cone(1.5,3.5,2.5))->setColor(.1,.9,.02, .75));
       this->lightN=lightN;
       Sphere *s= (new Sphere(.5))->setColor(1,1,1,.5);
       s->translate(0,0,1);
       push(s);
    }
    void lightSwich(){
        if(on= !on){
             set_light();
             glEnable(lightN);
        }else
             glDisable(lightN);
    }
    void paint(bool b)const{
        glCullFace(GL_BACK);
        GLboolean e= glIsEnabled(GL_CULL_FACE);
        glDisable(GL_CULL_FACE);
        Composite::paint(b);
        if(e!=GL_FALSE)glEnable(GL_CULL_FACE);
    }
    void set_light()const{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glMultMatrixd(MMatrix);
            GLfloat LuzDifusa[]={1,.8,.5,1};
            glLightfv(lightN, GL_DIFFUSE, LuzDifusa);
            /*GLfloat LuzEspec[]={1,1,1,1};
            glLightfv(lightN, GL_SPECULAR, LuzEspec);
            GLfloat LuzAmbien[]={.05,.1,0,1};
            glLightfv(lightN, GL_AMBIENT, LuzAmbien);*/

            //glLightf(lightN, GL_CONSTANT_ATTENUATION, .5);
            //glLightf(lightN, GL_LINEAR_ATTENUATION, .01);
            //glLightf(lightN, GL_QUADRATIC_ATTENUATION, .1);

            GLfloat PosLuz[]={0, 0, 0, 1};
            glLightfv(lightN, GL_POSITION, PosLuz);
            GLfloat DirLuz[]={0, 0, -1};
            glLightfv(lightN, GL_SPOT_DIRECTION, DirLuz);
            //glLightf(lightN, GL_SPOT_EXPONENT, 64);
            //glLightf(lightN, GL_SPOT_CUTOFF, 90);
        glPopMatrix();
    }

};
#endif // LAMP_H
