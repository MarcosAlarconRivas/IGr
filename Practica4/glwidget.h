#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include "selection.h"
#include "timage.h"

#define PROG_NAME "Practica4"

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
   ~GLWidget();

protected:
    GLfloat x, y;
    GLfloat zoom;
    Selection* selection;
    TImage *currentImage;
    bool frame, fixed_size;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event );

private:
    QString deffParntTit;
    void setTitle(QString s=PROG_NAME);
    void aplyView();
    V2d calcle(int x, int y);
    void loadImage(QString name);
    void saveImage();
};

#endif
