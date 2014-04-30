#ifndef BALL_H
#define BALL_H
#include "sphere.h"
#include "v3d.h"

class Ball: public Sphere{
    V3D memPosition;
    double R[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
public:
    Ball(double R=1, unsigned s=10, unsigned t=10,float r=1, float g=1, float b=1, float a=1)
        :Sphere(R,s,t,r,g,b,a){memorize();}

    void slide(V3D dir, double d){
        V3D v = dir*d;
        translate(v[0], v[1], v[2]);
    }

    void selfRot(double a, double x, double y, double z){
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadMatrixd(R);
            glRotated(a, x, y, z);
            glGetDoublev(GL_MODELVIEW_MATRIX, R);
        glPopMatrix();
    }

    void paint(bool f)const{
        glPushMatrix();
            glMultMatrixd(R);
            Sphere::paint(f);
        glPopMatrix();
    }

    void  roll(V3D dir, V3D up, double d){
        slide(dir, d);
        V3D axis = dir ^ up;
        d *= dir.mod();
        double angle = (d/radius)*180/M_PI;
        selfRot(angle, axis[0], axis[1], axis[2]);
    }

    void memorize(){
        memPosition[0]=MMatrix[12];
        memPosition[1]=MMatrix[13];
        memPosition[2]=MMatrix[14];
    }

    void restore(){
        MMatrix[12]=memPosition[0];
        MMatrix[13]=memPosition[1];
        MMatrix[14]=memPosition[2];
    }

    V3D getMemPosition(){
        return V3D(memPosition);
    }

    V3D getCurrentPosition(){
        return V3D((float)MMatrix[12], (float)MMatrix[13], (float)MMatrix[14], 1.0);
    }
};

#endif // BALL_H
