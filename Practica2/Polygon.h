//Marcos Alarcon Rivas
#ifndef PolygonH
#define PolygonH
#include "Vector.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <stdexcept>
#include <gl\gl.h>
#include <gl\glu.h>
//---------------------------------------------------------------------------
class Polygon{
  private:
        int nVert;
  protected:
        Vector* vertex;
  public:
        Polygon(){};
        Polygon(unsigned int vertices);
       ~Polygon();
        inline int nVertex()const{return nVert;}
        void move(Vector dir);
        virtual void paint()const;
        
        Polygon & operator = (const Polygon &p){
           nVert=p.nVert;
           vertex= new Vector[nVert];
           for(int i=0; i<nVert; i++)
               vertex[i]=p.vertex[i];
           return *this;
        }

        Polygon(const Polygon &p){
           nVert=p.nVert;
           vertex= new Vector[nVert];
           for(int i=0; i<nVert; i++)
                vertex[i]=p.vertex[i];
        }
};
//---------------------------------------------------------------------------
#endif
