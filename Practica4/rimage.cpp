#include "rimage.h"

RImage::RImage(QImage* image, float angle0){
    im=image;
    rotation=angle0;
    QRgb *pixmap= new QRgb [im->height()*im->width()];
    int fil =im->height();
    int col =im->width();
    for(int f=0; f<fil; f++)
        for(int c=0; c<col; c++)
            pixmap[f*col+c]=im->pixel(c, fil-f-1);

    // allocate a texture name
    glGenTextures( 1, &txt );

    // select our current texture
    glBindTexture(GL_TEXTURE_2D, txt);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, col, fil, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixmap);

    delete[] pixmap;
}

RImage::RImage(QString &path):RImage(new QImage(path)){}

RImage::~RImage(){
    delete im;
    glDeleteTextures(1, &txt);
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

void RImage::paint(unsigned int w, unsigned int h){

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
       glRotated(rotation, 0, 0, 1);
       glBegin(GL_QUADS);
           glTexCoord2f(0,0); glVertex2f(-x,-y);
           glTexCoord2f(1,0); glVertex2f( x,-y);
           glTexCoord2f(1,1); glVertex2f( x, y);
           glTexCoord2f(0,1); glVertex2f(-x, y);
       glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool RImage::save(const QString & fileName, const char * format, int quality){
    return im->save(fileName, format, quality);
}
