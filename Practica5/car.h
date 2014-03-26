#ifndef CAR_H
#define CAR_H
#include <mesh.h>
#include <GL/glu.h>

class Car{
private:
    class Cube:public Mesh{
      public: Cube(double x, double y, double z);
      private: void addFace(int f, int i0, int i1, int i2, int i3);
    };

protected:
    V3D(*d0)(double)=0;
    V3D(*d1)(double)=0;
    V3D(*d2)(double)=0;
    float M [16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    double t=0;//current position of the car

    unique_ptr<Cube> chassis=0;
    float cCol[4], wCol[4];//colors
    double wR, wW;//wheels dimensions
    double cW, cH, cL;//wheels positions
    double rollV=360;//rotation speed of wheels
    double rollP=0;//current angle of rotation

private:
    GLUquadric* wheel=0;

public:
    Car(double width, double height, double length, double wheelRadius, double wheelWidth);
   ~Car();
    void setChassisCol(float r, float g, float b, float a=1);
    void setWheelsCol (float r, float g, float b, float a=1);
    void setWay(V3D(*C)(double), V3D(*dC)(double), V3D(*ddC)(double));
    void setRollConstant(double v);
    void setT(double t);
    void advance(double t);
    void paint(bool f=1)const;
    void paintNormals()const;

protected:
    void roll(double angle);
    void frenet(int i=0);
    void makeWheel()const;

};

#endif // CAR_H
