#include "ellipse.h"
#include <cmath>
#include <GL/gl.h>

Ellipse::Ellipse(V2d center, double W, double H, double rot):Circle(V2d(0,0),1){
    double r= M_PI * rot/180;//openGl works with degrees
    double c = cos(r);
    double s = sin(r);
    double M[16]=
       {c*W, -s*H,  0,  center.x,
        s*W,  c*H,  0,  center.y,
        0,      0,  1,  0,
        0,      0,  0,  1 };
    for(int i=0; i<16; i++)transf[i]=M[i];

    double w=1/W, h=1/H;
    double N[16]=
        {c*w,  s*w,  0,  -center.x*c*w -center.y*s*w,
        -s*h,  c*h,  0,  +center.x*s*h -center.y*c*h,
         0,      0,  1,  0,
         0,      0,  0,  1 };
    for(int i=0; i<16; i++)tr_inv[i]=N[i];
}

void Ellipse::paint()const{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glMultTransposeMatrixd(transf);
        glBegin(GL_POLYGON);
            circle_vertex();
        glEnd();
    glPopMatrix();
}

bool Ellipse::intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const{
    float pt[4]={p.x,p.y,0,1};
    float dt[4]={d.x,d.y,0,0};
    pre_mult(tr_inv, pt);
    pre_mult(tr_inv, dt);
    return Circle::intersection(V2d(pt),V2d(dt), s, tIn, normalIn);
    /*if(! Circle::intersection(V2d(pt),V2d(dt), s, tIn, normalIn))return 0;
    float nt[]= {normalIn.x, normalIn.y, 0, 0};
    pre_mult(transf, nt);
    normalIn=V2d(nt)%1;
    return 1;*/
}

void Ellipse::pre_mult(const double m[16], float v[4]){
    float x=v[0], y=v[1], z=v[2], p=v[3];
    v[0]=x*m[0]+y*m[1]+z*m[2]+p*m[3];
    v[1]=x*m[4]+y*m[5]+z*m[6]+p*m[7];
    v[2]=x*m[8]+y*m[9]+z*m[10]+p*m[11];
    v[3]=x*m[12]+y*m[13]+z*m[14]+p*m[15];
}
