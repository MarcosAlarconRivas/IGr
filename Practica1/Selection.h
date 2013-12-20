//Marcos Alarcon Rivas

#ifndef SelectionH
#define SelectionH

#include "Cuadrado.h"
class Selection: public Cuadrado{
protected:
        GLfloat cx, cy;
public:
        Selection(GLfloat cX, GLfloat cY, GLfloat v1X, GLfloat v1Y);
        void paint()const;
        void setV1(GLfloat x1, GLfloat y1);
};
//---------------------------------------------------------------------------
#endif
