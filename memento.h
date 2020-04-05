#ifndef MEMENTO_H
#define MEMENTO_H
#include<QObject>

class Memento
{
public:
    Memento(QString cont);

   QString getContent();
   void setContent(QString con);

private:
    QString content;
};

#endif // MEMENTO_H
