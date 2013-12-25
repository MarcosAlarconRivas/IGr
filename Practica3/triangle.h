#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "obstacle.h"

class Triangle : public Obstacle {
private:
    V2d vertex[3];
    V2d norm[3];

    V2d centro; float radio;
    //estos se usan para descartar pelotas fuera de la circunferencia

    inline V2d bisectriz(int i)const{
      return (norm[i]+norm[(i+2)%3])%1;
    }

public:
    Triangle(V2d v0, V2d v1, V2d v2);
    virtual void paint()const;
    virtual bool intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const;

};

#endif // TRIANGLE_H
