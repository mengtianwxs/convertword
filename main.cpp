#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include<QDebug>
#include<QStatusBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString appp=argv[1];
    QStatusBar* sb=w.findChild<QStatusBar*>("statusBar");
    sb->showMessage("&&"+appp);
    if(appp.contains(".conw")){

        QFile file(appp);

        if(file.exists() and file.open(QIODevice::ReadOnly|QIODevice::Text)){

            QTextStream ts(&file);
            ts.setAutoDetectUnicode(true);
            QTextEdit* te_data=w.findChild<QTextEdit*>("tedata");
            te_data->clear();
            QString content="";
            while (!ts.atEnd()) {
                content=ts.readLine();
                te_data->append(content);

            }
            file.close();

        }
    }
    w.show();

    return a.exec();
}
