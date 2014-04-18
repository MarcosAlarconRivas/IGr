#include "model.h"

void Model::render(bool fill)const{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glMultMatrixd(MMatrix);
        paint(fill);
    glPopMatrix();
}

void Model::reset(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glGetDoublev(GL_MODELVIEW_MATRIX, MMatrix);
    glPopMatrix();
}

void Model::mutlTrans(const double *M){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadMatrixd(MMatrix);
        glMultTransposeMatrixd(M);
        glGetDoublev(GL_MODELVIEW_MATRIX, MMatrix);
    glPopMatrix();
}

void Model::scale(double x, double y, double z){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadMatrixd(MMatrix);
        glScaled(x, y, z);
        glGetDoublev(GL_MODELVIEW_MATRIX, MMatrix);
    glPopMatrix();
}

void Model::translate(double x, double y, double z){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadMatrixd(MMatrix);
        glTranslated(x, y, z);
        glGetDoublev(GL_MODELVIEW_MATRIX, MMatrix);
    glPopMatrix();
}

void Model::rotate(double angle, double x, double y, double z){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadMatrixd(MMatrix);
        glRotated(angle, x, y, z);
        glGetDoublev(GL_MODELVIEW_MATRIX, MMatrix);
    glPopMatrix();
}
