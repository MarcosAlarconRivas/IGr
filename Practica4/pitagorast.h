#ifndef PITAGORAST_H
#define PITAGORAST_H

#include <vector>

using namespace std;

typedef struct{
    float x[4];
    float y[4];
} cuadrado;

class PitagorasT:private vector< vector<cuadrado> >{
public:
    PitagorasT(float x0, float y0, float x1, float y1);
    void paint()const;
    void grow(unsigned lvls=1);

protected:
    float* levelColor(unsigned int level)const;
    static const float colR[3];//color de la raiz
    static const float colH[3];//color de las hojas
    static void branch(const cuadrado& p, cuadrado* &s1, cuadrado* &s2);
    static cuadrado* new_cuadrado(float x0, float y0, float x1, float y1);
};

#endif // PITAGORAST_H
