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
        //~ArbolPitagoras();
        void paint();
        void grow();
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
        static void branch(const Cuadrado& parent, auto_ptr<Cuadrado>&son1, auto_ptr<Cuadrado>&son2);
        static const GLfloat colR[3];//color de la raiz
        static const GLfloat colH[3];//color de las hojas
};
#endif
 