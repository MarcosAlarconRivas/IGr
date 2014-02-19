#include "glwidget.h"
#include <QFileDialog> //open file dialog
#include "window.h"
#include "pitagorast.h"

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
    selection=0; currentImage=0; frame=0; fixed_size=0;
}

GLWidget::~GLWidget(){
    delete selection;
    delete currentImage;
}

void GLWidget::initializeGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(currentImage){
        if(fixed_size)
            currentImage->paint();
        else
            currentImage->paint(width(), height());
    }

    if(selection){
          glColor3f(0,1,1);
          selection->paint();
          //degrees display
          V2d pib= selection->pibt();
          renderText(pib.x, pib.y, 0,
                     QString::number(selection->angle(),0,3)+"º",
                     QFont("Arial", 12, QFont::Bold, false) );
    }

    if(frame){
        glColor3f(0,1,0);
        float w= width(), h=height();
        glBegin(GL_LINES);
            glVertex2f( w, 0);
            glVertex2f(-w, 0);
            glVertex2f( 0, h);
            glVertex2f( 0,-h);
        glEnd();
        if(currentImage){
            w= currentImage->size().width()/2;
            h= currentImage->size().height()/2;
            glBegin(GL_LINE_LOOP);
                glVertex2f(-w,-h);
                glVertex2f( w,-h);
                glVertex2f( w, h);
                glVertex2f(-w, h);
            glEnd();
        }
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

void GLWidget::loadImage(QString fileName){
    if(fileName=="")return;
    delete currentImage;
    currentImage = new TImage(fileName);
    QWidget* p= ((QWidget*)parent());
    resize(currentImage->size());
    p->setWindowTitle(fileName);
    //TODO automatice margins (currently 25px)
    p->resize(width()+25,height()+25);
    fixed_size=1;
}

void GLWidget::saveImage(){
    QString fileName =QFileDialog::getSaveFileName(this, tr("Save Image"), "output.png", tr("Images (*.png)"));
    if(fileName=="")return;
    if(currentImage->save(fileName))
        loadImage(fileName);
}

void GLWidget::keyPressEvent(QKeyEvent *e){
    int key= e->key();
    switch(key){

            case Qt::Key_L:
                        loadImage(QFileDialog::getOpenFileName(this,
                                    tr("Open File"),"",tr("Images (*.*)"))
                                  );
                        break;

            case Qt::Key_S :
                        saveImage();
                        break;

            case Qt::Key_Space :
                        frame = !frame;
                        break;

            case Qt::Key_Shift :
                        fixed_size = !fixed_size;
                        break;

            case Qt::Key_0 :
                        if(currentImage && currentImage->angle()){
                            currentImage->resetPosition();
                            ((QWidget*)parent())->setWindowTitle(tr("Practica4"));
                        }
                        break;

            case Qt::Key_T :{
                        PitagorasT tree = PitagorasT(-width()*.1, -height()*.44, width()*.1, -height()*.44);
                        tree.grow(9);
                        tree.paint();
                        delete currentImage;
                        currentImage= new TImage(width(), height());
                        currentImage->updateBuff();

                        break;
            }

            case Qt::Key_Delete :
                    if(currentImage){
                        delete currentImage;
                        currentImage =0;
                        ((QWidget*)parent())->setWindowTitle(tr("Practica4"));
                    }
                    break;


            default:   return;
    }
    delete selection;
    selection=0;
    repaint();
}


V2d GLWidget::calcle(int X, int Y){
    return V2d( x-( width()/2 -X)/zoom,
                y+(height()/2- Y)/zoom);
}

void GLWidget::mousePressEvent(QMouseEvent * event){
    if(!selection && event->button() == Qt::LeftButton)
            selection= new Selection(calcle(event->x(), event->y()));
}

void GLWidget::mouseMoveEvent(QMouseEvent * event ){
    if(! selection)return;
    if(! event->buttons() & Qt::LeftButton)return;
    selection->setV(calcle(event->x(), event->y()));
    repaint();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * event ){
    if(event->button()!=Qt::LeftButton || ! selection)return;

    if(currentImage){
        currentImage->rotate(selection->angle(), selection->cent());
        ((QWidget*)parent())->setWindowTitle(QString::number(currentImage->angle(),0,1)+"º");
    }
    delete selection;
    selection=0;
    repaint();
}
