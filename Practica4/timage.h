#ifndef TIMAGE_H
#define TIMAGE_H

#include <QImage>
#include <GL/gl.h>
#include <v2d.h>

class TImage{
public:
    TImage(unsigned w, unsigned h);
    TImage(QString &path);
   ~TImage();
    void rotate(float angle, V2d center=V2d());
    void resetPosition();
    void paint(unsigned width=0, unsigned height=0);
    bool save(const QString& fileName, const char* format =0, int quality =-1);
    void readBuffer(unsigned width=0, unsigned height=0, V2d orig=V2d());
    void updateBuff(int glBuff=1029, unsigned width=0, unsigned height=0, V2d center=V2d());

    QSize size();
    inline float angle(){return rotation;}
    QImage* edges(uchar d=0xff);

    void op(QImage i, unsigned(*f)(unsigned, unsigned));
    void add(QImage i);
    void sub(QImage i);
    void gaussianFilter(unsigned rage=1);
    void switchToEdges();
    void seeBorder();
protected:
    TImage(QImage* image=0);
    void setup(bool clearAux=1);

    float rotation;
    float* transf;
    QImage *im;
    QImage *auxIm;
    GLuint txt;
};

#endif // TIMAGE_H
