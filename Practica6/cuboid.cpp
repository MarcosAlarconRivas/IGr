#include "cuboid.h"

static vector<shared_ptr<V3D>> buildFace(unsigned i, unsigned j, unsigned l,
                                         shared_ptr<V3D> n, vector<shared_ptr<V3D>> point, bool f){
   auto face= vector<shared_ptr<V3D>>(5);
   l++;
   face[0]=n;
   face[1]=point[i+j*l];
   face[f?2:4]=point[i+(j+1)*l];
   face[3]=point[1+i+(j+1)*l];
   face[f?4:2]=point[1+i+j*l];
   return face;
}

Cuboid::Cuboid(double w, double h, double d, unsigned x, unsigned y, unsigned z){
//TODO share edge points
    x++; y++; z++;
    double ix= w/x, iy= h/y, iz= d/z;

    //face z=0
    auto points= vector<shared_ptr<V3D>>((x+1)*(y+1));
    for(unsigned j=0; j<=y; j++)
            for(unsigned i=0; i<=x; i++)
                points[i+j*(x+1)]= make_shared<V3D>(V3D(ix*i, iy*j, 0, 1));

    auto n= make_shared<V3D>(V3D(0,0,-1,0));
    for(unsigned j=0; j<y; j++)
            for(unsigned i=0; i<x; i++)
                vertex.push_back(buildFace(i,j,x,n,points,1));
    //face z=d
    points= vector<shared_ptr<V3D>>((x+1)*(y+1));
    for(unsigned j=0; j<=y; j++)
            for(unsigned i=0; i<=x; i++)
                points[i+j*(x+1)]= make_shared<V3D>(V3D(ix*i, iy*j, d, 1));

    n= make_shared<V3D>(V3D(0,0,1,0));
    for(unsigned j=0; j<y; j++)
            for(unsigned i=0; i<x; i++)
                vertex.push_back(buildFace(i,j,x,n,points,0));
    //face y=0
    points= vector<shared_ptr<V3D>>((x+1)*(z+1));
    for(unsigned j=0; j<=z; j++)
            for(unsigned i=0; i<=x; i++)
                points[i+j*(x+1)]= make_shared<V3D>(V3D(ix*i,0,iz*j, 1));

    n= make_shared<V3D>(V3D(0,-1,0,0));
    for(unsigned j=0; j<z; j++)
            for(unsigned i=0; i<x; i++)
                vertex.push_back(buildFace(i,j,x,n,points,0));
    //face y=h
    points= vector<shared_ptr<V3D>>((x+1)*(z+1));
    for(unsigned j=0; j<=z; j++)
            for(unsigned i=0; i<=x; i++)
                points[i+j*(x+1)]= make_shared<V3D>(V3D(ix*i,h,iz*j, 1));

    n= make_shared<V3D>(V3D(0,-1,0,0));
    for(unsigned j=0; j<z; j++)
            for(unsigned i=0; i<x; i++)
                vertex.push_back(buildFace(i,j,x,n,points,1));

    //face x=0
    points= vector<shared_ptr<V3D>>((y+1)*(z+1));
    for(unsigned j=0; j<=z; j++)
            for(unsigned i=0; i<=y; i++)
                points[i+j*(y+1)]= make_shared<V3D>(V3D(0,iy*i,iz*j, 0));

    n= make_shared<V3D>(V3D(-1,0,0,0));
    for(unsigned j=0; j<z; j++)
            for(unsigned i=0; i<y; i++)
                vertex.push_back(buildFace(i,j,y,n,points,1));
    //face x=w
    points= vector<shared_ptr<V3D>>((y+1)*(z+1));
    for(unsigned j=0; j<=z; j++)
            for(unsigned i=0; i<=y; i++)
                points[i+j*(y+1)]= make_shared<V3D>(V3D(w,iy*i,iz*j, 1));

    n= make_shared<V3D>(V3D(1,0,0,0));
    for(unsigned j=0; j<z; j++)
            for(unsigned i=0; i<y; i++)
                vertex.push_back(buildFace(i,j,y,n,points,0));

}

Cuboid* Cuboid::setColor(float r, float g, float b, float a){
    color[0]=r;
    color[1]=g;
    color[2]=b;
    color[3]=a;
    return this;
}

Cuboid* Cuboid::setColor(float c[4], float a){
    return setColor(c[0], c[1], c[2], a);
}
