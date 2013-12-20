//Marcos Alarcon Rivas
#ifndef VectorH
#define VectorH
#include <cmath>
//---------------------------------------------------------------------------
#define zero 0.000000001
//const double zero = 0.000000001;
class Vector{
  public:
        float x,y;

        Vector(const Vector & v) { x=v.x; y=v.y; }

        Vector(){ x=0; y=0; }

        Vector(float x0, float y0);

        Vector & operator = (const Vector &v) { x=v.x; y=v.y; return *this; }

        double mod() const;

        double mod2() const;

        inline Vector unitario(){
                return (*this) % 1;
        }

        inline bool operator == (const Vector &v) const{
                return  zero<std::abs(x -v.x)&& zero<std::abs(y - v.y);
        }

        inline bool operator != (const Vector &v) const{
                return !(*this == v);
        }

        inline Vector operator + (const Vector &v) const{
                return Vector(x+v.x, y+v.y);
        }

        inline Vector & operator += (const Vector &v){
                x+= v.x; y+=v.y;
                return *this;
        }

        inline Vector operator - (const Vector &p) const{
                return Vector( x-p.x, y-p.y );
        }

        inline Vector & operator -= (const Vector &v){
                x-= v.x; y-=v.y;
                return *this;
        }

        Vector operator % (double mod0);

        inline Vector & operator %= (double mod){
                *this = *this % mod;
                return *this;
        }

        Vector operator * (double k) const;

        Vector & operator *= (double k);

        double operator * (const Vector &v) const;

        inline Vector & operator ++ (){
                float ax = x; x= (-y); y= ax;
                return *this;
        }

        inline Vector & operator -- (){
                float ax = x; x= y; y= (-ax);
                return *this;
        }
        
        inline Vector operator | (const Vector &p) const{
                return Vector((x + p.x)/2, (y+p.y)/2);
        }

        inline bool operator & (const Vector &v) const{
                return !(zero< std::abs((*this)*v));
        }

};
//---------------------------------------------------------------------------
#endif
