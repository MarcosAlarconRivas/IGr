#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "model.h"
#include <list>
#include <memory>
using namespace std;

class Composite : public Model, public list<shared_ptr<Model>>{
public:
    void push(Model* m){
        push_back(shared_ptr<Model>(m));
    }
protected:
    void paint(bool f)const{
        for(auto i= begin(); i != end(); i++)
            (*i)->render(f);
    }

};

#endif // COMPOSITE_H
