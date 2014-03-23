#include "glwidget.h"

static const double k = 2;

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

    gX=gY=gZ=0;
    float I[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    for(int i=0;i<16;i++)
        /*Rot[i]=*/Rx[i]=Ry[i]=Rz[i]=I[i];

    //crear los objetos de la escena
    pipe= new Extrusion(1, 16, &rusa0, &rusa1, &rusa2, 100, 0, 4*M_PI);
    //pipe= new Extrusion(1, 16, &rusa0, 200, 0, 4*M_PI);
    car = new Car(1, .75, 1.5, .2, .1);
    car->setWay(&rusa0, &rusa1, &rusa2);
    car->setChassisCol(0, 1, 0);
    car->setWheelsCol(.5, .5, .5);
}

GLWidget::~GLWidget(){
    delete pipe;
    delete car;
}

void GLWidget::initializeGL(){
    glClearColor(0,0,0,1);//0.6,0.7,0.8,1.0);
    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.1);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);//normal por vertice
    //glShadeModel(GL_FLAT);//normal por cara

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //no pintar caras traseras
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    //Cámara
    eye[0]=eye[1]=eye[2] =100;
    look[0]=look[1]=look[2]=0;
    up[0]=0; up[1]=1; up[2]=0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], up[0], up[1], up[2]);

    //Volumen de vista
    N=1; F=1000; zoom=25;

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

    if(axis){
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
    }

    glPushMatrix();
        glMultTransposeMatrixf(Rx);
        glMultTransposeMatrixf(Ry);
        glMultTransposeMatrixf(Rz);
    /*  glRotated(gX, 1,0,0);
        glRotated(gY, 0,1,0);
        glRotated(gZ, 0,0,1);
    */
        glColor4f(0, 0, 1, 1);
        pipe->paint(full);
        glColor4f(0,1,1,.5);
        if(showN)pipe->paintNormals();

        car->paint(full);

    glPopMatrix();
}

void GLWidget::aplyView(){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     float z= 2*zoom;
     GLdouble x= width()/z, y= height()/z;
     glOrtho(-x, x,-y, y, N, F);
     glMatrixMode(GL_MODELVIEW);
}

void GLWidget::buildRot(int i){
    double _2pi= 2*M_PI;
    if(!i){
        if(gX>_2pi)gX-=_2pi;
        if(gX<0)gX+=_2pi;
        float cx=cos(gX), sx=sin(gX);
        /*
        Rx=float[16]{1,  0,  0, 0,
                     0, cx,-sx, 0,
                     0, sx, cx, 0,
                     0,  0,  0, 1};
        */
        Rx[5] = cx; Rx[6] = -sx;
        Rx[9] = sx; Rx[10]=  cx;

    }else if(i==1){
        if(gY>_2pi)gY-=_2pi;
        if(gY<0)gY+=_2pi;
        float cy=cos(gY), sy=sin(gY);
        /*
        Ry[16]=float{cy, 0, sy, 0,
                      0, 1,  0, 0,
                    -sy, 0, cy, 0,
                      0, 0,  0, 1};
        */
        Ry[0] =  cy; Ry[2] = sy;
        Ry[8] = -sy; Ry[10]= cy;
    }else if(i==2){
        if(gZ>_2pi)gZ-=_2pi;
        if(gZ<0)gZ+=_2pi;
        float cz=cos(gZ), sz=sin(gZ);
        /*
        Rz[16]={cz,-sz, 0, 0,
                sz, cz, 0, 0,
                 0,  0, 0, 0,
                 0,  0, 0, 1};
        */
        Rz[0] = cz; Rz[1] = -sz;
        Rz[4] = sz; Rz[5] =  cz;
    }

    //TODO Calcular Rot=Rx*Ry*Rz

}

void GLWidget::resizeGL(int width, int height){
    //se actualiza puerto de vista
    glViewport(0,0,width,height);

    aplyView();
}

void GLWidget::step(){
    car->advance(.05);
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

            case Qt::Key_Up :
                        gX+=.05;
                        buildRot(0);
                        break;

            case Qt::Key_Down :
                        gX-=.05;
                        buildRot(0);
                        break;

            case Qt::Key_Right :
                        gY+=.05;
                        buildRot(1);
                        break;

            case Qt::Key_Left :
                        gY-=.05;
                        buildRot(1);
                        break;

            case Qt::Key_A :
                        gZ+=.05;
                        buildRot(2);
                        break;

            case Qt::Key_Z :
                        gZ-=.05;
                        buildRot(2);
                        break;

            case Qt::Key_H :
                        full= !full;
                        break;

            case Qt::Key_J :
                        showN= !showN;
                        break;

            case Qt::Key_K :
                        axis= !axis;
                        break;

            default:   return;
    }
    repaint();
}

