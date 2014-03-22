#include "extrusion.h"
#include <cmath>

//private fuction to make a regular poligon of @sides points and @rad size
static vector<v2d>& poligon(double rad, unsigned sides){
    static vector<v2d> pol= vector<v2d>(sides);

    float theta = 2 * M_PI / sides;
    //precalculate the sine and cosine
    double c = cos(theta), s = sin(theta);
    //we start at angle = 0
    double x =rad, y = 0;
    for(unsigned i=0; i<sides; i++){
        pol[i]= v2d{(float) x, (float)y};
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
    static vector<v2d> norm = vector<v2d>(s);
    for(unsigned i=0; i<s; i++){
        v2d p= cut[(i+s-1)%s];
        v2d t= cut[i];
        v2d n= cut[(i + 1)%s];
        float dx= t.x-p.x + t.x-n.x;
        float dy= t.y-p.y + t.y-n.y;
        float a=dx*dx, b=dy*dy;
        float mod= sqrt(a+b);
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

//builds the fernet frame for the curve point
static void frenet(float* M, V3D C, V3D dC, V3D ddC){
    V3D T= dC %1, B= dC ^ ddC, N= T ^ B;
                            //this half matrix is not used
    M[0]= N[0]; M[1]= N[1]; //M[2]= N[2]; M[3]= 0;
    M[4]= B[0]; M[5]= B[1]; //M[6]= B[2]; M[7]= 0;
    M[8]= T[0]; M[9]= T[1]; //M[10]=T[2]; M[11]=0;
    M[12]=C[0]; M[13]=C[1]; //M[14]=C[2]; M[15]=1;
}

//joins vertex points for an Extrusion of @num 'cylindres' of @s sides
static void quadFaces(vector<Face> &face, const vector<vtx_p> &vertex, unsigned s, unsigned num){
    face= vector<Face>(s*num);
    for(unsigned c=0; c<num; c++)
        for(unsigned p=0; p<s; p++){
            unsigned cs = c*s, c1s = (c+1)*s;//cut last is not joined whith first
            unsigned p1 = (p+1)%s;
            Face fa= Face(4);
            fa[0]= vertex[p + cs];
            fa[1]= vertex[p1+ cs];
            fa[2]= vertex[p1+c1s];
            fa[3]= vertex[p +c1s];
            face[cs+p]= fa;
        }
}

Extrusion::Extrusion(double r, unsigned s, V3D(*d0)(double),V3D(*d1)(double),
                     V3D(*d2)(double), unsigned n, double t0, double tf)
    :Extrusion(poligon(r,s), d0, d1, d2, n, t0, tf){}

Extrusion::Extrusion(vector<v2d> cut, V3D(*d0)(double),V3D(*d1)(double),V3D(*d2)(double),
                     unsigned num, double t0, double tf){
    unsigned s= cut.size();  //num of sides in each cut
    double step= (tf-t0)/(num-1);//inc in each step of curve
    vector<v2d> norm = normals(cut);

    float M[16]= {1,0,0,0,
                  0,1,0,0,
                  0,0,1,0,
                  0,0,0,1};

    vertex= vector<vtx_p>(s*num);
    double t=t0;
    for(unsigned c=0; c<num; c++, t+=step){
        frenet(M, d0(t), d1(t), d2(t));
        for(unsigned i=0; i<s; i++){
            float x= cut[i].x;
            float y= cut[i].y;
            V3D p = V3D(x*M[0]+y*M[1]+M[3], x*M[4]+y*M[5]+M[7], x*M[8]+y*M[9]+M[11], 1.0);
            x= norm[i].x;
            y= norm[i].y;
            V3D v = V3D(x*M[0]+y*M[1], x*M[4]+y*M[5], x*M[8]+y*M[9], 0.0);
            vertex[c*s+i]= make_shared<vtx>(vtx{p,v});
        }
    }

    quadFaces(face, vertex, s, num-1);
}

Extrusion::Extrusion(double r, unsigned s, V3D(*f)(double), unsigned n, double t0, double tf):
    Extrusion(poligon(r,s), f, n, t0, tf){}

Extrusion::Extrusion(vector<v2d> cut, V3D(*f)(double), unsigned num, double t0, double tf){
    unsigned s= cut.size();  //num of sides in each cut
    double step= (tf-t0)/(num-1);//inc in each step of curve
    vector<v2d> norm = normals(cut);

    //build vertex
    double t=t0;
    V3D _p = f(t0-step), p = f(t0), p_ = f(t0+step);
    vertex= vector<vtx_p>(s*num);
    for(unsigned c=0; c<num; c++, _p=p, p=p_, p_=f(t+=step)){
        V3D d0= (p- _p + p-p_)%1;
        V3D d1= perpen(d0);
        V3D d2= d0 ^ d1;
        float M[16]={d2[0],d1[0],d0[0],p[0],
                     d2[1],d1[1],d0[1],p[0],
                     d2[2],d1[2],d0[2],p[0],
                      0,    0,    0,    1  };

        for(unsigned i=0; i<s; i++){
            float x= cut[i].x;
            float y= cut[i].y;
            V3D p = V3D(x*M[0]+y*M[1]+M[3], x*M[4]+y*M[5]+M[7], x*M[8]+y*M[9]+M[11], 1.0);
            x= norm[i].x;
            y= norm[i].y;
            V3D v = V3D(x*M[0]+y*M[1], x*M[4]+y*M[5], x*M[8]+y*M[9], 0.0);// %1
            vertex[c*s+i]= make_shared<vtx>(vtx{p,v});
        }
    }

    quadFaces(face, vertex, s, num-1);
}

Extrusion::Extrusion(double r, unsigned s, V3D t0, V3D tf)
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
    quadFaces(face, vertex, s, 1);
}
