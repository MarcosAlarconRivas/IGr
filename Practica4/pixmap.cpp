#include "pixmap.h"
#include "GL/gl.h"
//#include <QtOpenGL>

PixMap::PixMap(unsigned cols, unsigned rows){
    // b = 3;
    r = rows; c = cols;
    map = new rgb[c*r];

}

PixMap::PixMap(QPixmap &qpm){
    c = qpm.height();
    r = qpm.width();

   /* qpm.data_ptr()

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "JPG");

    std::vector<unsigned char[3]> c(buffer.constData(), buffer.constData() + buffer.size());
    map = c;*/

}

PixMap::~PixMap(){
    delete[] map;
}

void PixMap::paint(){
    if(!map)return;

    glDrawPixels(c, r, //tamaño del bloque
                GL_RGB,  //datos a escribir: buffer de color, de profundidad, componente alpha...
                GL_UNSIGNED_BYTE,//tipo de los datos
                 map); //origen

}
