#include "ellipse.h"
#include <GL/gl.h>

Ellipse::Ellipse(V2d center, float W, float H):Ellipse(center,W,H,0){
}

Ellipse::Ellipse(V2d center, double W, double H, double rot):Circle(center,1){
    width=W, height=H, rotation=rot;
}

void Ellipse::paint()const{
    glPushMatrix();
    glTranslatef(center.x, center.y, 0);
    glRotatef(rotation, 0, 0, 1);
    glScalef(width, height, 1);
    glBegin(GL_POLYGON);
        circle_vertex();
    glEnd();
    glPopMatrix();
}

bool Ellipse::intersection(V2d p, V2d d, float s, double& tIn, V2d& normalIn)const{
    return 0;
}
