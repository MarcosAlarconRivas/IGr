#ifndef SOLID_H
#define SOLID_H
#include "model.h"

class Solid : public Model{
public:
    GLfloat ambient[4]={0.2, 0.2, 0.2, 1.0};
    GLfloat diffuse[4]={0.8, 0.8, 0.8, 1.0};
    GLfloat specular[4]={0,  0,  0,  1};
    GLfloat emission[4]={0,  0,  0,  1};
    GLfloat shininess=0;
    //void setColor(float r, float g, float b, float a=1);
    void set_emission(float r, float g, float b, float a=1);
    void set_specular(float r, float g, float b, float a=1);
    void set_diffuse(float r, float g, float b, float a=1);
    void set_ambient(float r, float g, float b, float a=1);
protected:
    virtual void render(bool fill=1)const;
};

#endif // SOLID_H
