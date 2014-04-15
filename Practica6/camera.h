#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glu.h>

class Camera{
protected:
    GLdouble eye[3], look[3], up[3]; //Camera
    GLdouble zoom=1, N=1, F=100;
public:
    Camera();
    void roll(double a); void yaw(double a); void pitch(double a);
    void turnX(double a); void turnY(double a); void turnZ(double a);
    void travel(float x, float y, float z);
    void side(double dist); void front(double dist); void zenit(double dist);
    void aplyView(int width, int height);
    void lookAt(double eye[3], double look[3], double up[3]);
    void lookAt(double eye0, double eye1, double eye2,
                        double look0=0, double look1=0,double look2=0,
                        double up0=0, double up1=1, double up2=0);
    void lookThere();
    void Zoom(double ratio);
    void setZoom(double zoom);
    void setVolume(double Near, double Far);
};

#endif // CAMERA_H
