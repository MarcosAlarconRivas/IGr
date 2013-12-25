#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <list>
#include "triangle.h"
#include "circle.h"
#include "ball.h"
#include "selection.h"

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);
    ~GLWidget();

public slots:
    void step();

protected:
    GLfloat x, y;
    GLfloat zoom;

    Selection* selection;
    std::list<Ball> pelota;
    std::list<Obstacle*> obstacle;

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
};

#endif
