#ifndef BILLARD_H
#define BILLARD_H
#include "cuboid.h"
#include "sphere.h"
#include "composite.h"

Model* new_Billiard(){
    //create scene objects
    auto scene= new Composite;
    auto balls= new Composite;
    auto table= new Composite;
    auto brdrs= new Composite;

    double ballR = .5715;

    double legW=.6;
    double inBrdr=.8;
    double woodW=.5;
    double tabW=25.4, tabH=7.5, tabD=12.7;
    float wood[3]{.5, .2, .02};

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
