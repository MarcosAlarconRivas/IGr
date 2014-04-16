#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glu.h>
#include "v3d.h"

class Camera{
protected:
    V3D eye, look, up; //Camera
    GLdouble zoom=1, N=1, F=100;
    int perspective=0;
    unsigned width=100, height=100;
    V3D oblicV;

public:
    Camera();
    Camera(unsigned width, unsigned height);
    void roll(double a); void yaw(double a); void pitch(double a);
    void turnX(double a); void turnY(double a); void turnZ(double a);
    void travel(float x, float y, float z);
    void side(double dist); void front(double dist); void zenit(double dist);
    void lookAt(V3D eye, V3D look, V3D up);
    void lookAt(double eye[3], double look[3], double up[3]);
    void lookAt(double eye0, double eye1, double eye2,
                        double look0=0, double look1=0,double look2=0,
                        double up0=0, double up1=1, double up2=0);
    void Zoom(double ratio);
    void setZoom(double zoom);
    void setVolume(double Near, double Far);
    void setWindow(unsigned width, unsigned height);

    inline void Orthogonal(){
        perspective=0; aplyView();
    }
    inline void Perspective(){
        perspective=1; aplyView();
    }
    inline void Oblique(V3D d){
        perspective=2; oblicV=d; aplyView();
    }

protected:
    void aplyView();
    void lookThere();

};

#endif // CAMERA_H
