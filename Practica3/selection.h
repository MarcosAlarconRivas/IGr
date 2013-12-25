#ifndef SELECTION_H
#define SELECTION_H

#include "ball.h"

class Selection: public Ball{
protected:
        V2d p0, p1, p2;
public:
        Selection(V2d centro);
        virtual void paint()const;
        void setV(V2d dir, float ratio=1);
};

#endif // SELECTION_H
