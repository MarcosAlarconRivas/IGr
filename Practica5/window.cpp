#include "glwidget.h"
#include "window.h"

#include <QtOpenGL>

#define PROG_NAME "Practica5"

Window::Window(){
    setWindowTitle(PROG_NAME);
    GLWidget *openGL = new GLWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(openGL);
    setLayout(mainLayout);

    /*
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), openGL, SLOT(step()));
    timer->start(30);
    */
}

QSize Window::sizeHint() const{
    return QSize(400, 400);
}


