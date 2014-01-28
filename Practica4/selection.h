#ifndef SELECTION_H
#define SELECTION_H

#include "v2d.h"

class Selection{
protected:
        V2d centro, pib, curr;
        float rad;
public:
        Selection(V2d centro);
        void paint()const;
        void setV(V2d curr);
};

#endif // SELECTION_H
