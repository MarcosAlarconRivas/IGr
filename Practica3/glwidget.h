#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <list>
#include "circle.h"

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);

public slots:
    void step();

protected:
    GLfloat x, y;
    GLfloat zoom;

    //Selection* selection;
    //list<Ball> pelota;
    std::list<Obstacle*> obstacle;


    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event);
    void calcle(GLfloat& X, GLfloat& Y);

private:
    void aplyView();
};

#endif
