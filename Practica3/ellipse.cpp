#include "ellipse.h"
#include <cmath>

Ellipse::Ellipse(V2d center, double W, double H, double rot):Circle(center,1){
    /*//en la constructora no funcina :(
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(center.x, center.y, 0);
        glRotatef(rotation, 0, 0, 1);
        glScalef(width, height, 1);
        glGetDoublev(GL_MODELVIEW_MATRIX, transf);
    glPopMatrix();*/

    double r= M_PI * rot/180;
    double c = cos(r);
    double s = sin(r);
    double M[16]=
           {c*W, -s*H,  0,  center.x,
            s*W,  c*H,  0,  center.y,
            0,      0,  1,  0,
            0,      0,  0,  1 };

    for(int i=0; i<16; i++)transf[i]=M[i];
    /*for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            transf[4*i+j]=M[4*j+i];*/
}

void Ellipse::paint()const{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        //glLoadMatrixd(transf);
        //glMultMatrixd(transf);
        glMultTransposeMatrixd(transf);
        glBegin(GL_POLYGON);
            circle_vertex();
        glEnd();
    glPopMatrix();
}

bool Ellipse::intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const{
    return 0;
}
