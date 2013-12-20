//Marcos Alarcon Rivas
#ifndef ObstacleH
#define ObstacleH
#include "Vector.h"
#include "Polygon.h"
//---------------------------------------------------------------------------
class Obstacle: public Polygon{
  public:
        Obstacle(unsigned int vertices);
        virtual bool intersection(Vector P, Vector dir, float speed,
                        double& tIn, Vector& normalIn)const =0;

};
//---------------------------------------------------------------------------
#endif
 