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
        float angle()const;
        V2d pibt()const;
        V2d cent()const;
};

#endif // SELECTION_H
