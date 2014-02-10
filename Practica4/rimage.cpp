#include "rimage.h"
#include <GL/gl.h>

RImage::RImage(QImage* image, float angle0){
    im=image;
    rotation=angle0;
    pixmap= new QRgb [im->height()*im->width()];
    int fil =im->height();
    int col =im->width();
    for(int f=0; f<fil; f++)
        for(int c=0; c<col; c++)
            pixmap[f*col+c]=im->pixel(c, fil-f-1);

}

RImage::RImage(QString &path):RImage(new QImage(path)){}

RImage::~RImage(){
    delete im;
    delete pixmap;
}

QSize RImage::size(){
    if(im)return im->size();
    return QSize(0,0);
}

void RImage::rotate(float degr){
    rotation += degr;
    //rotation %= 360;
    int div= rotation/360;
    rotation -= div*360;
}

void RImage::paint(){
    glDrawPixels(im->width(), im->height(), GL_BGRA/*GL_RGB*/, GL_UNSIGNED_BYTE, pixmap/*im->bits()*/);
}

bool RImage::save(const QString & fileName, const char * format, int quality){
    return im->save(fileName, format, quality);
}
