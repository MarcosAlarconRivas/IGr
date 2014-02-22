#include "timage.h"
#include <cmath>

TImage::TImage(QImage* image){
    transf=0;
    resetPosition();

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

/*static float* multMx(float m1[16], float m2[16]){
    float* r = new float[16];
    int pos=0;
    for(int f=0; f<16; f+=4)
        for(int c=0; c<4; c++)
            r[pos++]= m1[f]*m2[c] +m1[f+1]*m2[c+4] +m1[f+2]*m2[c+8] +m1[f+3]*m2[c+12];

    delete m1;
    delete m2;
    return r;
}*/

void TImage::rotate(float deg, V2d o){
    rotation += deg;
    rotation -= 360*((int)rotation/360);

    double rad= M_PI * deg/180;
    float x= o.x, y= o.y;
    float s= sin(rad), c= cos(rad);

    /*transf = multMx(new float[16]
                {c,  -s,  0,  x -x*c +y*s,
                 s,   c,  0,  y -x*s -y*c,
                 0,   0,  1,  0,
                 0,   0,  0,  1            }, transf);*/

    float t00=transf[0], t01=transf[1], t03=transf[3];
    float t10=transf[4], t11=transf[5], t13=transf[7];
    transf[0]=t00*c -t10*s;
    transf[1]=t01*c -t11*s;
    transf[4]=t00*s +t10*c;
    transf[5]=t01*s +t11*c;
    transf[3]=t03*c -t13*s +x-x*c+y*s;
    transf[7]=t03*s +t13*c +y-x*s-y*c;

}

void TImage::resetPosition(){
    rotation=0;
    if(transf)delete[] transf;
    transf= new float[16]{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
}

void TImage::paint(unsigned int w, unsigned int h){

    if(!w) w=im->width();
    if(!h) h=im->height();
    int x=w/2, y=h/2;
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txt);
    glColor3f(1,1,1);
    glPushMatrix();
        glMultTransposeMatrixf(transf);
        glBegin(GL_QUADS);
           glTexCoord2f(0,1); glVertex2f(-x,-y);
           glTexCoord2f(1,1); glVertex2f( x,-y);
           glTexCoord2f(1,0); glVertex2f( x, y);
           glTexCoord2f(0,0); glVertex2f(-x, y);
       glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 0);

}

void TImage::readBuffer(unsigned width, unsigned height, V2d orig){
    unsigned nCols= width ? width  : im->width();
    unsigned nRows= height? height : im->height();

    int x = orig.x, y = orig.y;
    for(unsigned f=0; f<nRows; ++f){
        uchar* fila= im->scanLine(nRows-f-1);
        glReadPixels(x, y+f, //esquina inferior‐izquierda del bloque
                    nCols, 1, //tamaño del bloque
                    GL_BGRA, //formato
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

void TImage::add(QImage i){


}

void TImage::sub(QImage i){
    QImage a= im->convertToFormat(QImage::Format_Indexed8);
    i = i.convertToFormat(QImage::Format_Indexed8);


}

static QRgb getGAUSS(const QImage &orig, unsigned rage, int x, int y){
    unsigned r=0, g=0, b=0, k=0;
    int iL= x-rage, iR= x+rage, iB= y-rage, iT= y+rage;
    unsigned left= iL<0 ?0 : iL, right= iR<orig.width() ?iR :orig.width()-1;
    unsigned bot = iB<0 ?0 : iB, top = iT<orig.height() ?iT :orig.height()-1;
    for(unsigned i=left; i<=right; i++)
        for(unsigned j=bot; j<=top; j++){
            QRgb rgb =orig.pixel(i,j);
            b += (uchar) (rgb & 0xff);
            g += (uchar) ((rgb & 0xff00)>>8);
            r += (uchar) ((rgb & 0xff0000)>>16);
            k++;
    }
    r/=k; g/=k; b/=k;
    return (unsigned) (b | g<<8 | r<<16);
}

void TImage::gaussianFilter(unsigned rage){
    QImage* copy= new QImage(im->copy());
    int width= copy->width(), height= copy->height();
    for(int x=0; x<width; x++)
        for(int y=0; y<height; y++)
                copy->setPixel(x, y, getGAUSS(*im, rage, x, y));
    delete im;
    im= copy;
    setup();
}
