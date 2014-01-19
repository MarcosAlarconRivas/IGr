#include "glwidget.h"
#include "window.h"

#include <QTimer>
#include <QtOpenGL>

Window::Window(){
    setWindowTitle(tr("openGL Widget"));

    GLWidget *openGL = new GLWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(openGL);
    setLayout(mainLayout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), openGL, SLOT(step()));
    timer->start(50);

}

QSize Window::sizeHint() const{
    return QSize(400, 400);
}


