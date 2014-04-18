#ifndef MODEL_H
#define MODEL_H
#include "GL/gl.h"

class Model{
public:
    virtual ~Model(){}

    void render(bool fill=1)const;

    void reset();
    void mutlTrans(const double M[16]);
    void scale(double x, double y, double z);
    void translate(double x, double y, double z);
    void rotate(double angle, double x, double y, double z);

protected:
    virtual void paint(bool fill)const=0;
    double MMatrix[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
};

#endif // MODEL_H
