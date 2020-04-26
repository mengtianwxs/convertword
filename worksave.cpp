#include "worksave.h"

#include <QFile>
#include <QTextStream>
#include<QDebug>
#include <QDir>

WorkSave::WorkSave()
{
   qDebug()<<"worksave";
}

void WorkSave::stopThread()
{
    isStart=false;

}

void WorkSave::startThread()
{
    isStart=true;
}

void WorkSave::setContent(QString content)
{
    this->data=content;
//    list.append(content);
//    currentNum=list.length();



}

void WorkSave::run()
{

    while (isStart) {



        if(this->data!=""){
            QDir dir;
            if(!dir.exists("D:/CONWTEMP")){
                dir.mkpath("D:/CONWTEMP");
            }
           QFile file("D:/CONWTEMP/temp.conw");
           QString all;
            if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
                QTextStream ts(&file);
                ts.setAutoDetectUnicode(true);
                if(all!="" and all!=this->data){

                    ts<<this->data;
                }

                file.close();


            }


//            if(file.exists()){
//                if(file.open(QIODevice::ReadOnly)){
//                    QTextStream readts(&file);
//                     readts.setAutoDetectUnicode(true);
//                    all=readts.readAll();
//                    qDebug()<<all<<"all";
//                    file.close();
//                }

//            }


        sleep(55);
 }

    }
}
