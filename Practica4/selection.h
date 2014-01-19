#ifndef SELECTION_H
#define SELECTION_H

#include "v2d.h"

class Selection{
protected:
        V2d centro, p0, pf;
public:
        Selection(V2d centro);
        void paint()const;
        void setV0(V2d p0);
        void setVf(V2d pf);
};

#endif // SELECTION_H
