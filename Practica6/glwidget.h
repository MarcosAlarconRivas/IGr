#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>
#include <camera.h>
#include <extrusion.h>
#include <cuboid.h>

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
   ~GLWidget();

protected:
    float Rot[16]; //Scene rotation
    bool full=1, axis=1;
    Camera camera= Camera();

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);

private:
    void aplyView();
    void sceneRot(int axis, double angle);
};

#endif
