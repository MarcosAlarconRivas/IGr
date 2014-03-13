#include "glwidget.h"
#include "window.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent){

    setAutoFillBackground(false);
    setFocusPolicy(Qt::ClickFocus);
    setFocus();

    //Color de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //crear los objetos de la escena
    esfera=gluNewQuadric();
}

GLWidget::~GLWidget(){
    gluDeleteQuadric(esfera);
}

void GLWidget::initializeGL(){
    glClearColor(0.6,0.7,0.8,1.0);
    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);   //Defecto

    //Cámara
    eye[0]=eye[1]=eye[2] =100;
    look[0]=look[1]=look[2]=0;
    up[0]=0; up[1]=1; up[2]=0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);

    //Volumen de vista
    N=1; F=1000; zoom=20;

    //Luz0
    glEnable(GL_LIGHT0);
    GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    GLfloat PosicionLuz0[]={25.0, 25.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Dibujo de la esfera blanca
    glColor3f(1.0, 1.0, 1.0);
    gluQuadricDrawStyle(esfera, GLU_FILL);
    gluSphere(esfera, 3, 30, 30);

}

void GLWidget::aplyView(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLdouble x= .5*width()/zoom, y= .5*height()/zoom;
    glOrtho(-x, x, -y, y, N, F);
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

void GLWidget::keyPressEvent(QKeyEvent *e){
    int key= e->key();
    switch(key){

            case Qt::Key_Plus :
                        zoom*=1.1;
                        aplyView();
                        break;

            case Qt::Key_Minus :
                        zoom/=1.1;
                        aplyView();
                        break;

            default:   return;
    }
    repaint();
}

