#include "window.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Window window;
    window.resize(window.sizeHint());
    window.show();
    return app.exec();
}
