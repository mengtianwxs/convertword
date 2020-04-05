#ifndef CARETAKER_H
#define CARETAKER_H

#include "memento.h"

#include <QObject>
#include <QVector>

class Caretaker
{
private:
    QVector<Memento*> vec;
public:

    QVector<Memento*> getVector(){
        return vec;
    }

    void setMemento(Memento* me){

         vec.push_back(me);
    };
    Memento* getMemento(int i){
        return (Memento*)vec[i];
    };
};



#endif // CARETAKER_H
