#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glu.h>
#include "v3d.h"

class Camera{
protected:
    V3D eye, look, up; //Camera
    GLdouble zoom=1, N=1, F=100;
    int perspective=1;
    unsigned width=100, height=100;
    V3D oblicV;

public:
    Camera();
    Camera(unsigned width, unsigned height);
    void roll(double angle); void yaw(double angle); void pitch(double angle);
    void orbitX(double angle); void orbitY(double angle); void orbitZ(double angle);
    void travel(float x, float y, float z);
    void Zoom(double ratio);
    void setZoom(double zoom);
    void setVolume(double Near, double Far);
    void setWindow(unsigned width, unsigned height);
    void lookAt(V3D eye, V3D look, V3D up);
    void lookAt(double eye[3], double look[3], double up[3]);
    void lookAt(double eye0, double eye1, double eye2,
                double look0=0, double look1=0,double look2=0,
                double up0=0, double up1=1, double up2=0);

    inline void Orthogonal(){
        perspective=0; aplyView();
    }
    inline void Perspective(){
        perspective=1; aplyView();
    }
    inline void Oblique(V3D d){
        perspective=2; oblicV=d; aplyView();
    }

    inline void side(double d){
        lookAt(d,0,0);
    }
    inline void front(double d){
        lookAt(0,0,d);
    }
    inline void top(double d){
        lookAt(0,d,0, 0,0,0, -1,0,0);
    }
    void oposed();

protected:
    void aplyView();
    void lookThere();

};

#endif // CAMERA_H
