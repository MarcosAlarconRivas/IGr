//Marcos Alarcon Rivas

#ifndef CuadradoH
#define CuadradoH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <stdexcept>
#include <gl\gl.h>
#include <gl\glu.h>
typedef GLfloat point[2];

class Cuadrado{
    protected:
        GLfloat x[4], y[4];
        //inline Cuadrado(){};
    public:
        Cuadrado(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1);
        inline Cuadrado(point p0, point p3){Cuadrado(p0[0], p0[1], p3[0], p3[1]);}
        //~Cuadrado();
        void paint()const;
        bool contain(GLfloat px, GLfloat py);
        point* get(unsigned int vert) const throw(std::bad_alloc);
        inline GLfloat getx(unsigned int vert)const throw(std::bad_alloc)
        {return x[vert];}
        inline GLfloat gety(unsigned int vert)const throw(std::bad_alloc)
        {return y[vert];}

};
//---------------------------------------------------------------------------
#endif