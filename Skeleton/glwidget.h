#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
//#include <GL/gl.h>
//#include <GL/glu.h>

class Helper;

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);

public slots:
    void animate();

protected:
    GLfloat x, y;
    GLfloat zoom;
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void aplyView();
};

#endif
