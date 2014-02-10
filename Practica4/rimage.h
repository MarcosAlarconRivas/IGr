#ifndef RIMAGE_H
#define RIMAGE_H

#include <QImage>

class RImage{
public:
    RImage(QImage* image=0, float rotation=0);
    RImage(QString &path);
   ~RImage();
    void rotate(float angle);
    void paint();
    bool save(const QString & fileName, const char * format = 0, int quality = -1 );
    QSize size();
protected:
    double rotation;
    QImage *im;
    QRgb * pixmap;
};

#endif // RIMAGE_H
