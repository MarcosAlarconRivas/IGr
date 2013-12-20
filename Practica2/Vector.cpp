//Marcos Alarcon Rivas
#pragma hdrstop
#include <math.h>
#include "Vector.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//const static float zero= 0.0000000001;
//---------------------------------------------------------------------------
Vector::Vector(float x0, float y0){
  x=x0;
  y=y0;
}

double Vector::mod()const{
  return std::sqrt(mod2());
}

double Vector::mod2() const {
  return x*x+y*y;
}

Vector Vector::operator * (double k) const {
  return Vector(x*k, y*k);
}

Vector & Vector::operator *= (double k) {
  x*=k; y*=k;
  return *this;
}

double Vector::operator * (const Vector &v) const {
  return x*v.x + y*v.y;
}

Vector Vector::operator % (double mod0) {
  float m = mod();
  if ( m < zero ) return Vector(0,0);
  float r = mod0 / m;
  return Vector(r*x,r*y);
}

//---------------------------------------------------------------------------
