#include "timage.h"

TImage::TImage(QImage* image, float angle0){
    rotation=angle0;
    if(image->format()==QImage::Format_ARGB32)
        im=image;
    else{
        im= new QImage(image->convertToFormat(QImage::Format_ARGB32));
        delete image;
    }
    setup();
}

TImage::TImage(QString &path):TImage(new QImage(path)){}

TImage::TImage(unsigned w, unsigned h):TImage(new QImage(w, h, QImage::Format_ARGB32)){}

TImage::~TImage(){
    delete im;
    glDeleteTextures(1, &txt);
}

void TImage::setup(){
    glDeleteTextures(1, &txt);
    glGenTextures( 1, &txt );
    glBindTexture(GL_TEXTURE_2D, txt);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im->width(), im->height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, im->bits());
    glBindTexture(GL_TEXTURE_2D,0);
}

QSize TImage::size(){
    if(im)return im->size();
    return QSize(0,0);
}

void TImage::rotate(float degr, V2d o){
    rotation += degr;
    //rotation %= 360;
    int div= rotation/360;
    rotation -= div*360;


}

void TImage::resetPosition(){
    rotation = 0;

}


void TImage::paint(unsigned int w, unsigned int h){

    if(!w) w=im->width();
    if(!h) h=im->height();
    int x=w/2, y=h/2;
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    // select our current texture
    glBindTexture(GL_TEXTURE_2D, txt);
    glPushMatrix();
       glLoadIdentity();
       glColor3f(1,1,1);
       //glMultMatrixf(transf);
       glBegin(GL_QUADS);
           glTexCoord2f(0,1); glVertex2f(-x,-y);
           glTexCoord2f(1,1); glVertex2f( x,-y);
           glTexCoord2f(1,0); glVertex2f( x, y);
           glTexCoord2f(0,0); glVertex2f(-x, y);
       glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TImage::readBuffer(unsigned width, unsigned height, V2d orig){
    unsigned nCols= width ? width  : im->width();
    unsigned nRows= height? height : im->height();
    //int x= -nRows/2 + center.x, y= -nCols/2 + center.y;
    int x = orig.x, y = orig.y;
    for(unsigned f=0; f<nRows; ++f){
        uchar* fila= im->scanLine(nRows-f-1);
        glReadPixels(x, y+f, //esquina inferior‐izquierda del bloque,
                    nCols, 1, //tamaño del bloque
                    GL_BGRA, //datos a leer: buffer de color, de
                            //profundidad, componente alpha...
                    GL_UNSIGNED_BYTE, //tipo de los datos
                    fila); //destino
    }
}

void TImage::updateBuff(int glBuff, unsigned width, unsigned height, V2d center){
    if(im&&!width)width=im->width();
    if(im&&!height)height=im->height();
    if(im)delete im;
    im= new QImage(width, height, QImage::Format_ARGB32);
    int b;
    glGetIntegerv(GL_READ_BUFFER, &b);
    glReadBuffer(glBuff);
        readBuffer(width, height, center);
    glReadBuffer(b);

    setup();
}

bool TImage::save(const QString & fileName, const char * format, int quality){
    readBuffer();
    return im->save(fileName, format, quality);
}
