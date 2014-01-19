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

    //crear los objetos de la escena
    selection=0;
    pelota= std::list<Ball>();
    obstacle= std::list<Obstacle*>();
    obstacle.push_back( new Circle(V2d(-10,-20), 20) );
    obstacle.push_back( new Triangle(V2d(0,0), V2d(50,300), V2d(300,50)) );
    obstacle.push_back( new Ellipse(V2d(-45,45), 20, 50, -22.5) );

}

GLWidget::~GLWidget(){
    delete selection;
}

void GLWidget::step(){
    if(pelota.empty())return;
    std::list<Ball>::iterator it;
    for (it =pelota.begin(); it !=pelota.end(); ++it)
       step(*it);

    repaint();
}

void GLWidget::initializeGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    // comandos para dibujar la escena
    glColor3f(1,1,1);
    for (std::list<Ball>::const_iterator it=pelota.begin();
     it!=pelota.end(); ++it)
       it->paint();

    glColor3f(1,0,0);
    for (std::list<Obstacle*>::const_iterator it=obstacle.begin();
     it!=obstacle.end(); ++it)
       (*it)->paint();

    if(selection){
          glColor3f(0,1,1);
          selection->paint();
    }

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

            case Qt::Key_Space:
                       backward();
                       return;

            default:   return;
    }
    repaint();
}

V2d GLWidget::calcle(int X, int Y){
    return V2d( x-( width()/2 -X)/zoom,
                y+(height()/2- Y)/zoom);
}

void GLWidget::mousePressEvent(QMouseEvent * event){
    if(event->button() != Qt::LeftButton)return;
    if(selection)return;
    selection= new Selection(calcle(event->x(), event->y()));
    repaint();
}

void GLWidget::mouseMoveEvent(QMouseEvent * event ){
    if(! selection)return;
    if(! event->buttons() & Qt::LeftButton)return;
    selection->setV(calcle(event->x(), event->y()), .2 );
        //el segundo argumento ajusta la velocidad
    repaint();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * event ){
    if(event->buttons())return;
    if(event->button()==Qt::LeftButton && selection)
        pelota.push_back(*selection);
    delete selection;
    selection=0;
    repaint();
}

void GLWidget::backward(){
    for (std::list<Ball>::iterator it=pelota.begin();it!=pelota.end(); ++it)
        it->inv_mov();
}

void GLWidget::step(Ball& pelota){
    if(pelota.s()<zero)return;
    double hitTime = 2;
    V2d normal;

    for(std::list<Obstacle*>::const_iterator it =obstacle.begin();
       it !=obstacle.end(); ++it){
           V2d Nor; double tIn;
           if( pelota.hit(**it, tIn, Nor)&& tIn < hitTime && tIn > zero){
                  normal= Nor; hitTime= tIn;
             }
    }

     if(hitTime == 2){
           pelota.advance();
           return;
     }

     pelota.advance(hitTime);
     pelota.revota(normal);
}
