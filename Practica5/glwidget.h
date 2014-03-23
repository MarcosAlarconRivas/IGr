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

/*public slots:
    void step();*/

protected:
    GLdouble eye[3], look[3], up[3]; //Camara
    GLdouble zoom, N, F;  //Volumen de vista
    GLdouble gX, gY, gZ;
    float Rx[16],Ry[16],Rz[16];//,Rot[16];
    bool full=1, showN=0, axis=1;

    Extrusion *pipe;
    Car *car;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);

private:
    void aplyView();
    void buildRot(int i);
};

#endif
