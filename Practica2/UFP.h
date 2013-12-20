//Marcos Alarcon Rivas
#ifndef UFPH
#define UFPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <list.h>

#include <gl\gl.h>
#include <gl\glu.h>

#include "Triangle.h"
#include "Quadrangle.h"
#include "Ball.h"
#include "Circle.h"
#include "Selection.h"

//---------------------------------------------------------------------------
class TGLForm2D : public TForm
{
__published:	// IDE-managed Components
  TTimer *timer;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall keyPressed(TObject *Sender, char &Key);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall timerTimer(TObject *Sender);

private:	// User declarations
 HDC hdc;
 HGLRC hrc;

 GLfloat x, y; //(x,y) is the ceter of the visibe area
 float zoom;

 Selection* selection;
 list<Ball> pelota;
 list<Obstacle*> obstacle;

 // métodos privados
 void __fastcall SetPixelFormatDescriptor();
 void __fastcall GLScene();
 void aplyView();
 void calcle(GLfloat& X, GLfloat& Y);
 inline void calcle(Vector &punto){calcle(punto.x, punto.y);}
 void step();
 void step(Ball &pelota, double time=1);
 void backward();
 void clock(bool enable);
 
 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
