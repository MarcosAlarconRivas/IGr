//Marcos Alarcon Rivas

#ifndef SelectionH
#define SelectionH
#include "Ball.h"
class Selection: public Ball{
protected:
        Vector p0, p1, p2;
public:
        Selection(Vector centro);
        virtual void paint()const;
        void setV(Vector dir, float ratio=1);
};
//---------------------------------------------------------------------------
#endif
