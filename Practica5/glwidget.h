#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>
#include "extrusion.h"
#include "car.h"

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
   ~GLWidget();

protected:
    GLdouble eye[3], look[3], up[3]; //Camera
    GLdouble zoom, N, F;  //View Volume
    float Rot[16]; //Scene rotation
    bool full=1, showN=0, axis=1;

    Extrusion *pipe;
    Car *car;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);

private:
    void aplyView();
    void sceneRot(int axis, double angle);
};

#endif
