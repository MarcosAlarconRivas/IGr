#include "glwidget.h"

#include <QTimer>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent){

    setAutoFillBackground(false);
    setFocusPolicy(Qt::ClickFocus);

    //Color de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicialización del volumen de vista
    zoom=1; x=0; y=0;

    //crear los objetos de las escena
    obstacle= std::list<Obstacle*>();
    obstacle.push_back( new Circle(V2d(-10,-20), 20) );

}

void GLWidget::step(){
    //repaint();
}

void GLWidget::initializeGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);
    for (std::list<Obstacle*>::const_iterator it=obstacle.begin();
     it!=obstacle.end(); ++it)
       (*it)->paint();

    glColor3f(0,1,0);
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
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     //glOtho2d(a,b,c,d) == glOtrho(a,b,c,d,-1,1)
     glOrtho(x-(width()/2)/zoom, x+(width()/2)/zoom,
             y-(height()/2)/zoom, y+(height()/2)/zoom, -1, 1);
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

            case Qt::Key_W :
                        y+= 20/zoom;
                        aplyView();
                        break;

            case Qt::Key_S :
                        y-= 20/zoom;
                        aplyView();
                        break;

            case Qt::Key_D :
                        x+= 20/zoom;
                        aplyView();
                        break;

            case Qt::Key_A :
                        x-= 20/zoom;
                        aplyView();
                        break;

            default:   return;
    }
    repaint();
}

void GLWidget::calcle(GLfloat& X, GLfloat& Y){
    X= x - ( width()/2 -X)/zoom;
    Y= y + (height()/2- Y)/zoom;
}
