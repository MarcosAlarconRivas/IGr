#include "solid.h"

void Solid::render(bool fill)const{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    Model::render(fill);
}

/*void Solid::setColor(float r, float g, float b, float a){
    ambient[0]=r*.2;
    ambient[1]=g*.2;
    ambient[2]=b*.2;
    diffuse[0]=r*.2;
    diffuse[1]=g*.2;
    diffuse[2]=b*.2;
    diffuse[3]=ambient[3]=a;
}*/

void Solid::set_ambient(float r, float g, float b, float a){
    ambient[0]=r;
    ambient[1]=g;
    ambient[2]=b;
    ambient[3]=a;
}

void Solid::set_diffuse(float r, float g, float b, float a){
    diffuse[0]=r;
    diffuse[1]=g;
    diffuse[2]=b;
    diffuse[3]=a;
}

void Solid::set_specular(float r, float g, float b, float a){
    specular[0]=r;
    specular[1]=g;
    specular[2]=b;
    specular[3]=a;
}
void Solid::set_emission(float r, float g, float b, float a){
    emission[0]=r;
    emission[1]=g;
    emission[2]=b;
    emission[3]=a;
}
