#include "camera.h"

Camera::Camera(){
    eye=V3D(0,0,0,1);
    look=V3D(1,1,1,1);
    up=V3D(0,1,0,0);
}

Camera::Camera(unsigned width, unsigned height):Camera(){
    setWindow(width, height);
}

void Camera::setWindow(unsigned w, unsigned h){
    width=w;
    height=h;
    aplyView();
}

void Camera::travel(float x, float y, float z){
    eye[0]+=x;
    eye[1]+=y;
    eye[2]+=z;
    lookThere();
}

void Camera::setZoom(double zoom){
    this->zoom=zoom;
    aplyView();
}

void Camera::Zoom(double ratio){
    zoom*=ratio;
    aplyView();
}

void Camera::setVolume(double Near, double Far){
    N=Near; F=Far;
    aplyView();
}

void Camera::aplyView(){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

    if(!perspective){//Orthogonal
         double z= 2*zoom;
         double w= width/z, h= height/z;
         glOrtho(-w, w,-h, h, N, F);

    }else if(perspective==1){//Perspective
         gluPerspective(zoom, ((double) width)/height, N, F);

    }else if(perspective==2){//Oblique
        double w= width/2.0, h= height/2.0;
        glOrtho(-w, w,-h, h, N, F);

        double x=oblicV[0], y=oblicV[1], z=oblicV[2];
        if(z!=0 && (x!=0 || y!=0)){
            double x_z = x/z;
            double y_z = y/z;
            double M[16]= {
               1, 0, -x_z, -N*x_z,
               0, 1, -y_z, -N*y_z,
               0, 0,   1,    0,
               0, 0,   0,    1
            };
           glMultMatrixd(M);
            //glMultTransposeMatrixd(M);
        }
    }




     glMatrixMode(GL_MODELVIEW);
}

void Camera::lookAt(V3D eye, V3D look, V3D up){
    lookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);
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

void Camera::roll(double a){

}

void Camera::yaw(double a){

}

void Camera::pitch(double a){

}

void Camera::orbitX(double a){

}

void Camera::orbitY(double a){

}

void Camera::orbitZ(double a){

}

void Camera::oposed(){
    eye[0]= -eye[0];
    eye[1]= -eye[1];
    eye[2]= -eye[2];
    lookThere();
}




