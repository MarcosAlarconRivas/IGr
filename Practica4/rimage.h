#ifndef RIMAGE_H
#define RIMAGE_H

#include <QImage>
#include <GL/gl.h>
#include <v2d.h>

class RImage{
public:
    RImage(unsigned w, unsigned h);
    RImage(QString &path);
   ~RImage();
    void rotate(float angle);
    void setAngle(float angle);
    void paint(unsigned width=0, unsigned height=0);
    void readBuffer(unsigned width=0, unsigned height=0, V2d orig=V2d());
    void updateBuff(int glBuff=1029, unsigned width=0, unsigned height=0, V2d center=V2d());
    bool save(const QString& fileName, const char* format =0, int quality =-1);
    QSize size();
    inline float angle(){return rotation;}
protected:
    RImage(QImage* image=0, float rotation=0);
    void setup();
    double rotation;
    QImage *im;
    GLuint txt;
};

#endif // RIMAGE_H
