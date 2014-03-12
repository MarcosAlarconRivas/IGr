#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
   ~GLWidget();

protected:
    GLfloat x, y;
    GLfloat zoom;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event );

private:
    void aplyView();
    void calcle(float &x, float &y);
};

#endif
