#include "car.h"

Car::Cube::Cube(double x, double y, double z){
    vertex= vector<vtx_p>(8);
    vertex[0]= make_shared<vtx>(vtx{V3D( x, y, z), V3D( 1, 1, 1, 0)});
    vertex[1]= make_shared<vtx>(vtx{V3D(-x, y, z), V3D(-1, 1, 1, 0)});
    vertex[2]= make_shared<vtx>(vtx{V3D(-x,-y, z), V3D(-1,-1, 1, 0)});
    vertex[3]= make_shared<vtx>(vtx{V3D( x,-y, z), V3D( 1,-1, 1, 0)});
    vertex[4]= make_shared<vtx>(vtx{V3D( x, y,-z), V3D( 1, 1,-1, 0)});
    vertex[5]= make_shared<vtx>(vtx{V3D(-x, y,-z), V3D(-1, 1,-1, 0)});
    vertex[6]= make_shared<vtx>(vtx{V3D(-x,-y,-z), V3D(-1,-1,-1, 0)});
    vertex[7]= make_shared<vtx>(vtx{V3D( x,-y,-z), V3D( 1,-1,-1, 0)});

    face=   vector<Face> (6);
    addFace(0, 0,1,2,3); //front
    addFace(1, 5,4,7,6); //back
    addFace(2, 4,0,3,7); //right
    addFace(3, 1,5,6,2); //left
    addFace(4, 4,5,1,0); //up
    addFace(5, 3,2,6,7); //down
}

void Car::Cube::addFace(int f, int i0, int i1, int i2, int i3){
    face[f]= Face(4);
    face[f][0]= vertex[i0];
    face[f][1]= vertex[i1];
    face[f][2]= vertex[i2];
    face[f][3]= vertex[i3];
}

Car::Car(double width, double height, double length, double wheelRadius, double wheelWidth){
    double w=width/2, h=height/2, l=length/2;
    chassis= unique_ptr<Cube>(new Cube(w,h,l));
    //TODO bouid wheels

}

//builds the fernet frame (M) for the current point (t)
void Car::frenet(){
    V3D C= d0(t) %1;
    V3D T= d1(t) %1;
    V3D B= T ^ d2(t);
    V3D N= T ^ B;

    M[0] = N[0]; M[1] = B[0]; M[2]= T[0]; M[3]= C[0];
    M[4] = N[1]; M[5] = B[1]; M[6]= T[1]; M[7]= C[1];
    M[8] = N[2]; M[9] = B[2]; M[10]=T[2]; M[11]=C[2];
    //M[12]=  0  ; M[13]=  0  ; M[14]= 0  ; M[15]= 1  ;
}

void Car::setWay(V3D (*C)(double), V3D (*dC)(double), V3D (*ddC)(double)){
    d0= C; d1= dC; d2= ddC;
}

void Car::advance(double inc){
    t += inc;
    frenet();
    //roll(inc*rollW);
}

void Car::paint(bool f)const{
    glPushMatrix();
        glMultTransposeMatrixf(M);
        glColor4fv(cCol);
        chassis->paint(f);
        glColor4fv(wCol);
        //wheel->paint(f);
    glPopMatrix();
}

void Car::setChassisCol(float r, float g, float b, float a){
    cCol[0]=r; cCol[1]=g; cCol[2]=b; cCol[3]=a;
}

void Car::setWheelsCol(float r, float g, float b, float a){
    wCol[0]=r; wCol[1]=g; wCol[2]=b; wCol[3]=a;
}

