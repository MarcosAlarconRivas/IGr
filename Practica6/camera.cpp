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

void Camera::orbitX(double a){
    double p= atan2(eye[1], eye[2]) + a;
    eye[2]=cos(p);
    eye[1]=sin(p);
    lookThere();
}

void Camera::orbitY(double a){
    double p= atan2(eye[2], eye[0]) + a;
    eye[0]=cos(p);
    eye[2]=sin(p);
    lookThere();
}

void Camera::orbitZ(double a){
    double p= atan2(eye[1], eye[0]) + a;
    eye[0]=cos(p);
    eye[1]=sin(p);
    lookThere();
}

void Camera::oposed(){
    eye[0]= -eye[0];
    eye[1]= -eye[1];
    eye[2]= -eye[2];
    lookThere();
}

static void preM(float *v, const double *M){
    float r[3];
    for(int i=0; i<3; i++)
        r[i]= M[i]*v[0]+M[i+4]*v[1]+M[i+8]*v[2]+M[i+12]*v[3];

    for(int i=0; i<3; i++)
        v[i]=r[i];
}

void Camera::roll(double a){
    double R[16];
    V3D f = look - eye;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glRotated(a*180/M_PI, f[0], f[1], f[2]);
        glGetDoublev(GL_MODELVIEW_MATRIX, R);
    glPopMatrix();

    preM(up.v, R);
    lookThere();
}

void Camera::yaw(double a){
    double R[16];

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glRotated(a*180/M_PI, up[0], up[1], up[2]);
        glGetDoublev(GL_MODELVIEW_MATRIX, R);
    glPopMatrix();

    V3D f = look - eye;
    preM(f.v , R);
    look = f + eye;
    lookThere();
}

void Camera::pitch(double a){
    double R[16];
    V3D f= look-eye;
    V3D x= up ^ f;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glRotated(a*180/M_PI, x[0], x[1], x[2]);
        glGetDoublev(GL_MODELVIEW_MATRIX, R);
    glPopMatrix();

    preM(up.v, R);
    V3D F = look - eye;
    preM(F.v , R);
    look = F + eye;
    lookThere();
}
