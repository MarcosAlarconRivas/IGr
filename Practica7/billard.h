#ifndef BILLARD_H
#define BILLARD_H
#include "ball.h"
#include "cuboid.h"
#include "cone.h"
#include "disk.h"
#include "composite.h"
#include "lamp.h"
#include <QString>

GLuint getTexture(QString path, bool mirrored=1){
    GLuint texture=0;
    QImage im= QImage(path);
    if(mirrored)im = im.mirrored(1, 0);
    if(im.isNull())return 0;
    glEnable(GL_TEXTURE_2D);
    glGenTextures( 1, &texture );
    glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.width(), im.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, im.bits());
    glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_TEXTURE_2D);

    return texture;
}

Model* new_stick(float r, float g, float b){
    double l1= .1, l2= 6, l3= 17, l4= .5, l5= .05;
    double r1= .4, r2= .1;
    auto stick= new Composite;

    auto c= new Cone(0, r1, l1, 10, 5);
    stick->push( c->setColor(.03,.03,.03) );

    c= new Cone(r1, r1, l2);
    c->translate(0,0,l1);
    stick->push( c->setColor(r*.8,g*.8,b*.8) );

    c = new Cone(r1, r2, l3);
    c->translate(0,0,l1+l2);
    stick->push( c->setColor(r*1.4,g*1.7,b*1.5) );

    c = new Cone(r2, r2, l4, 10, 8);
    c->translate(0,0,l1+l2+l3);
    stick->push( c->setColor(1,1,1) );

    c= new Cone(r2, 0, l5, 10, 5);
    c->translate(0,0,l1+l2+l3+l4);
    stick->push( c->setColor(0,.3,1) );
    return stick;
}

static Composite* new_hole(double rad, double hth){
    auto h= new Composite;
    auto c= new Cone(rad,rad,hth);
    c->translate(0,0,-hth);
    h->push(c->setColor(0,0,0));
    auto d= new Disk(rad);
    h->push(d->setColor(0,0,0));
    h->rotate(270, 1,0,0);
    return h;
}

Composite* new_15Balls(double ballR){
    //Images from http://www.sharecg.com
    double sqr3 = sqrt(3);
    Sphere* b; 
    auto balls = new Composite;
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball9.jpeg")));
    b->rotate(90,0,0,1);
    balls->push(b);

    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball7.jpeg")));
    b->translate(ballR*sqr3,0,ballR);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball12.jpeg")));
    b->translate(ballR*sqr3,0,-ballR);b->rotate(90,0,0,1);
    balls->push(b);

    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball8.jpeg")));
    b->translate(2*ballR*sqr3,0,0);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball15.jpeg")));
    b->translate(2*ballR*sqr3,0,2*ballR);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball1.jpeg")));
    b->translate(2*ballR*sqr3,0,-2*ballR);b->rotate(90,0,0,1);
    balls->push(b);

    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball10.jpeg")));
    b->translate(3*ballR*sqr3,0,ballR);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball3.jpeg")));
    b->translate(3*ballR*sqr3,0,-ballR);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball6.jpeg")));
    b->translate(3*ballR*sqr3,0,3*ballR);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball14.jpeg")));
    b->translate(3*ballR*sqr3,0,-3*ballR);b->rotate(90,0,0,1);
    balls->push(b);

    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball13.jpeg")));
    b->translate(4*ballR*sqr3,0,0);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball2.jpeg")));
    b->translate(4*ballR*sqr3,0,2*ballR);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball4.jpeg")));
    b->translate(4*ballR*sqr3,0,-2*ballR);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball11.jpeg")));
    b->translate(4*ballR*sqr3,0,4*ballR);b->rotate(90,0,0,1);
    balls->push(b);
    b=(new Sphere(ballR))->setTexture(getTexture(QString("ball5.jpeg")));
    b->translate(4*ballR*sqr3,0,-4*ballR);b->rotate(90,0,0,1);
    balls->push(b);
    return balls;
}

static Cuboid* set(Cuboid* c, float* cl, GLuint t){
    return c->setColor(cl)->setTexture(t);
}

