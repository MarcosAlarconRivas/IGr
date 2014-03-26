#ifndef TRGLPIPE_H
#define TRGLPIPE_H
#include "extrusion.h"

class TrglPipe : public Extrusion{
public:
    TrglPipe(double rad, unsigned sides, V3D(*d0)(double),V3D(*d1)(double),V3D(*d2)(double),
             unsigned cutNum, double t0=0, double tf=2*M_PI){

        vector<v2d> cut= poligon(rad,sides);
        vector<v2d> norm = normals(cut);

        float M[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

        //twist for each inter cut
        double cz= cos(M_PI/sides), sz= sin(M_PI/sides);
        double t=t0;
        double step= (tf-t0)/(cutNum-1)/2;
        unsigned numTot= (2*cutNum)-1;//num of cuts+ intercuts
        vertex= vector<vtx_p>(sides*numTot);
        for(unsigned c=0; c<numTot; c++, t+=step){
            frenet(M, d0(t), d1(t), d2(t));
            if(c%2)//twist the cut
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

        //build (triangular) faces
        face= vector<Face>(sides*(cutNum-1)<<2);
        unsigned currF=0;
        for(unsigned c=0; c<numTot-1; c+=2){
            unsigned p0 = c*sides;//curent point
            unsigned p1 = p0+sides;//current point in inter-cut
            unsigned p2 = p1+sides;//next cut, current point
            for(unsigned i=0; i<sides; i++,p0++,p1++,p2++){
                int j = (i==sides-1) ? -i : 1;
                //this 4 trigl covers the same area than the quad in quadFaces
                Face*f= &(face[currF++]= Face(3));
                (*f)[0]= vertex[ p0 ];
                (*f)[1]= vertex[ p1 ];
                (*f)[2]= vertex[p0+j];
                f= &(face[currF++]= Face(3));
                (*f)[0]= vertex[ p0 ];
                (*f)[1]= vertex[ p2 ];
                (*f)[2]= vertex[ p1 ];
                f= &(face[currF++]= Face(3));
                (*f)[0]= vertex[ p1 ];
                (*f)[1]= vertex[ p2 ];
                (*f)[2]= vertex[p2+j];
                f= &(face[currF++]= Face(3));
                (*f)[0]= vertex[p0+j];
                (*f)[1]= vertex[ p1 ];
                (*f)[2]= vertex[p2+j];
            }
        }

    }
};
#endif // TRGLPIPE_H
