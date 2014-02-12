#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include "selection.h"
#include "rimage.h"

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
   ~GLWidget();

protected:
    GLfloat x, y;
    GLfloat zoom;
    Selection* selection;
    RImage *currentImage;
    bool frame, fixed_size;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event );

private:
    void aplyView();
    V2d calcle(int x, int y);
    void loadImage(QString name);
    void saveImage();
};

#endif
