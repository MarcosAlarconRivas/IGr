//Marcos Alarcon Rivas
#ifndef TriangleH
#define TriangleH

#include "Vector.h"
#include "Polygon.h"
#include "Obstacle.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <stdexcept>
#include <gl\gl.h>
#include <gl\glu.h>
//---------------------------------------------------------------------------
class Triangle : public Obstacle {
    private:
        Vector norm[3];

        Vector centro; float radio;
        //estos se usan para descartar pelotas fuera de la circunferencia

        static int min(double vect[], int leng);
        inline Vector bisectriz(int i)const{
          return (norm[i]+norm[(i+2)%3]).unitario();
        }

    public:
        Triangle(Vector v0, Vector v1, Vector v2);
        
        //heredados de Obstacle
        virtual void paint()const;
        virtual bool intersection(Vector P, Vector v, float speed,
                                        double& tIn,Vector& normalIn)const;

};
//---------------------------------------------------------------------------
#endif
 