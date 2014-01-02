#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "circle.h"
#include "v2d.h"
#include <GL/gl.h>

class Ellipse : public Circle{
protected:
    double width, height, rotation;V2d cent;
    GLdouble transf[16];
    double tr_inv[16];

public:
    Ellipse(V2d center, double W, double H, double rot=0);
    virtual void paint()const;
    virtual bool intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const;

    static void invert(double matrix[4][4], double result[4][4]);
    static inline double determinant(double matrix[4][4]);
    static inline void post_mult(float v[4], const double matrix[16]);
    static inline void pre_mult(const double matrix[16], float v[4]);

};

#endif // ELLIPSE_H
