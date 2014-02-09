#include "rimage.h"
#include <GL/gl.h>

RImage::RImage(QImage* image, float angle0){
    im=image;
    rotation=angle0;
}

RImage::RImage(QString &path):RImage(new QImage(path)){}

RImage::~RImage(){
    delete im;
}

QSize RImage::size(){
    if(im)return im->size();
    return QSize();
}

void RImage::rotate(){
}

void RImage::paint(){
    glDrawPixels(im->width(), im->height(), GL_BGRA,/*GL_RGBA,*/ GL_UNSIGNED_BYTE, im->bits());
}

bool RImage::save(const QString & fileName, const char * format, int quality){
    return im->save(fileName, format, quality);
}
