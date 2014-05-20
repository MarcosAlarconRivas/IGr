#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>
#include <memory>
#include "camera.h"
#include "ball.h"

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
    Camera camera;
    unique_ptr<Model> scene;
    shared_ptr<Ball> white;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);

private:
    void sceneRot(int axis, double angle);
    V3D up, dir, fall;
    int runing=0;
};

#endif
