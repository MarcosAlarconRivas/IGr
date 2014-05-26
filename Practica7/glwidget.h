#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>
#include <memory>
#include "camera.h"
#include "ball.h"
#include "lamp.h"

using namespace std;

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
   ~GLWidget();

public slots:
    void step();

protected:
    float Rot[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}; //Scene rotation
    bool fill=1, axis=0;
    bool lightAm=1,lightRm=1, fog=0;
    Camera camera;
    unique_ptr<Model> table;
    shared_ptr<Lamp> lamp;
    shared_ptr<Ball> white;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);

private:
    void sceneRot(int axis, double angle);
    int runing=0;
};

#endif
