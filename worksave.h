#ifndef WORKSAVE_H
#define WORKSAVE_H

#include <QObject>
#include <QThread>

class WorkSave : public QThread
{

public:
    WorkSave();
    volatile bool isStart=false;
    void stopThread();
    void startThread();
    void setContent(QString content);
    QStringList list;
    int lastNum=0;
    int currentNum=0;
protected:
    void run();
private:
    QString data;
};

#endif // WORKSAVE_H
