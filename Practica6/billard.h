#ifndef BILLARD_H
#define BILLARD_H
#include "cuboid.h"
#include "sphere.h"
#include "cone.h"
#include "composite.h"

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

Model* new_Billiard(){

    double ballR = .5715;
    double legW=1;
    double inBrdr=1.8;
    double woodW=.6;
    double tabW=25.4, tabH=7.5, tabD=12.7;
    float wood[3]{.5, .2, .02};

    //create scene objects
    auto scene= new Composite;
    auto balls= new Composite;
    auto table= new Composite;
    auto brdrs= new Composite;
    auto chalk= new Composite;
    auto stick= new_stick(wood[0], wood[1], wood[2]);

    Cuboid* t= new Cuboid(tabW, woodW, tabD, .1, 1, .2);//mat
    t->translate(0,woodW+tabH,0);
    table->push(t);
    t=new Cuboid(tabW+inBrdr*2, woodW, tabD+inBrdr*2, wood);//table
    t->translate(-inBrdr,tabH,-inBrdr);
    table->push(t);
    t=new Cuboid(legW, tabH, legW, wood);//leg 0,0
    t->translate(-inBrdr,0,-inBrdr);
    table->push(t);
    t=new Cuboid(legW, tabH, legW, wood);//leg 1,0
    t->translate(tabW+inBrdr-legW,0,-inBrdr);
    table->push(t);
    t=new Cuboid(legW, tabH, legW, wood);//leg 0,1
    t->translate(-inBrdr,0,tabD +inBrdr-legW);
    table->push(t);
    t=new Cuboid(legW, tabH, legW, wood);//leg 1,1
    t->translate(tabW+inBrdr-legW,0,tabD +inBrdr-legW);
    table->push(t);

    brdrs->translate(0, woodW+tabH, 0);
    t= new Cuboid(tabW, woodW+ballR*1.2, inBrdr, wood);
    t->translate(0,0,-inBrdr);
    brdrs->push(t);
    t= new Cuboid(tabW, woodW+ballR*1.2, inBrdr, wood);
    t->translate(0,0,tabD);
    brdrs->push(t);
    t= new Cuboid(inBrdr, woodW+ballR*1.2, tabD+2*inBrdr, wood);
    t->translate(-inBrdr,0,-inBrdr);
    brdrs->push(t);
    t= new Cuboid(inBrdr, woodW+ballR*1.2, tabD+2*inBrdr, wood);
    t->translate(tabW,0,-inBrdr);
    brdrs->push(t);

    t= new Cuboid(.21, .18, .21, .3, 0, .5);
    t->translate(-.005, -.005, -.005);
    chalk->push(t);
    t= new Cuboid(.2, .2, .2, 0, .2, 1);
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

    balls->translate(.7*tabW, tabH+2*woodW+ballR, .5*tabD);
    double sqr3 = sqrt(3);

    Sphere* b= new Sphere(ballR);//white one
    b->translate(-.5*tabW,0,0);
    balls->push(b);

    b=(new Sphere(ballR))->setColor(1,1,0);//9 yelow
    balls->push(b);

    b=(new Sphere(ballR))->setColor(.6,0,.08);//7 crimson
    b->translate(ballR*sqr3,0,ballR);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(.3,0,.4);//12 purple
    b->translate(ballR*sqr3,0,-ballR);
    balls->push(b);

    b=(new Sphere(ballR))->setColor(.02,.02,.02);//8 black
    b->translate(2*ballR*sqr3,0,0);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(.6,0,.08);//15 crimson
    b->translate(2*ballR*sqr3,0,2*ballR);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(1,1,0);//1 yelow
    b->translate(2*ballR*sqr3,0,-2*ballR);
    balls->push(b);

    b=(new Sphere(ballR))->setColor(0,0,1);//10 blue
    b->translate(3*ballR*sqr3,0,ballR);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(1,0,0);//3 red
    b->translate(3*ballR*sqr3,0,-ballR);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(0,.5,.15);//6 green
    b->translate(3*ballR*sqr3,0,3*ballR);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(0,.5,.15);//14 green
    b->translate(3*ballR*sqr3,0,-3*ballR);
    balls->push(b);

    b=(new Sphere(ballR))->setColor(1,.2,0);//13 orange
    b->translate(4*ballR*sqr3,0,0);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(0,0,1);//2 blue
    b->translate(4*ballR*sqr3,0,2*ballR);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(.3,0,.4);//12 purple
    b->translate(4*ballR*sqr3,0,-2*ballR);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(1,0,0);//11 red
    b->translate(4*ballR*sqr3,0,4*ballR);
    balls->push(b);
    b=(new Sphere(ballR))->setColor(1,.2,0);//5 orange
    b->translate(4*ballR*sqr3,0,-4*ballR);
    balls->push(b);

    scene->push(table);
    scene->push(balls);
    return scene;
}

#endif // BILLARD_H
