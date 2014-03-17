#include "extrusion.h"

//private fuction to make a regular poligon of @sides points and @rad size
static vector<vtx>& poligon(unsigned rad, unsigned sides){
    auto pol= vector<vtx>(sides);
    for(unsigned i=0; i<sides; i++){
      //TODO add vertex
    }
    return pol;
}

Extrusion::Extrusion(unsigned r, unsigned s, V3D(*f)(float), unsigned n)
    :Extrusion(poligon(r,s), f, n){}

Extrusion::Extrusion(vector<vtx> cut, V3D(*f)(float), unsigned num){

}



