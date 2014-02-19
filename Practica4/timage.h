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
    void readBuffer(unsigned width=0, unsigned height=0, V2d orig=V2d());
    void updateBuff(int glBuff=1029, unsigned width=0, unsigned height=0, V2d center=V2d());
    bool save(const QString& fileName, const char* format =0, int quality =-1);
    QSize size();
    inline float angle(){return rotation;}
protected:
    TImage(QImage* image=0);
    void setup();
    double rotation;
    float* transf;
    QImage *im;
    GLuint txt;
};

#endif // TIMAGE_H
