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
    x++; y++; z++;
    double ix= w/x, iy= h/y, iz= d/z;
    int t;

    //points shared by mutilpe faces
    auto edgZ0X0= vector<shared_ptr<V3D>>();//(y+1);
    auto edgZ0XW= vector<shared_ptr<V3D>>();//(y+1);
    auto edgZ0Y0= vector<shared_ptr<V3D>>();//(x+1);
    auto edgZ0YH= vector<shared_ptr<V3D>>();//(x+1);
    auto edgZDX0= vector<shared_ptr<V3D>>();//(y+1);
    auto edgZDXW= vector<shared_ptr<V3D>>();//(y+1);
    auto edgZDY0= vector<shared_ptr<V3D>>();//(x+1);
    auto edgZDYH= vector<shared_ptr<V3D>>();//(x+1);
    auto edgY0X0= vector<shared_ptr<V3D>>(1);//(z+1)-2
    auto edgY0XW= vector<shared_ptr<V3D>>(1);//(z+1)-2
    auto edgYHX0= vector<shared_ptr<V3D>>(1);//(z+1)-2
    auto edgYHXW= vector<shared_ptr<V3D>>(1);//(z+1)-2

    //face z=0
    auto points= vector<shared_ptr<V3D>>((x+1)*(y+1));
    for(unsigned j=0; j<=y; j++)
            for(unsigned i=0; i<=x; i++){
                auto p = make_shared<V3D>(V3D(ix*i, iy*j, 0, 1));
                points[i+j*(x+1)]= p;
                if(!j)edgZ0Y0.push_back(p);
                if(j==y)edgZ0YH.push_back(p);
                if(!i)edgZ0X0.push_back(p);
                if(i==x)edgZ0XW.push_back(p);
            }


    auto n= make_shared<V3D>(V3D(0,0,-1,0));
    for(unsigned j=0; j<y; j++)
            for(unsigned i=0; i<x; i++)
                vertex.push_back(buildFace(i,j,x,n,points,1));
    //face z=d
    points= vector<shared_ptr<V3D>>((x+1)*(y+1));
    for(unsigned j=0; j<=y; j++)
            for(unsigned i=0; i<=x; i++){
                auto p =make_shared<V3D>(V3D(ix*i, iy*j, d, 1));
                points[i+j*(x+1)]= p;
                if(!j)edgZDY0.push_back(p);
                if(j==y)edgZDYH.push_back(p);
                if(!i)edgZDX0.push_back(p);
                if(i==x)edgZDXW.push_back(p);
            }

    n= make_shared<V3D>(V3D(0,0,1,0));
    for(unsigned j=0; j<y; j++)
            for(unsigned i=0; i<x; i++)
                vertex.push_back(buildFace(i,j,x,n,points,0));

    //face y=0
    points= vector<shared_ptr<V3D>>((x+1)*(z+1));
    t=0;for(auto e=edgZ0Y0.begin(); e!=edgZ0Y0.end(); e++)points[t++]= *e;
    t=0;for(auto e=edgZDY0.begin(); e!=edgZDY0.end(); e++)points[z*(x+1)+t++]= *e;
    for(unsigned j=1; j<z; j++)
            for(unsigned i=0; i<=x; i++){
                auto p= make_shared<V3D>(V3D(ix*i,0,iz*j, 1));;
                points[i+j*(x+1)]= p;
                if(!i)edgY0X0.push_back(p);
                if(i==x)edgY0XW.push_back(p);
            }

    n= make_shared<V3D>(V3D(0,-1,0,0));
    for(unsigned j=0; j<z; j++)
            for(unsigned i=0; i<x; i++)
                vertex.push_back(buildFace(i,j,x,n,points,0));

    //face y=h
    points= vector<shared_ptr<V3D>>((x+1)*(z+1));
    t=0;for(auto e=edgZ0YH.begin(); e!=edgZ0YH.end(); e++)points[t++]= *e;
    t=0;for(auto e=edgZDYH.begin(); e!=edgZDYH.end(); e++)points[z*(x+1)+t++]= *e;
    for(unsigned j=1; j<z; j++)
            for(unsigned i=0; i<=x; i++){
                auto p = make_shared<V3D>(V3D(ix*i,h,iz*j, 1));
                points[i+j*(x+1)]= p;
                if(!i)edgYHX0.push_back(p);
                if(i==x)edgYHXW.push_back(p);
            }

    n= make_shared<V3D>(V3D(0,-1,0,0));
    for(unsigned j=0; j<z; j++)
            for(unsigned i=0; i<x; i++)
                vertex.push_back(buildFace(i,j,x,n,points,1));

    //face x=0
    points= vector<shared_ptr<V3D>>((y+1)*(z+1));
    t=0;for(auto e=edgZ0X0.begin(); e!=edgZ0X0.end(); e++)points[t++]= *e;
    t=0;for(auto e=edgZDX0.begin(); e!=edgZDX0.end(); e++)points[z*(y+1)+t++]= *e;
    t=1;for(auto e=++edgY0X0.begin(); e!=edgY0X0.end(); e++)points[(y+1)*t++]= *e;
    t=1;for(auto e=++edgYHX0.begin(); e!=edgYHX0.end(); e++)points[(y+1)*(++t)-1]= *e;
    for(unsigned j=1; j<z; j++)
            for(unsigned i=1; i<y; i++)
                points[i+j*(y+1)]= make_shared<V3D>(V3D(0,iy*i,iz*j, 0));

    n= make_shared<V3D>(V3D(-1,0,0,0));
    for(unsigned j=0; j<z; j++)
            for(unsigned i=0; i<y; i++)
                vertex.push_back(buildFace(i,j,y,n,points,1));
    //face x=w
    points= vector<shared_ptr<V3D>>((y+1)*(z+1));
    t=0;for(auto e=edgZ0XW.begin(); e!=edgZ0XW.end(); e++)points[t++]= *e;
    t=0;for(auto e=edgZDXW.begin(); e!=edgZDXW.end(); e++)points[z*(y+1)+t++]= *e;
    t=1;for(auto e=++edgY0XW.begin(); e!=edgY0XW.end(); e++)points[(y+1)*t++]= *e;
    t=1;for(auto e=++edgYHXW.begin(); e!=edgYHXW.end(); e++)points[(y+1)*(++t)-1]= *e;
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
