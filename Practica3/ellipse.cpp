#include "ellipse.h"
#include <cmath>

Ellipse::Ellipse(V2d center, double W, double H, double rot):Circle(V2d(0,0),1){
    rotation = rot; width= W; height=H; cent=center;
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

    double w=1/W, h=1/H;
    double N[16]=
    {c*w,  s*w,  0,  -center.x,
    -s*h,  c*h,  0,  -center.y,
     0,      0,  1,  0,
     0,      0,  0,  1 };
    for(int i=0; i<16; i++)tr_inv[i]=N[i];

    /*for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            tr_inv[4*i+j]=M[4*j+i];
    for(int i=0;i<4;i++)
        tr_inv[12+i]=M[12+i];
    for(int i=0;i<3;i++)
        tr_inv[4*(i+1)-1]= -M[3]*M[i] -M[6]*M[i+4] -M[9]*M[i+8];*/
}

void Ellipse::paint()const{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glMultTransposeMatrixd(transf);
        Circle::paint();
    glPopMatrix();
}

bool Ellipse::intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const{
    float pt[4]={p.x,p.y,0,1};
    float dt[4]={d.x,d.y,0,0};
    double M[16];
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glScalef(1/width, 1/height, 1);
        glRotatef(-rotation, 0, 0, 1);
        glTranslatef(-cent.x, -cent.y, 0);
        glGetDoublev(GL_MODELVIEW_MATRIX, M);
    glPopMatrix();
    /*post_mult(pt, tr_inv);
    post_mult(dt, tr_inv);*/
    post_mult(pt, M);
    post_mult(dt, M);
    if(! Circle::intersection(V2d(pt),V2d(dt), s, tIn, normalIn))return 0;
    float nt[]= {normalIn.x, normalIn.y, 0, 0};
    //TODO transformar normalIn
    return 1;
}

void Ellipse::post_mult(float v[4], const double m[16]){
    float x=v[0], y=v[1], z=v[2], p=v[3];
    v[0]=x*m[0]+y*m[4]+z*m[8]+p*m[12];
    v[1]=x*m[1]+y*m[5]+z*m[9]+p*m[13];
    v[2]=x*m[2]+y*m[6]+z*m[10]+p*m[14];
    v[3]=x*m[3]+y*m[7]+z*m[11]+p*m[15];
}

void Ellipse::pre_mult(const double m[16], float v[4]){
    float x=v[0], y=v[1], z=v[2], p=v[3];
    v[0]=x*m[0]+y*m[1]+z*m[2]+p*m[3];
    v[1]=x*m[4]+y*m[5]+z*m[6]+p*m[7];
    v[2]=x*m[8]+y*m[9]+z*m[10]+p*m[11];
    v[3]=x*m[12]+y*m[13]+z*m[14]+p*m[15];
}

void Ellipse::invert(double m[4][4], double r[4][4]) {
   //double d= determinant(m);
}

double Ellipse::determinant(double m[4][4]){
    return
    m[0][3]*m[1][2]*m[2][1]*m[3][0] - m[0][2]*m[1][3]*m[2][1]*m[3][0] - m[0][3]*m[1][1]*m[2][2]*m[3][0] + m[0][1]*m[1][3]*m[2][2]*m[3][0]+
    m[0][2]*m[1][1]*m[2][3]*m[3][0] - m[0][1]*m[1][2]*m[2][3]*m[3][0] - m[0][3]*m[1][2]*m[2][0]*m[3][1] + m[0][2]*m[1][3]*m[2][0]*m[3][1]+
    m[0][3]*m[1][0]*m[2][2]*m[3][1] - m[0][0]*m[1][3]*m[2][2]*m[3][1] - m[0][2]*m[1][0]*m[2][3]*m[3][1] + m[0][0]*m[1][2]*m[2][3]*m[3][1]+
    m[0][3]*m[1][1]*m[2][0]*m[3][2] - m[0][1]*m[1][3]*m[2][0]*m[3][2] - m[0][3]*m[1][0]*m[2][1]*m[3][2] + m[0][0]*m[1][3]*m[2][1]*m[3][2]+
    m[0][1]*m[1][0]*m[2][3]*m[3][2] - m[0][0]*m[1][1]*m[2][3]*m[3][2] - m[0][2]*m[1][1]*m[2][0]*m[3][3] + m[0][1]*m[1][2]*m[2][0]*m[3][3]+
    m[0][2]*m[1][0]*m[2][1]*m[3][3] - m[0][0]*m[1][2]*m[2][1]*m[3][3] - m[0][1]*m[1][0]*m[2][2]*m[3][3] + m[0][0]*m[1][1]*m[2][2]*m[3][3];
}
