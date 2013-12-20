//Marcos Alarcon Rivas
#ifndef BallH
#define BallH
#include "Vector.h"
#include "Circle.h"
#include "Polygon.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <stdexcept>

#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------
class Ball: public Polygon{
   protected:
        Vector direction, movement;
        float speed;

        Vector center;
        float radius;
   public:
         Ball(Vector v=Vector(0,0), Vector center=Vector(0,0), float radius=10, unsigned int nVert=100);
         inline float get_speed()const{return speed;}
         inline Vector get_direction()const{return direction;}
         inline Vector get_movement()const{return movement;}
         inline Vector get_center()const{return center;}
         void revota(Vector normal);
         void avanza(float recorrido);
         void inv_mov();
         virtual void paint()const;
         inline virtual void move(Vector dir){center+=dir;Polygon::move(dir);}
};
//---------------------------------------------------------------------------
#endif
