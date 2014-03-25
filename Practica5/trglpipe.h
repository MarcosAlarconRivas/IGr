#ifndef TRGLPIPE_H
#define TRGLPIPE_H
#include "extrusion.h"

class TrglPipe : public Extrusion{
public:
    TrglPipe(double rad, unsigned sides, V3D(*d0)(double),V3D(*d1)(double),V3D(*d2)(double),
             unsigned cutNum, double t0=0, double tf=2*M_PI){

        vector<v2d> cut= poligon(rad,sides);

        //twist for each inter cut
        double cz= cos(M_PI/sides), sz= sin(M_PI/sides);
       /*Rz[16]={cz,-sz, 0, 0,
                sz, cz, 0, 0,
                 0,  0, 0, 0,
                 0,  0, 0, 1};*/

        double step= (tf-t0)/(cutNum-1)/2;
        vector<v2d> norm = normals(cut);

        float M[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

        double t=t0;
        unsigned numTot= (2*cutNum)-1;//num of cuts+ intercuts
        vertex= vector<vtx_p>(sides*numTot);
        for(unsigned c=0; c<numTot; c++, t+=step){
            frenet(M, d0(t), d1(t), d2(t));
            if(c%2)//twist the cut
                //M*=Rz
                for(int i=0;i<=12;i+=4){
                    float Mi=M[i];
                    M[i]= Mi*cz+M[i+1]*sz;
                    M[i+1]= Mi*(-sz)+ M[i+1]*cz;
                }
            for(unsigned i=0; i<sides; i++){
                float x= cut[i].x;
                float y= cut[i].y;
                V3D p = V3D(x*M[0]+y*M[1]+M[3], x*M[4]+y*M[5]+M[7], x*M[8]+y*M[9]+M[11], 1.0);
                x= norm[i].x;
                y= norm[i].y;
                V3D v = V3D(x*M[0]+y*M[1], x*M[4]+y*M[5], x*M[8]+y*M[9], 0.0);
                vertex[c*sides+i]= make_shared<vtx>(vtx{p,v});
            }
        }

        //trangFaces(e, s, numR)
        face= vector<Face>(sides*cutNum<<2);
        unsigned currF=0;
        for(unsigned c=0; c<cutNum-1; c++){
            unsigned c0s = c*sides;//curent cut
            unsigned c1sp = c0s+sides;//demi-cut
            unsigned c2s = c1sp+sides;//next cut
            for(unsigned p=0; p<sides; p++,c1sp++){
                unsigned p1 = (p+1)%sides;//next point
                //this 4 triangle cover the same area than the quad in quadFaces
                Face*f= &(face[currF++]= Face(3));
                (*f)[0]= vertex[c0s+p ];
                (*f)[1]= vertex[ c1sp ];
                (*f)[2]= vertex[c0s+p1];
                f= &(face[currF++]= Face(3));
                (*f)[0]= vertex[c0s+p ];
                (*f)[1]= vertex[c2s+p ];
                (*f)[2]= vertex[c1sp ];
                f= &(face[currF++]= Face(3));
                (*f)[0]= vertex[ c1sp ];
                (*f)[1]= vertex[c2s+p ];
                (*f)[2]= vertex[c2s+p1];
                f= &(face[currF++]= Face(3));
                (*f)[0]= vertex[c0s+p1];
                (*f)[1]= vertex[ c1sp ];
                (*f)[2]= vertex[c2s+p1];
            }
        }

    }
};
#endif // TRGLPIPE_H
