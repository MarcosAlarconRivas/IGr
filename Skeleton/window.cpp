#include "glwidget.h"
#include "window.h"

#include <QTimer>

Window::Window()
{
    setWindowTitle(tr("openGL Widget"));

    GLWidget *openGL = new GLWidget(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
    timer->start(50);
}
