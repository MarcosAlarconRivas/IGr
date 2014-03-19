#ifndef V3D_H
#define V3D_H

class V3D {
public:
    float v[4];

    V3D(){
        v[0]=v[1]=v[2]=v[3]=0.0;
    }

    V3D(float x, float y, float z, bool point){
      v[0]=x; v[1]=y; v[2]=z; v[3]=point ? 1.0: 0.0;
    }

    V3D(float x, float y, bool point):V3D(x,y,0,point){}

    inline float& operator [] (const int i){
            return v[i];
    }

    inline float operator [](const int i)const{
        return v[i];
    }

    inline V3D operator + (const V3D w)const{
        return V3D(v[0]+w[0], v[1]+w[1], v[2]+w[2],!(v[3]&&w[3])&&(v[3]||w[3]));
    }

    inline V3D operator - (const V3D w)const{
        return V3D( v[0]-w[0], v[1]-w[1], v[2]-w[2],!(v[3]&&w[3])&&(v[3]||w[3]));
    }


};

#endif // V3D_H
