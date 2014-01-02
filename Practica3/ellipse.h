#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "circle.h"
#include "v2d.h"

class Ellipse : public Circle{
protected:
    double transf[16];
    double tr_inv[16];

public:
    Ellipse(V2d center, double W, double H, double rot=0);
    virtual void paint()const;
    virtual bool intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const;

    static inline void pre_mult(const double matrix[16], float v[4]);

};

#endif // ELLIPSE_H
