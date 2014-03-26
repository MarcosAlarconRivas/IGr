#include "glwidget.h"
#include "trglpipe.h"

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

    //gX=gY=gZ=0;
    float I[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    for(int i=0;i<16;i++)
        Rot[i]=/*Rx[i]=Ry[i]=Rz[i]=*/I[i];

    //crear los objetos de la escena
    //pipe= new Extrusion(1, 16, &rusa0, &rusa1, &rusa2, 100, 0, 4*M_PI);
    //pipe= new Extrusion(1, 16, &rusa0, 100, 0, 4*M_PI);
    pipe= new TrglPipe(1, 16, &rusa0, &rusa1, &rusa2, 50, 0, 4*M_PI);

    car= new Car(1, .75, 1.5, .2, .1);
    car->setWay(&rusa0, &rusa1, &rusa2);
    car->setChassisCol(0, 1, 0);
    car->setWheelsCol(.5, .5, .5);
    car->setT(0);
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
        glMultTransposeMatrixf(Rot);
    /*  glRotated(gX, 1,0,0);
        glRotated(gY, 0,1,0);
        glRotated(gZ, 0,0,1);
    */
        glColor4f(0, 0, 1, 1);
        pipe->paint(full);
        glColor4f(0,1,1,.5);
        if(showN)pipe->paintNormals();

        car->paint(full);
        if(showN)car->paintNormals();

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

void GLWidget::buildRot(int i, double alpha){
    if(!i){
        float cx=cos(alpha), sx=sin(alpha);
        /*
        Rx[16]=float{1,  0,  0, 0,
                     0, cx,-sx, 0,
                     0, sx, cx, 0,
                     0,  0,  0, 1};
         */

        float R5 = cx, R6 = -sx;
        float R9 = sx, R10=  cx;
        //M*=Rx
        /*
         *              m0, m1, m2, m3
         * m4r5+m8r6, m5r5+m9r6, m6r5+m10r6, m7r5+m11r6
         * m4r9+m8r10,m5r9+m9r10,m6r9+m10r10,m7r9+m11r10
         *              m12, m13, m14, m15
        */
        for(int i=0;i<4;i++){
            int a=4+i, b=8+i;
            float Ma=Rot[a];
            Rot[a]=Ma*R5+Rot[b]*R6;
            Rot[b]=Ma*R9+Rot[b]*R10;
        }

    }else if(i==1){
        float cy=cos(alpha), sy=sin(alpha);
        /*
        Ry[16]=float{cy, 0, sy, 0,
                      0, 1,  0, 0,
                    -sy, 0, cy, 0,
                      0, 0,  0, 1};
        */
        float R0 =  cy, R2 = sy;
        float R8 = -sy, R10= cy;
        //M*=Ry
        /*
         * m0r0+m8r2, m1r0+m9r2, m2r0+m10r2, m3r0+m11r2
         *              m4, m5, m6, m7
         * m0r8+m8r10,m1r8+m9r10,m2r8+m10r10,m3r8+m11r10
         *              m12, m13, m14, m15
        */
        for(int i=0;i<4;i++){
            int a=i, b=8+i;
            float Ma=Rot[a];
            Rot[a]=Ma*R0+Rot[b]*R2;
            Rot[b]=Ma*R8+Rot[b]*R10;
        }
    }else if(i==2){
        float cz=cos(alpha), sz=sin(alpha);
        /*
        Rz[16]={cz,-sz, 0, 0,
                sz, cz, 0, 0,
                 0,  0, 0, 0,
                 0,  0, 0, 1};
        */
        float R0 = cz, R1 = -sz;
        float R4 = sz, R5 =  cz;
        //M*=Rz
        /*
         * m0r0+m4r1, m1r0+m5r1, m2r0+m6r1, m3r0+m7r1
         * m0r4+m4r5, m1r4+m5r5, m2r4+m6r5, m3r4+m7r5
         *              m8,  m9,  m10, m11
         *              m12, m13, m14, m15
        */
        for(int i=0;i<4;i++){
            int a=i, b=4+i;
            float Ma=Rot[a];
            Rot[a]=Ma*R0+Rot[b]*R1;
            Rot[b]=Ma*R4+Rot[b]*R5;
        }
    }
}

void GLWidget::resizeGL(int width, int height){
    //se actualiza puerto de vista
    glViewport(0,0,width,height);

    aplyView();
}

/*void GLWidget::step(){
    car->advance(.05);
    repaint();
}*/

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
                        buildRot(0, .1);
                        break;

            case Qt::Key_Down :
                        buildRot(0, -.1);
                        break;

            case Qt::Key_Right :
                        buildRot(1, .1);
                        break;

            case Qt::Key_Left :
                        buildRot(1, -.1);
                        break;

            case Qt::Key_A :
                        buildRot(2, .1);
                        break;

            case Qt::Key_Z :
                        buildRot(2, -.1);
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

            case Qt::Key_W :
                        car->advance( .05);
                        break;

            case Qt::Key_Q :
                        car->advance(-.05);
                        break;

            default:   return;
    }
    repaint();
}

