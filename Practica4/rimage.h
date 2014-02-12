#ifndef RIMAGE_H
#define RIMAGE_H

#include <QImage>
#include <GL/gl.h>

class RImage{
public:
    RImage(QImage* image=0, float rotation=0);
    RImage(QString &path);
   ~RImage();
    void rotate(float angle);
    void setAngle(float angle);
    void paint(unsigned wth=0, unsigned hth=0);
    bool save(const QString & fileName, const char * format = 0, int quality = -1 );
    QSize size();
    inline float angle(){return rotation;}
protected:
    double rotation;
    QImage *im;
    GLuint txt;
};

#endif // RIMAGE_H
