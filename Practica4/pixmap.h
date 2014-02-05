#ifndef PIXMAP_H
#define PIXMAP_H
#include <QPixmap>

typedef unsigned char rgb[3];

class PixMap{
    protected:
        unsigned r, c, b;
        rgb *map;
    public:
        PixMap(unsigned cols, unsigned rows);
        PixMap(QPixmap &qpm);
       ~PixMap();
        void paint();

        //FIX: glPixelMap
};

#endif // PIXMAP_H
