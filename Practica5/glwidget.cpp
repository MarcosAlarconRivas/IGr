#include "glwidget.h"
#include "window.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent){

    setAutoFillBackground(false);
    setFocusPolicy(Qt::ClickFocus);
    setFocus();

    //Color de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicialización del volumen de vista
    zoom=1; x=0; y=0;

    //crear los objetos de la escena
}

GLWidget::~GLWidget(){

}

void GLWidget::initializeGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

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
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     //glOtho2d(a,b,c,d) == glOtrho(a,b,c,d,-1,1)
     glOrtho(x-(width()/2)/zoom, x+(width()/2)/zoom,
             y-(height()/2)/zoom, y+(height()/2)/zoom, -1, 1);
}

void GLWidget::keyPressEvent(QKeyEvent *e){
    int key= e->key();
    switch(key){

            case Qt::Key_Escape:
                    delete this->parent();

            default:   return;
    }
    repaint();
}


void GLWidget::calcle(float &X, float &Y){
    X= x-( width()/2 -X)/zoom;
    Y= y+(height()/2 -Y)/zoom;
}

void GLWidget::mousePressEvent(QMouseEvent * event){

}

void GLWidget::mouseMoveEvent(QMouseEvent * event ){

}

void GLWidget::mouseReleaseEvent(QMouseEvent * event ){

}
