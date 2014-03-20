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

    t=gX=gY=gZ=0;
    Rot[0]=Rot[5]=Rot[10]=Rot[15]=1;
    Rot[1]=Rot[2]=Rot[3]=Rot[4]=Rot[6]=Rot[7]=Rot[8]=Rot[9]=Rot[11]=Rot[12]=Rot[13]=Rot[14]=0;
    //crear los objetos de la escena
    //tubo= new Extrusion(3, 6, &vivain0, &vivain1, &vivain2, 33);
    //tubo= new Extrusion(3, 6, &rusa0, &rusa1, &rusa2, 66, 0, 4*M_PI);
    tubo= new Extrusion(1, 8, V3D(0,0,0), V3D(10,10,10));
    //tubo= new Extrusion(3, 6, &rusa0, 66, 0, 4*M_PI);
    //tubo= new Extrusion(3, 6, &toro, &toro, &toro, 33);
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

    glPushMatrix();
       /* glRotated(gX, 1,0,0);
        glRotated(gY, 0,1,0);
        glRotated(gZ, 0,0,1);*/
        glMultTransposeMatrixf(Rot);

        glColor4f(0.3, 0.3, 0.3, 1);
        tubo->paint(full);

        auto esfera=gluNewQuadric();
        glColor4f(1, 1, 0, .3);
        glPushMatrix();
            V3D tr= rusa0(t);
            glTranslatef(tr[0], tr[1], tr[2]);
            gluQuadricDrawStyle(esfera, GLU_FILL);
            gluSphere(esfera, .3, 30, 30);
        glPopMatrix();
        /*glColor4f(0, 0, 1, .3);
        glPushMatrix();
            tr= toro(t);
            glTranslatef(tr[0], tr[1], tr[2]);
            gluQuadricDrawStyle(esfera, GLU_FILL);
            gluSphere(esfera, .3, 30, 30);
        glPopMatrix();*/
        gluDeleteQuadric(esfera);
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

static void multM(float* M, float*N,float*R){
    R[0]= M[0] *N[0]+ M[1]*N[4]+ M[2]*N[8] +M[3]*N[12];
    R[1]= M[0] *N[1]+ M[1]*N[5]+ M[2]*N[9] +M[3]*N[13];
    R[2]= M[0] *N[2]+ M[1]*N[6]+ M[2]*N[10]+M[3]*N[14];
    R[3]= M[0] *N[3]+ M[1]*N[7]+ M[2]*N[11]+M[3]*N[15];

    R[4]= M[4] *N[0]+ M[5]*N[4]+ M[6]*N[8] +M[7]*N[12];
    R[5]= M[4] *N[1]+ M[5]*N[5]+ M[6]*N[9] +M[7]*N[13];
    R[6]= M[4] *N[2]+ M[5]*N[6]+ M[6]*N[10]+M[7]*N[14];
    R[7]= M[4] *N[3]+ M[5]*N[7]+ M[6]*N[11]+M[7]*N[15];

    R[8]= M[8] *N[0]+ M[9]*N[4]+ M[10]*N[8] +M[11]*N[12];
    R[9]= M[8] *N[1]+ M[9]*N[5]+ M[10]*N[9] +M[11]*N[13];
    R[10]=M[8] *N[2]+ M[9]*N[6]+ M[10]*N[10]+M[11]*N[14];
    R[11]=M[8] *N[3]+ M[9]*N[7]+ M[10]*N[11]+M[11]*N[15];

    R[12]=M[12]*N[0]+ M[13]*N[4]+ M[14]*N[8] +M[15]*N[12];
    R[13]=M[12]*N[1]+ M[13]*N[5]+ M[14]*N[9] +M[15]*N[13];
    R[14]=M[12]*N[2]+ M[13]*N[6]+ M[14]*N[10]+M[15]*N[14];
    R[15]=M[12]*N[3]+ M[13]*N[7]+ M[14]*N[11]+M[15]*N[15];

}

void GLWidget::buildRot(int i){
    double _2pi= 2*M_PI;
    if(!i){
        if(gX>_2pi)gX-=_2pi;
        if(gX<0)gX+=_2pi;

        float cx=cos(gX), sx=sin(gX);

      Rx[16]={1, 0, 0, 0,
              0,cx,sx, 0,
              0,-sx,cx,0,
              0, 0, 0, 1};

        else if(i==1){
            if(gY>_2pi)gY-=_2pi;
            if(gY<0)gY+=_2pi;

            float cy=cos(gY), sy=sin(gY);

            Ry[16]={cy, 0, sy, 0,
                    0, 1,  0, 0,
                   -sy,0, cy, 0,
                    0, 0, 0, 1};

        }else if(i=2){
            if(gZ>_2pi)gZ-=_2pi;
            if(gZ<0)gZ+=_2pi;

            float cz=cos(gZ), sz=sin(gZ);

           Rz[16]={cz, sz, 0, 0,
                 -sz, cz, 0, 0,
                   0,  0, 0, 0,
                   0,  0, 0, 1};
        }

    float I[16]={1,0,0,0,
                 0,1,0,0,
                 0,0,1,0,
                 0,0,0,1};

    multM(Rx, Ry, I);
    multM( I, Rz, Rot);

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

            case Qt::Key_Up :
                        //gX+=5;
                        gX+=.05;
                        buildRot();
                        break;

            case Qt::Key_Down :
                        //gX-=5;
                        gX-=.05;
                        buildRot();
                        break;

            case Qt::Key_Right :
                        //gY+=5;
                        gY+=.05;
                        buildRot();
                        break;

            case Qt::Key_Left :
                        //gY-=5;
                        gY-=.05;
                        buildRot();
                        break;

            case Qt::Key_A :
                        //gZ+=5;
                        gZ+=.05;
                        buildRot();
                        break;

            case Qt::Key_Z :
                        //gZ-=5;
                        gZ-=.05;
                        buildRot();
                        break;

            case Qt::Key_H :
                        full=1;
                        break;

            case Qt::Key_G :
                        full=0;
                break;

            default:   return;
    }
    repaint();
}

