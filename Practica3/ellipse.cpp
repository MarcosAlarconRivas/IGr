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

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            tr_inv[4*i+j]=M[4*j+i];
    for(int i=0;i<4;i++)
        tr_inv[12+i]=M[12+i];
    for(int i=0;i<3;i++)
        tr_inv[4*(i+1)-1]= -M[3]*M[i] -M[6]*M[i+4] -M[9]*M[i+8];

    for(int i=0; i<16; i++)transf[i]=M[i];
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
    float pt[4]={p.x,p.y,0,1};
    float dt[4]={d.x,d.y,0,0};
    transfV(pt);
    transfV(dt);
    return Circle::intersection(V2d(pt),V2d(dt), s, tIn, normalIn);
    //TODO transformar normalIn
}

void Ellipse::transfV(float *v)const{
    float x=v[0], y=v[1], z=v[2], p=v[3];
    v[0]=x*tr_inv[0]+y*tr_inv[4]+z*tr_inv[8]+p*tr_inv[12];
    v[1]=x*tr_inv[1]+y*tr_inv[5]+z*tr_inv[9]+p*tr_inv[13];
    v[2]=x*tr_inv[2]+y*tr_inv[6]+z*tr_inv[10]+p*tr_inv[14];
    v[3]=x*tr_inv[3]+y*tr_inv[7]+z*tr_inv[11]+p*tr_inv[15];
}
