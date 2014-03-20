#ifndef V3D_H
#define V3D_H
#include <math.h>

class V3D {
public:
    float v[4];

    V3D(){
        v[0]=v[1]=v[2]=v[3]=0.0;
    }

    V3D(float x, float y, float z, bool point=0){
      v[0]=x; v[1]=y; v[2]=z; v[3]=point ? 1.0: 0.0;
    }

    inline float& operator [] (const int i){
            return v[i];
    }

    inline float operator [](const int i)const{
        return v[i];
    }

    inline double mod()const{
        float x=v[0], y=v[1], z=v[2];
        return sqrt(x*x+y*y+z*z);
    }

    inline V3D operator % (double m)const{
        double md= mod();
        if(md) m/=md;
        return (*this)*m;
    }

    inline V3D operator + (const V3D w)const{
        return V3D(v[0]+w[0], v[1]+w[1], v[2]+w[2],!(v[3]&&w[3])&&(v[3]||w[3]));
    }

    inline V3D operator - (const V3D w)const{
        return V3D( v[0]-w[0], v[1]-w[1], v[2]-w[2],!(v[3]&&w[3])&&(v[3]||w[3]));
    }

    inline V3D operator ^ (const V3D w)const{
        return V3D(v[1]*w[2] - v[2]*w[1],
                   w[0]*v[2] - v[0]*w[2],
                   v[0]*w[1] - v[1]*w[0],
                             0          )%1;
    }

    inline double operator * (const V3D w)const{
        return v[0]*w[0]+v[1]*w[1]+v[2]*w[2];
    }

    inline V3D operator * (double k)const{
        return V3D(v[0]*k, v[1]*k, v[2]*k, v[3]);
    }

    inline V3D operator / (double k)const{
        return V3D(v[0]/k, v[1]/k, v[2]/k, v[3]);
    }


};

#endif // V3D_H
