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

    this->SetName("Pactica2");
    this->Caption=this->Name+"-Pelota";

    //Color de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicialización del volumen de vista
    zoom=1;

    //inicialización del puerto de vista
    //ClientWidth=400;
    //ClientHeight=400;

    selection=0;
    pelota= list<Ball>();

    obstacle= list<Obstacle*>();
    obstacle.push_back( new Circle(Vector(50,-30), 20) );
    obstacle.push_back( new Circle(Vector(-10,25), 25) );
   //ostacle.push_back( new Triangle(Vector(30,-30),Vector(100,60),Vector(-10,20)) );
   obstacle.push_back( new Triangle(Vector(-20,-20),Vector(250, 5), Vector(100,60)) );
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormDestroy(TObject *Sender)
{
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);

    // eliminar objetos creados
    delete selection;
    /*delete pelota;
    delete obstacle;*/
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
    X= x - (ClientWidth/2 - X)/zoom;
    Y= y + (ClientHeight/2- Y)/zoom;
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::GLScene()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // comandos para dibujar la escena
  glColor3f(1,1,1);
  for (std::list<Ball>::const_iterator it=pelota.begin();
   it!=pelota.end(); ++it)
     it->paint();

  glColor3f(1,0,0);
  for (std::list<Obstacle*>::const_iterator it=obstacle.begin();
   it!=obstacle.end(); ++it)
     (*it)->paint();

  if(selection){
        glColor3f(0,1,1);
        selection->paint();
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
 void TGLForm2D::step(Ball &pelota, double time){
 if(time<zero)return;
 double speed= pelota.get_speed(); if(speed<zero)return;
 double hitTime = 2;
 Vector p= pelota.get_center(), dir= pelota.get_direction(), normal;

 for(std::list<Obstacle*>::const_iterator it =obstacle.begin();
    it !=obstacle.end(); ++it){
        Vector Nor; double tIn;
        if((*it)->intersection(p, dir, speed, tIn, Nor) && tIn < hitTime
        && tIn> zero){
                normal= Nor; hitTime= tIn;
          }
 }

  if(hitTime == 2){
        pelota.avanza(1);
        return;
  }

  pelota.avanza(hitTime);
  pelota.revota(normal);
  //step(pelota, 1-hitTime);//funciona bien, pero no se pintan todos los rebotes
}
//---------------------------------------------------------------------------
void TGLForm2D::step(){
  if(pelota.empty())return;
  std::list<Ball>::iterator it;
  for (it =pelota.begin(); it !=pelota.end(); ++it)
     step(*it);
}
//---------------------------------------------------------------------------
void TGLForm2D::backward(){
  bool was = timer->Enabled;
  clock(0);
  for (std::list<Ball>::iterator it=pelota.begin();it!=pelota.end(); ++it)
          it->inv_mov();
  clock(was);
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::keyPressed(TObject *Sender, char &Key){

 switch(Key){
 
         case ' ' : if(timer->Enabled)return;
                    step();
                    break;
                    
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

         case '1' : clock(!timer->Enabled);
                    return;

         case '2' : backward();
                    return;

         default:   return;
 }

 GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if(selection)return;
     if(Button)return;
     Vector centro=Vector(X,Y);
     calcle(centro);
     selection= new Selection(centro);
     GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
     if(!selection)return;
     if(!Shift.Contains(ssLeft))return;
     Vector curr= Vector(X,Y);
     calcle(curr);
     selection->setV(curr, timer->Interval/100.0);
     //la flecha que se dibija es el movomieto por decima de segundo
     GLScene();        
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if(Button)return;
     if(!selection)return;
     pelota.push_back(*selection);
     delete selection;
     selection=0;
     GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::timerTimer(TObject *Sender)
{
 clock(0);
 step();
 GLScene();
 clock(1);
}
//---------------------------------------------------------------------------
void TGLForm2D::clock(bool enable){
        if(timer->Enabled ==enable)return;
        if(enable)timer->CleanupInstance();
        timer->Enabled=enable;
}
//---------------------------------------------------------------------------

