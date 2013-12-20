//Marcos Alarcon Rivas
#ifndef CircleH
#define CircleH
#include "Vector.h"
#include "Obstacle.h"

//---------------------------------------------------------------------------
class Circle: public Obstacle{
   protected:
        float radius;
        Vector center;
  public:
        Circle(Vector center, float radius, unsigned int vertices=100);

        inline virtual void move(Vector dir){center+=dir;Polygon::move(dir);}
        virtual bool intersection(Vector P, Vector dir, float speed,
                        double& tIn, Vector& normalIn)const;

};
//---------------------------------------------------------------------------
#endif