Model* new_Billiard(shared_ptr<Ball>& movile, shared_ptr<Lamp>& lamp){
    double ballR = .5715;
    double legW=1;
    double inBrdr=1.8;
    double woodW=.6;
    double tabW=25.4, tabH=7.5, tabD=12.7;
    float wood[3]{.5, .2, .02};
    GLuint woodTx=getTexture(QString("wood1.jpg"));
    GLuint  matTx=getTexture(QString("mat.png"));

    //create scene objects
    auto scene= new Composite;
    auto table= new Composite;
    auto brdrs= new Composite;
    auto chalk= new Composite;
    auto holes= new Composite;
    auto stick= new_stick(wood[0], wood[1], wood[2]);
    auto balls= new_15Balls(ballR);

    Cuboid* t= (new Cuboid(tabW, woodW, tabD, 20, 0, 10))->setColor(.3, 1, .6)->setTexture(matTx);//mat
    t->translate(0,woodW+tabH,0);
    table->push(t);
    t=set(new Cuboid(tabW+inBrdr*2, woodW, tabD+inBrdr*2, 20, 0, 10), wood, woodTx);//table
    t->translate(-inBrdr,tabH,-inBrdr);
    table->push(t);
    t=set(new Cuboid(legW, tabH, legW, 0, 7), wood, woodTx);//leg 0,0
    t->translate(-inBrdr,0,-inBrdr);
    table->push(t);
    t=set(new Cuboid(legW, tabH, legW, 0, 7), wood, woodTx);//leg 1,0
    t->translate(tabW+inBrdr-legW,0,-inBrdr);
    table->push(t);
    t=set(new Cuboid(legW, tabH, legW, 0, 7), wood, woodTx);//leg 0,1
    t->translate(-inBrdr,0,tabD +inBrdr-legW);
    table->push(t);
    t=set(new Cuboid(legW, tabH, legW, 0, 7), wood, woodTx);//leg 1,1
    t->translate(tabW+inBrdr-legW,0,tabD +inBrdr-legW);
    table->push(t);

    brdrs->translate(0, woodW+tabH, 0);
    t=set(new Cuboid(tabW, woodW+ballR*1.2, inBrdr, 20, 2, 3), wood, woodTx);
    t->translate(0,0,-inBrdr);t->set_specular(.5,1,.4,0);
    brdrs->push(t);
    t=set(new Cuboid(tabW, woodW+ballR*1.2, inBrdr, 20, 2, 3), wood, woodTx);
    t->translate(0,0,tabD);t->set_specular(.5,1,.4,0);
    brdrs->push(t);
    t=set(new Cuboid(inBrdr, woodW+ballR*1.2, tabD+2*inBrdr, 0, 2, 3), wood, woodTx);
    t->translate(-inBrdr,0,-inBrdr);t->set_specular(.5,1,.4,0);
    brdrs->push(t);
    t=set(new Cuboid(inBrdr, woodW+ballR*1.2, tabD+2*inBrdr, 0, 2, 3), wood, woodTx);
    t->translate(tabW,0,-inBrdr);t->set_specular(.5,1,.4,0);
    brdrs->push(t);

    t=(new Cuboid(.21, .18, .21))->setColor(.3, 0, .5);
    t->translate(-.005, -.005, -.005);
    chalk->push(t);
    t=(new Cuboid(.2, .2, .2))->setColor(0, .2, 1);
    chalk->translate(-inBrdr*.6,woodW+ballR*1.2, tabD*.7);
    chalk->rotate(30, 0, 1, 0);
    chalk->push(t);
    brdrs->push(chalk);

    stick->translate(0, woodW+ballR*1.2, 0);
    stick->rotate(-27, 0,1,0);
    stick->translate(4,.5,-10);
    stick->rotate(1, 1,0,0);
    brdrs->push(stick);

    table->push(brdrs);

    holes->translate(0,tabH+2*woodW+ballR*1.2+0.01,0);
    auto h= new_hole(ballR*1.2, 2*woodW);
    holes->push(h);
    h= new_hole(ballR*1.2, 2*woodW);
    h->translate(tabW*.5,0,0);
    holes->push(h);
    h= new_hole(ballR*1.2, 2*woodW);
    h->translate(tabW,0,0);
    holes->push(h);
    h= new_hole(ballR*1.2, 2*woodW);
    h->translate(0,-tabD,0);
    holes->push(h);
    h= new_hole(ballR*1.2, 2*woodW);
    h->translate(tabW*.5,-tabD,0);
    holes->push(h);
    h= new_hole(ballR*1.2, 2*woodW);
    h->translate(tabW,-tabD,0);
    holes->push(h);
    table->push(holes);

    V3D ballsPos= V3D(.7*tabW, tabH+2*woodW+ballR, .5*tabD);
    balls->translate(ballsPos[0], ballsPos[1], ballsPos[2]);

    Ball* b = new Ball(ballR);//white one
    b->translate(-.5*tabW,0,0);
    b->memorize();
    balls->push(b);//FIXME store after make shared
    movile= shared_ptr<Ball>(b);
    V3D d= ballsPos + b->getMemPosition(); d[0]= -d[0]; d[1]=0; d[2]= -d[2];
    V3D fall= V3D(0,-2*woodW+ballR,0);
    movile->setingMove(d, V3D(-fall[0], -fall[1], -fall[2]) % 1, fall);

    Lamp *l= new Lamp;
    l->translate(tabW*.5,tabH*2.75,tabD*.5);
    l->rotate(90, 1, 0, 0);
    //scene->push(l);
    lamp= shared_ptr<Lamp>(l);

    scene->push(table);
    scene->push(balls);
    return scene;
}

#endif // BILLARD_H
