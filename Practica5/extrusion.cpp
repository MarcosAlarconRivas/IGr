#include "extrusion.h"

//private fuction to make a regular poligon of @sides points and @rad size
static vector<v2d>& poligon(unsigned rad, unsigned sides){
    static vector<v2d> pol= vector<v2d>(sides);

    float theta = 2 * M_PI / sides;
    //precalculate the sine and cosine
    double c = cos(theta), s = sin(theta);
    //we start at angle = 0
    double x =rad, y = 0;
    for(unsigned i=0; i<sides; i++){
        pol[i]= v2d{(float) x*rad, (float)y*rad};
        //apply the rotation matrix
        double t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    return pol;
}

//returns normals for a 2d poligon
static vector<v2d>& normals(const vector<v2d>& cut){
    unsigned s = cut.size();
    vector<v2d> norm = vector<v2d>(s);
    for(unsigned i=0; i<s; i++){
        v2d p= cut[(i+s-1)%s];
        v2d t= cut[i];
        v2d n= cut[(i + 1)%s];
        float dx= t.x-p.x + t.x-n.x;
        float dy= t.y-p.y + t.y-n.y;
        float mod= sqrt(dx*dx +dy*dy);
        norm[i]= mod ? v2d{dx/mod, dy/mod}: v2d{0,0};
    }
    return norm;
}

//returns a perpendicular vector to v,, |v|=1
static V3D perpen(V3D v){
    if(v[0]){
        float k = -(v[1]+v[2])/v[0];
        float m = sqrt(k*k+2);
        float u = 1/m;
        return V3D{k/m, u, u, 0};
    }
    if(v[1]){
        float k = -(v[0]+v[2])/v[1];
        float m = sqrt(k*k+2);
        float u = 1/m;
        return V3D{u, k/m, u, 0};
    }
    if(v[2]){
        float k = -(v[0]+v[1])/v[2];
        float m = sqrt(k*k+2);
        float u = 1/m;
        return V3D{u, u, k/m, 0};
    }
    return V3D(0,0,0,0);
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
    unsigned s = cut.size();
    vertex= vector<vtx_p>(2*s);

    V3D px= perpen(n);
    V3D py= px ^ n;
    float M[16]=
       {px[0], py[0], n[0], t0[0],
        px[1], py[1], n[1], t0[1],
        px[2], py[2], n[2], t0[2],
        0,     0,     0,    1   };
    //get cut0
    for(unsigned i=0; i<s; i++){
        float x= cut[i].x;
        float y= cut[i].y;
        V3D p = V3D(x*M[0]+y*M[1]+M[3], x*M[4]+y*M[5]+M[7], x*M[8]+y*M[9]+M[11], 1.0);
        x= norm[i].x;
        y= norm[i].y;
        V3D v = V3D(x*M[0]+y*M[1], x*M[4]+y*M[5], x*M[8]+y*M[9], 0.0);
        vertex[i]= make_shared<vtx>(vtx{p,v});
    }

    M[3]=tf[0]; M[7]=tf[1]; M[11]=tf[2];
    //get cutf
    for(unsigned i=0; i<s; i++){
        float x= cut[i].x;
        float y= cut[i].y;
        V3D p = V3D{x*M[0]+y*M[1]+M[3], x*M[4]+y*M[5]+M[7], x*M[8]+y*M[9]+M[11], 1.0};
        V3D v = vertex[i]->norm;
        vertex[s+i]= make_shared<vtx>(vtx{p,v});
    }

    //build faces
    face= vector<Face>(s);
    for(unsigned i=0; i<s; i++){
        unsigned j= (i+1)%s;
        Face fa= Face(4);
        fa[0]= vertex[i];
        fa[1]= vertex[j];
        fa[2]= vertex[j+s];
        fa[3]= vertex[i+s];
        face[i]= fa;
    }
}



