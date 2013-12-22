#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class Helper;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent);

public slots:
    void animate();

protected:
    void paintGL();

};

#endif
