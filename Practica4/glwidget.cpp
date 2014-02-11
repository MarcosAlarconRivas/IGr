#include "glwidget.h"
#include <QFileDialog> //open file dialog

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
    selection=0; currentImage=0;
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

    if(currentImage)
        currentImage->paint();

    if(selection){
          glColor3f(0,1,1);
          selection->paint();
          //degrees display
          renderText(selection->pib.x, selection->pib.y, 0,
                     QString::number(selection->angle(),0,3)+"º",
                     QFont("Arial", 12, QFont::Bold, false) );
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

void GLWidget::loadImage(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Images (*.*)"));
    currentImage = new RImage(fileName);
    QWidget* p= ((QWidget*)parent());
    p->setWindowTitle(fileName);
    QMargins m= p->contentsMargins();
    resize(currentImage->size());
    p->resize(width()+m.right()+m.left(),height()+m.bottom()+m.top());
}

void GLWidget::saveImage(){
    QString fileName =QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png)"));
    //save currentImage to flileName
    if(currentImage->save(fileName)){
        delete currentImage;
        currentImage =0;
        ((QWidget*)parent())->setWindowTitle("Practica 4");
    }
}

void GLWidget::keyPressEvent(QKeyEvent *e){
    int key= e->key();
    switch(key){

            case Qt::Key_Insert :
                        loadImage();
                        break;

            case Qt::Key_S :
                        saveImage();
                        break;

            default:   return;
    }
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
        currentImage->rotate(selection->angle());
        ((QWidget*)parent())->setWindowTitle(QString::number(currentImage->angle(),0,1)+"º");
    }
    delete selection;
    selection=0;
    repaint();
}
