#include "extrusion.h"

//private fuction to make a regular poligon of @sides points and @rad size
static vector<v2d>& poligon(unsigned rad, unsigned sides){
    static vector<v2d> pol= vector<v2d>(sides);
    double inc = 2*M_PI/sides;
    double alpha=0;
    for(unsigned i=0; i<sides; i++, alpha+=inc){
      v2d p;
      p.x= sin(alpha)*rad;
      p.y= cos(alpha)*rad;
      pol[i]= p;
    }
    return pol;
}

Extrusion::Extrusion(unsigned r, unsigned s, V3D(*f)(float), unsigned n, double t0, double tf)
    :Extrusion(poligon(r,s), f, n, t0, tf){}

Extrusion::Extrusion(vector<v2d> cut, V3D(*f)(float), unsigned num, double t0, double tf){

}



