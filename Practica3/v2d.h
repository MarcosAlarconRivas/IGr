#ifndef V2D_H
#define V2D_H
#include <cmath>
#define zero 0.000000001
class V2d{
public:
    //Atributes
    //static const double zero = 0.000000001;
    float x, y;

    //Constructors
    V2d(){}
    V2d(const V2d & v) { x=v.x; y=v.y; }
    V2d(float x0, float y0) { x=x0; y=y0; }

    //Geters
    inline double mod()const{
      return sqrt(mod2());
    }

    inline double mod2() const {
      return x*x+y*y;
    }

    //Operators
    inline bool operator == (const V2d &v) const{
            return  zero< std::abs(x -v.x)&& zero< std::abs(y - v.y);
    }

    inline bool operator != (const V2d &v) const{
            return !(*this == v);
    }

    inline V2d operator + (const V2d &v) const{
            return V2d(x+v.x, y+v.y);
    }

    inline V2d & operator += (const V2d &v){
            x+= v.x; y+=v.y;
            return *this;
    }

    inline V2d operator - (const V2d &p) const{
            return V2d( x-p.x, y-p.y );
    }

    inline V2d & operator -= (const V2d &v){
            x-= v.x; y-=v.y;
            return *this;
    }

    inline V2d operator * (double k) const {
            return V2d(x*k, y*k);
    }

    inline V2d & operator *= (double k) {
            x*=k; y*=k;
            return *this;
    }

    inline double operator * (const V2d &v) const {
            return x*v.x + y*v.y;
    }

    inline V2d operator % (double mod0) {
            float m = mod();
            if ( m < zero ) return V2d(0,0);
            float r = mod0 / m;
            return V2d(r*x,r*y);
    }

    inline V2d & operator %= (double mod){
            *this = *this % mod;
            return *this;
    }

    inline V2d operator | (const V2d &p) const{
            return V2d((x + p.x)/2, (y+p.y)/2);
    }

    inline bool operator & (const V2d &v) const{
            return !(zero< std::abs((*this)*v));
    }

    //Rotations
    inline V2d & operator ++ (){
            float ax = x; x= (-y); y= ax;
            return *this;
    }

    inline V2d & operator -- (){
            float ax = x; x= y; y= (-ax);
            return *this;
    }

};
#endif // V2D_H
