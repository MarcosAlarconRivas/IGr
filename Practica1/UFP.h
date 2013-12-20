//Marcos Alarcon Rivas

#ifndef UFPH
#define UFPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "ArbolPitagoras.h"
#include "Cuadrado.h"
#include "Selection.h"

#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------
class TGLForm2D : public TForm
{
__published:	// IDE-managed Components
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


private:	// User declarations
 HDC hdc;
 HGLRC hrc;

 GLfloat x, y; //(x,y) is the ceter of the visibe area
 float zoom;
 ArbolPitagoras * tree;
 Selection * root;

 // métodos privados
 void __fastcall SetPixelFormatDescriptor();
 void __fastcall GLScene();
 void aplyView();
 void calcle(GLfloat& X, GLfloat& Y);
 inline void calcle(point & p){calcle(p[0],p[1]);}

 
 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
