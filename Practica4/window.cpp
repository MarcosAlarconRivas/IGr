#include "glwidget.h"
#include "window.h"

#include <QtOpenGL>

Window::Window(){
    setWindowTitle(PROG_NAME);

    GLWidget *openGL = new GLWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(openGL);
    setLayout(mainLayout);

}

QSize Window::sizeHint() const{
    return QSize(400, 400);
}


