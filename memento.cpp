#include "memento.h"

Memento::Memento(QString cont)
{
   this->content=cont;
}

QString Memento::getContent()
{
   return content;
}

void Memento::setContent(QString con)
{
  this->content=con;
}

