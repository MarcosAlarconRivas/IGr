#include "glwidget.h"

#include <QTimer>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent){
    setAutoFillBackground(false);

    //Color de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicialización del volumen de vista
    zoom=1; x=0; y=0;

}

void GLWidget::animate(){
    repaint();
}

void GLWidget::initializeGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(100,500);
        glVertex2f(500,100);
    glEnd();

}

void GLWidget::resizeGL(int width, int height){

    //se actualiza puerto de vista
     glViewport(0,0,width,height);

     // se actualiza el volumen de vista
     aplyView();

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     paintGL();
}

void GLWidget::aplyView(){
     int ClientWidth= this->width();
     int ClientHeight= this->height();
     GLfloat xRight= x+(ClientWidth /2)/zoom;
     GLfloat xLeft=  x-(ClientWidth /2)/zoom;
     GLfloat yTop=   y+(ClientHeight/2)/zoom;
     GLfloat yBot=   y-(ClientHeight/2)/zoom;

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     //gluOrtho2D(xLeft,xRight, yBot,yTop);
     glOrtho(xLeft, xRight, yBot, yTop, -1, 1);
}
