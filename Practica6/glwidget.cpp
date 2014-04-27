#include "glwidget.h"
#include "billard.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent){

    setAutoFillBackground(false);
    setFocusPolicy(Qt::ClickFocus);
    setFocus();
}

GLWidget::~GLWidget(){
    //delete scene;
}


void GLWidget::initializeGL(){
    glClearColor(0,0,0,1);
    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.1);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_NORMALIZE);
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
    camera.lookAt(100,100,100);

    //Ligth0
    glEnable(GL_LIGHT0);
    GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    GLfloat PosicionLuz0[]={25.0, 25.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);

    scene=unique_ptr<Model>(new_Billiard(white, dir, fall));
    up = V3D(-fall[0], -fall[1], -fall[2]) % 1;

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
        scene->render(full);
    glPopMatrix();
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
    if(runing<1)return;

    if(runing<100)
        white->slide(dir, .01);
    else
        white->slide(fall, .05);

    if(++runing>120)runing=-1;

    repaint();
}

void GLWidget::keyPressEvent(QKeyEvent *e){
    int key= e->key();
    switch(key){
            //Zoom
            case Qt::Key_Plus :
                        camera.Zoom(1.1);
                        break;
            case Qt::Key_Minus :
                        camera.Zoom(1/1.1);
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
                        camera.yaw(-.1);
                        break;
            case Qt::Key_K :
                        camera.yaw( .1);
                        break;
            case Qt::Key_N :
                        camera.pitch(-.1);
                        break;
            case Qt::Key_M :
                        camera.pitch( .1);
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
                        camera.lookAt(100,100,100);
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
            //Perspectives
            case Qt::Key_O :
                        camera.Orthogonal();
                        break;
            case Qt::Key_P :
                        camera.Perspective();
                        break;
            case Qt::Key_Ntilde :
                        camera.Oblique(V3D(0,.1,.9));
                        break;

            //Scene settings
            case Qt::Key_Shift :
                        full = !full;
                        break;
            case Qt::Key_0 :
                        axis= !axis;
                        break;

            //Ball move
            case Qt::Key_F1 :
                        if(runing){
                            runing=0;
                            white->restore();
                        }else
                           runing=1;
                        break;

             //Scene transformations
             case Qt::Key_F9  :
                        scene->translate(-2,0,0);
                        break;
             case Qt::Key_F10 :
                        scene->rotate(1, 0,0,1);
                        break;
             case Qt::Key_F11:
                        scene->scale(1,1.1,1);
                        break;
             case Qt::Key_F12:
                        scene->reset();
                        break;


            default:   return;
    }
    repaint();
}
