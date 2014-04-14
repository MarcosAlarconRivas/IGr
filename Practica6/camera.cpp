#include "camera.h"

Camera::Camera(){}

void Camera::setZoom(double zoom){
    this->zoom=zoom;
}

void Camera::Zoom(double ratio){
    zoom*=ratio;
}

void Camera::setVolume(double Near, double Far){
    N=Near; F=Far;
}

void Camera::aplyView(int width, int height){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     double z= 2*zoom;
     GLdouble x= width/z, y= height/z;
     glOrtho(-x, x,-y, y, N, F);
     glMatrixMode(GL_MODELVIEW);
}

void Camera::lookAt(double eye[3], double look[3], double up[3]){
    lookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);
}

void Camera::lookAt(double eye0, double eye1, double eye2,
                    double look0, double look1,double look2,
                    double up0, double up1, double up2){
    eye[0]=eye0;
    eye[1]=eye1;
    eye[2]=eye2;
    look[0]=look0;
    look[1]=look1;
    look[2]=look2;
    up[0]=up0;
    up[1]=up1;
    up[2]=up2;
    lookThere();
}

void Camera::lookThere(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);
}

