#include "glwidget.h"
#include "billard.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent){

    setAutoFillBackground(false);
    setFocusPolicy(Qt::ClickFocus);
    setFocus();
}

GLWidget::~GLWidget(){}

void GLWidget::initializeGL(){
    glClearColor(0,0,0,1);
    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    //glMaterialf(GL_FRONT, GL_SHININESS, 0.1);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //FOG
    GLfloat fogCol[]={.8, .8, .8, .3};
    glFogfv(GL_FOG_COLOR, fogCol);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_DENSITY, .5);
    glFogf(GL_FOG_START, 10);
    glFogf(GL_FOG_END, 100);


    glDisable(GL_NORMALIZE);
    //glEnable(GL_NORMALIZE);
    //glShadeModel(GL_SMOOTH);//a normal for each vertex
    //glShadeModel(GL_FLAT);//a normal for each face

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //do not paint back faces
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    //Camera
    camera.setZoom(30);
    camera.setWindow(width(),height());
    camera.setVolume(1, 1000);
    camera.lookAt(50,50,50);

    //Ligth0
    glEnable(GL_LIGHT0);
    GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    GLfloat PosicionLuz0[]={50.0, 50.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);
    GLfloat DireccionLuz0[]={0.0, -1.0, -1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, DireccionLuz0);

    table=unique_ptr<Model>(new_Billiard(white, lamp));

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
        //Rotate scene
        glMultTransposeMatrixf(Rot);
        //Draw scene
        table->render(fill);
    glPopMatrix();
    lamp->render(fill);
}

void GLWidget::sceneRot(int i, double alpha){
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
    glViewport(0,0,width,height);//View port update

    camera.setWindow(width,height);//View volume
}

void GLWidget::step(){
    if(!white->defaultMove(runing))return;
    repaint();
}

void GLWidget::keyPressEvent(QKeyEvent *e){
    int key= e->key();
    switch(key){
            //Zoom
            case Qt::Key_Plus :
                        camera.Zoom(1/1.1);
                        break;
            case Qt::Key_Minus :
                        camera.Zoom(1.1);
                        break;

            //Scene Rotations
            case Qt::Key_Up :
                        sceneRot(0, .1);
                        break;
            case Qt::Key_Down :
                        sceneRot(0, -.1);
                        break;
            case Qt::Key_Right :
                        sceneRot(1, .1);
                        break;
            case Qt::Key_Left :
                        sceneRot(1, -.1);
                        break;
            case Qt::Key_A :
                        sceneRot(2, .1);
                        break;
            case Qt::Key_Z :
                        sceneRot(2, -.1);
                        break;

            //Camera Rotations
            case Qt::Key_U :
                        camera.roll(-.1);
                        break;
            case Qt::Key_I :
                        camera.roll( .1);
                        break;
            case Qt::Key_J :
                        camera.yaw(-.01);
                        break;
            case Qt::Key_K :
                        camera.yaw( .01);
                        break;
            case Qt::Key_N :
                        camera.pitch(-.01);
                        break;
            case Qt::Key_M :
                        camera.pitch( .01);
                        break;

            //Translation
            case Qt::Key_E :
                        camera.travel(-5,0,0);
                        break;
            case Qt::Key_R :
                        camera.travel( 5,0,0);
                        break;
            case Qt::Key_D :
                        camera.travel(0,-5,0);
                        break;
            case Qt::Key_F :
                        camera.travel(0, 5,0);
                        break;
            case Qt::Key_C :
                        camera.travel(0,0,-5);
                        break;
            case Qt::Key_V :
                        camera.travel(0,0, 5);
                        break;
            case Qt::Key_1 :
                        camera.orbitX(.1);
                        break;
            case Qt::Key_2 :
                        camera.orbitY(.1);
                        break;
            case Qt::Key_3 :
                        camera.orbitZ(.1);
                        break;

            //Camera positions
            case Qt::Key_Space :
                        camera.lookAt(50,50,50);
                        camera.setZoom(30);
                        break;
            case Qt::Key_4 :
                        camera.side(100);
                        break;
            case Qt::Key_5 :
                        camera.front(100);
                        break;
            case Qt::Key_6 :
                        camera.top(100);
                        break;
            case Qt::Key_7 :
                        camera.oposed();
                        break;

            //Scene settings
            case Qt::Key_Shift :
                        fill = !fill;
                        break;
            case Qt::Key_0 :
                        axis= !axis;
                        break;
            case Qt::Key_Control:
                        if(fog= !fog)
                            glEnable(GL_FOG);
                        else
                            glDisable(GL_FOG);
                        break;

            //Ball move
            case Qt::Key_F1 :
                        if(runing){
                            runing=0;
                            white->restore();
                        }else
                           runing=1;
                        break;

             //Ligths
            case Qt::Key_F2:
                    lamp->scale(1,1,.9);
                    break;
            case Qt::Key_F3:
                    lamp->scale(1,1,1/.9);
                    break;
            case Qt::Key_F4:
                    lamp->translate(0,0,-1);
                    lamp->set_light();
                    break;
            case Qt::Key_F5:
                    lamp->translate(0,0, 1);
                    lamp->set_light();
                    break;
            case Qt::Key_F6:
                    lamp->translate(0,-1,0);
                    lamp->set_light();
                    break;
            case Qt::Key_F7:
                    lamp->translate(0, 1,0);
                    lamp->set_light();
                    break;
            case Qt::Key_F8:
                    lamp->translate(-1,0,0);
                    lamp->set_light();
                    break;
            case Qt::Key_F9:
                    lamp->translate( 1,0,0);
                    lamp->set_light();
                    break;
            case Qt::Key_F10:
                    lamp->lightSwich();
                    break;
            case Qt::Key_8:
                    lamp->intensity(.05);
                    break;
            case Qt::Key_9:
                    lamp->intensity(-.05);
                    break;
            case Qt::Key_F11:
                        if(lightAm){
                            float black[3]={0,0,0};
                            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
                            lightAm=0;
                        }else{
                            float grey[3]={.2,.2,.2};
                            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, grey);
                            lightAm=1;
                        }
                        break;
            case Qt::Key_F12:
                        if(lightRm = !lightRm)glEnable(GL_LIGHT0);
                        else glDisable(GL_LIGHT0);
                        break;

            default:   return;
    }
    repaint();
}

static bool aprox(float a, float b){
    if(a==b)return 1;
    if(!a || !b)return 0;
    float d= a/b;
    return d<1.2 && d>.8;
}

void GLWidget::mouseReleaseEvent(QMouseEvent * event){
    if(event->button()!=Qt::LeftButton)return;
    GLint x = event->x(), y = event->y();
    float data[4] = {0, 0, 0, 0};
    glReadPixels (x, height() - y, 1, 1, GL_RGBA, GL_FLOAT, &data);
    int i;
    float chalk0[4]= {.3, 0, .5, 1};
    for(i=0; i<4; i++)
        if(!aprox(data[i],chalk0[i]))break;

    if(i<4){
        float chalk1[4]= {0, .2, 1, 1};
        for(i=0; i<4; i++)
            if(!aprox(data[i],chalk1[i]))break;
    }

    if(i==4){
        lamp->lightSwich();
        repaint();
    }

}
