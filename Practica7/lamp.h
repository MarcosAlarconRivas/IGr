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
    double zR=1;
public:
    Lamp(unsigned lightN=GL_LIGHT1){
       this->lightN=lightN;
       Sphere *s= (new Sphere(.5))->setColor(1,1,1,.5);
       s->translate(0,0,1);
       push(s);
       push((new Cone(1.5,3.5,2.5))->setColor(.1,.9,.02, .75));
    }
    void lightSwich(){
        auto it = begin();
        if(on= !on){
             set_light();
             glEnable(lightN);
             ((Solid*)it->get())->set_emission(1,1,1);
             ((Solid*)(++it)->get())->set_emission(.05,.25,0);
        }else{
             glDisable(lightN);
             ((Solid*)it->get())->set_emission(0,0,0);
             ((Solid*)(++it)->get())->set_emission(0,0,0);
        }
    }
    void paint(bool b)const{
        glCullFace(GL_BACK);
        GLboolean e= glIsEnabled(GL_CULL_FACE);
        glDisable(GL_CULL_FACE);
        Composite::paint(b);
        if(e)glEnable(GL_CULL_FACE);
    }
    void set_light()const{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glMultMatrixd(MMatrix);
            GLfloat LuzDifusa[]={1,.8,.3,1};
            glLightfv(lightN, GL_DIFFUSE, LuzDifusa);
            GLfloat LuzEspec[]={.1,.1,.1,1};
            glLightfv(lightN, GL_SPECULAR, LuzEspec);
            /*GLfloat LuzAmbien[]={.05,.1,0,1};
            glLightfv(lightN, GL_AMBIENT, LuzAmbien);*/
            GLfloat PosLuz[]={0, 0, 0, 1};
            glLightfv(lightN, GL_POSITION, PosLuz);
            GLfloat DirLuz[]={0, 0, 1};
            glLightfv(lightN, GL_SPOT_DIRECTION, DirLuz);

            //glLightf(lightN, GL_CONSTANT_ATTENUATION, .5);
            //glLightf(lightN, GL_LINEAR_ATTENUATION, .01);
            //glLightf(lightN, GL_QUADRATIC_ATTENUATION, .01);

            glLightf(lightN, GL_SPOT_CUTOFF, 40/zR);
            glLightf(lightN, GL_SPOT_EXPONENT, 30);
        glPopMatrix();
    }
    void scale(double x, double y, double z){
        glLightf(lightN, GL_SPOT_CUTOFF, 40/(zR*=x));
        Model::scale(x,y,z);
    }

};
#endif // LAMP_H
