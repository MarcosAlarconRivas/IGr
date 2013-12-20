//Marcos Alarcon Rivas

#ifndef ArbolPitagorasH
#define ArbolPitagorasH
#include <vector>
using namespace std;

#include "Cuadrado.h"
//---------------------------------------------------------------------------
class ArbolPitagoras: private vector< vector<Cuadrado> >{
  public:
        ArbolPitagoras(Cuadrado root);
        void paint();
        void grow(bool randomBranching);
        void prune();
        void select(GLfloat x, GLfloat y);
        void unselect();
        inline unsigned int deep(){
          return size();
        }
        
  protected:
        Cuadrado *selected;
        unsigned int selected_lvl;

        const GLfloat* levelColor(unsigned int level);
        static const GLfloat colR[3];//color de la raiz
        static const GLfloat colH[3];//color de las hojas
        static void divert(const float (&o)[2], float (&p)[2]);
        static void branch(bool randBranch, const Cuadrado& parent,
                 auto_ptr<Cuadrado>&son1, auto_ptr<Cuadrado>&son2);
};
#endif
 