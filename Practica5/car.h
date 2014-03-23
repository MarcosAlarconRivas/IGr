#ifndef CAR_H
#define CAR_H
#include <mesh.h>

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
    float cCol[4], wCol[4];
    double t=0, rollW=1;
    unique_ptr<Cube> chassis=0;
    //vector<GLUquadric> wheel= vector<GLUquadric>(4);

public:
    Car(double width, double height, double length, double wheelRadius, double wheelWidth);
    void setChassisCol(float r, float g, float b, float a=1);
    void setWheelsCol (float r, float g, float b, float a=1);
    void setWay(V3D(*C)(double), V3D(*dC)(double), V3D(*ddC)(double));
    void setRollConstant(double v);
    void setT(double t);
    void advance(double t);
    void paint(bool f=1)const;

private:
    void roll(double angle);
    void frenet();

};

#endif // CAR_H
