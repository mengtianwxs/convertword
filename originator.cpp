#include "originator.h"

Originator::Originator()
{

}

void Originator::setContent(QString con)
{
    this->content=con;
}

QString Originator::getContent()
{
    return this->content;
}
