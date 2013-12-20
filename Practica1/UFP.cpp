//Marcos Alarcon Rivas

#include <vcl.h>
#pragma hdrstop

#include "UFP.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
__fastcall TGLForm2D::TGLForm2D(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormCreate(TObject *Sender)
{
    hdc = GetDC(Handle);
    SetPixelFormatDescriptor();
    hrc = wglCreateContext(hdc);
    if(hrc == NULL)
    	ShowMessage(":-)~ hrc == NULL");
    if(wglMakeCurrent(hdc, hrc) == false)
    	ShowMessage("Could not MakeCurrent");

    this->SetName("Pactica1");
    this->Caption=this->Name+"-Arboles de Pitagoras";

    //Color de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicialización del volumen de vista
    zoom=1;

    //inicialización del puerto de vista
    //ClientWidth=400;
    //ClientHeight=400;
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormDestroy(TObject *Sender)
{
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);

    // eliminar objetos creados
    delete tree, root;
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::SetPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
    };
    int PixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, PixelFormat, &pfd);
}
//---------------------------------------------------------------------
void __fastcall TGLForm2D::FormResize(TObject *Sender)
{

 //se actualiza puerto de vista
  glViewport(0,0,ClientWidth,ClientHeight);

  // se actualiza el volumen de vista
  aplyView();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  GLScene();

}
//---------------------------------------------------------------------------
void TGLForm2D::aplyView(){
     GLfloat xRight= x+(ClientWidth /2)/zoom;
     GLfloat xLeft=  x-(ClientWidth /2)/zoom;
     GLfloat yTop=   y+(ClientHeight/2)/zoom;
     GLfloat yBot=   y-(ClientHeight/2)/zoom;
     
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(xLeft,xRight, yBot,yTop);
}
//---------------------------------------------------------------------------
void TGLForm2D::calcle(GLfloat& X, GLfloat& Y){
/*X= xLeft+ X/zoom;
  Y= yTop - Y/zoom;*/
    X= x - (ClientWidth/2 - X)/zoom;
    Y= y + (ClientHeight/2- Y)/zoom;
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::GLScene()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // comandos para dibujar la escena
  if(tree)tree->paint();
  if(root){
   glColor3f(0,1,1);
   root->paint();
  }

  glFlush();
  SwapBuffers(hdc);
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormPaint(TObject *Sender)
{
  GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::keyPressed(TObject *Sender, char &Key){

 switch(Key){
         case '+' : zoom*=1.1;
                    aplyView();
                    break;

         case '-' : zoom/=1.1;
                    aplyView();
                    break;

         case 'w' : y+= 20/zoom;
                    aplyView();
                    break;

         case 's' : y-= 20/zoom;
                    aplyView();
                    break;

         case 'd' : x+= 20/zoom;
                    aplyView();
                    break;

         case 'a' : x-= 20/zoom;
                    aplyView();
                    break;

         case '1' : if(!tree)return;
                    tree->grow();
                    break;

         case '2' : if(!tree)return;
                    tree->prune();
                    break;

         default:   return;
 }

 GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==1){
        if(root)return;
        point curr={X,Y};
        calcle(curr);
        root= new Selection(curr[0], curr[1], curr[0], curr[1]);
    }
    if(Button==0){
       if(!tree)return;
       point curr={X,Y};
       calcle(curr);
       tree->select(curr[0],curr[1]);
       GLScene();
    }
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
     if(!root)return;
     if(!Shift.Contains(ssRight))return;
     point curr={X,Y};
     calcle(curr);
     root->setV1(curr[0], curr[1]);
     GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if(Button!=1)return;
     if(!root)return;
     point curr={X,Y};
     calcle(curr);
     delete tree;
     tree= new ArbolPitagoras(*root);
     delete root;
     root=0;
     GLScene();
}
//---------------------------------------------------------------------------

