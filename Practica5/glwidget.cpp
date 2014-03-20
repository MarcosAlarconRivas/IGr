#include "glwidget.h"

static const double k = 4;

static V3D vivain0(double t){
    return V3D(1+cos(t), sin(t), 2*sin(t/2), 1)*k;
}
static V3D vivain1(double t){
    return V3D(-sin(t), cos(t), cos(t/2), 1)*k;
}
static V3D vivain2(double t){
    return V3D(-cos(t), -sin(t), sin(t/2)/2, 1)*k;
}
static V3D rusa0(double t){
    return V3D(3*cos(t), 2*cos(1.5*t), 3*sin(t))*k;
}
static V3D rusa1(double t){
    return V3D(-3*sin(t), -3*sin(1.5*t), 3*cos(t))*k;
}
static V3D rusa2(double t){
    return V3D(-3*cos(t), -4.5*cos(1.5*t), -3*sin(t))*k;
}


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent){

    setAutoFillBackground(false);
    setFocusPolicy(Qt::ClickFocus);
    setFocus();

    t=0;
    //crear los objetos de la escena
    //tubo= new Extrusion(3, 6, &vivain0, &vivain1, &vivain2, 33);
    tubo= new Extrusion(3, 6, &rusa0, &rusa1, &rusa2, 66, 0, 4*M_PI);
    //tubo= new Extrusion(3, 6, &rusa0, 66, 0, 4*M_PI);
}

GLWidget::~GLWidget(){
    delete tubo;
}

void GLWidget::initializeGL(){
    glClearColor(0.6,0.7,0.8,1.0);
    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
    //   glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);   //Defecto

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Cámara
    eye[0]=eye[1]=eye[2] =100;
    look[0]=look[1]=look[2]=0;
    up[0]=0; up[1]=1; up[2]=0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);

    //Volumen de vista
    N=1; F=1000; zoom=12;

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

    //Axis draw
    glBegin(GL_LINES);
          glColor4f(1, 0, 0, 1);
          glVertex3f(  0, 0, 0);
          glVertex3f(100, 0, 0);
          glColor4f(0, 1, 0, 1);
          glVertex3f( 0,   0, 0);
          glVertex3f( 0, 100, 0);
          glColor4f(0, 0, 1, 1);
          glVertex3f( 0, 0,  0);
          glVertex3f( 0, 0, 100);
    glEnd();

    glColor4f(0, 0, 0, 1);
    tubo->paint(0);

    auto esfera=gluNewQuadric();
    glColor4f(1, 1, 0, .3);
    glPushMatrix();
        V3D tr= rusa0(t);
        glTranslatef(tr[0], tr[1], tr[2]);
        gluQuadricDrawStyle(esfera, GLU_FILL);
        gluSphere(esfera, .3, 30, 30);
    glPopMatrix();
/*    glColor4f(0, 0, 1, .3);
    glPushMatrix();
        tr= vivain0(t);
        glTranslatef(tr[0], tr[1], tr[2]);
        gluQuadricDrawStyle(esfera, GLU_FILL);
        gluSphere(esfera, .3, 30, 30);
    glPopMatrix();*/
    gluDeleteQuadric(esfera);
}

void GLWidget::aplyView(){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     float z= 2*zoom;
     GLdouble x= width()/z, y= height()/z;
     glOrtho(-x, x,-y, y, N, F);
     glMatrixMode(GL_MODELVIEW);
}

void GLWidget::resizeGL(int width, int height){
    //se actualiza puerto de vista
    glViewport(0,0,width,height);

    aplyView();
}

void GLWidget::step(){
    t+=.01;
    if(t>4*M_PI)t-=4*M_PI;
    repaint();
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

            case Qt::Key_4 :
                        //glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        gluLookAt(eye[0]-=20, eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);
                        break;

            case Qt::Key_5 :
                        //glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        gluLookAt(eye[0]+=20, eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);
                        break;

            case Qt::Key_6 :
                        //glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        gluLookAt(eye[0]-=20, eye[1]-=20, eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);
                        break;

            case Qt::Key_7 :
                        //glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        gluLookAt(eye[0]+=20, eye[1]+=20, eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);
                        break;

            case Qt::Key_8 :
                        //glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        gluLookAt(eye[0]-=20, eye[1], eye[2]-=20, look[0], look[1], look[2], up[0], up[1], up[2]);
                        break;

            case Qt::Key_9 :
                        //glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        gluLookAt(eye[0], eye[1], eye[2]+=20, look[0], look[1], look[2], up[0], up[1], up[2]);
                        break;

            case Qt::Key_0 :
                        //glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        eye[0]=eye[1]=eye[2]=100;
                        gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);
                        break;

            default:   return;
    }
    repaint();
}

