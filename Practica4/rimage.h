#ifndef RIMAGE_H
#define RIMAGE_H

#include <QImage>

class RImage{
public:
    RImage(QImage* image=0, float rotation=0);
    RImage(QString &path);
   ~RImage();
    void rotate();
    void paint();
    QSize size();
protected:
    float rotation;
    QImage *im;
};

#endif // RIMAGE_H
