#include "glwidget.h"

#include <QTimer>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setFixedSize(200, 200);
    setAutoFillBackground(false);
}

void GLWidget::animate()
{
    repaint();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(100,500);
        glVertex2f(500,100);
    glEnd();

}
