#include "extrusion.h"

//private fuction to make a regular poligon of @sides points and @rad size
static vector<v2d>& poligon(unsigned rad, unsigned sides){
    static vector<v2d> pol= vector<v2d>(sides);
    double inc = 2*M_PI/sides;
    double alpha=0;
    for(unsigned i=0; i<sides; i++, alpha+=inc)
      pol[i]= v2d{ sin(alpha)*rad, cos(alpha)*rad};

    return pol;
}

static vector<v2d>& normals(const vector<v2d>& cut){
    //calculo de las normales
    unsigned s = cut.size();
    vector<v2d> norm = vector<v2d>(s);
    for(unsigned i=0; i<s; i++){
        v2d p= cut[(i+s-1)%s];
        v2d t= cut[i];
        v2d n= cut[(i + 1)%s];
        float dx= t.x-p.x + t.x-n.x;
        float dy= t.y-p.y + t.y-n.y;
        float mod= sqrt(dx*dx +dy*dy);
        norm[i]= v2d{dx/mod, dy/mod};
    }
    return norm;
}

Extrusion::Extrusion(unsigned r, unsigned s, V3D(*f)(double), unsigned n, double t0, double tf)
    :Extrusion(poligon(r,s), f, n, t0, tf){}

Extrusion::Extrusion(vector<v2d> cut, V3D(*f)(double), unsigned num, double t0, double tf){
    if(tf<t0){double x=t0; t0=tf; tf=x;} //begin < end
    //unsigned s= cut.size();  //num of sides in each cut
    double step= (tf-t0)/num;//inc in each step of curve
    vector<v2d> norm = normals(cut);

    double t=t0;
    for(unsigned i=0; i<num; i++, t+=step){
        //TODO
    }

}

Extrusion::Extrusion(unsigned r, unsigned s, V3D t0, V3D tf)
        :Extrusion(poligon(r,s), t0, tf){}

Extrusion::Extrusion(vector<v2d> cut, V3D t0, V3D tf){
    V3D n= tf-t0;
    vector<v2d> norm = normals(cut);

    //TODO
    //translate to t0
    //rotate to n
    //get cut0

    //translate to tf
    //rotate to n
    //get cutf

    //build faces

}



