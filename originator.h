#ifndef ORIGINATOR_H
#define ORIGINATOR_H

#include "memento.h"

#include <QObject>

class Originator
{
public:
    Originator();
    void setContent(QString con);
    QString getContent();
    void restoreMemento(Memento* me){

        this->content=me->getContent();
    };
    Memento* createMemento(){

        return new Memento(this->content);
    };

private:
    QString content;
};


#endif // ORIGINATOR_H
