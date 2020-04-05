#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXlsx>
#include <QDebug>
#include <xlsxformat.h>
#include <QFileDialog>
#include<QKeyEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("ConvertWord V0.1版");
    initui();
    initMementoMode();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initui()
{

    this->setFixedSize(1000,800);
    pb_convert=ui->pushButton;
    pb_parse=ui->pushButton_2;
    pb_clear=ui->pushButton_clear;
    pb_reset=ui->pushButton_reset;
    pb_translate=ui->pushButton_translate;
    pb_undo=ui->pushButton_undo;
    pb_redo=ui->pushButton_redo;

    te_data=ui->te_data;
    te_name=ui->te_name;
    te_value=ui->te_value;

    te_data->setFixedWidth(600);
    prob=ui->progressBar;
    dspinbox=ui->doubleSpinBox;


    prob->setMinimum(0);
    prob->setMaximum(100);
    prob->setOrientation(Qt::Horizontal);
    prob->setValue(0);
    prob->setTextVisible(false);

    dspinbox->setMinimum(0.1);
    dspinbox->setSingleStep(0.1);
    dspinbox->setDecimals(1);
    dspinbox->setValue(0.3);


//    pb_undo->setEnabled(false);
//    pb_redo->setEnabled(false);


    connect(pb_convert,SIGNAL(clicked()),this,SLOT(onconvert()));
    connect(pb_parse,SIGNAL(clicked()),this,SLOT(onparse()));
    connect(pb_clear,SIGNAL(clicked()),this,SLOT(onclear()));
    connect(pb_reset,SIGNAL(clicked()),this,SLOT(onreset()));
    connect(pb_translate,SIGNAL(clicked()),this,SLOT(ontranslate()));
    connect(pb_undo,SIGNAL(clicked()),this,SLOT(onundo()));
    connect(pb_redo,SIGNAL(clicked()),this,SLOT(onredo()));



}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers()==Qt::ControlModifier){

        if(event->key()==Qt::Key_T){
            ontranslate();
            moveCursorToEnd(te_data);

        }

        if(event->key()==Qt::Key_E){
            onconvert();
           moveCursorToEnd(te_data);
        }

        if(event->key()==Qt::Key_P){
            onparse();
        }
        if(event->key()==Qt::Key_R){
            onreset();
        }
    }
}

void MainWindow::initMementoMode()
{

   Car=new Caretaker();
   Ori=new Originator();

}

void MainWindow::moveCursorToEnd(QTextEdit *te)
{
    QTextCursor cursor=te->textCursor();
    cursor.movePosition(QTextCursor::End);
    te->setTextCursor(cursor);

}



void MainWindow::onconvert()
{
    prob->reset();
    ui->statusBar->clearMessage();


    if(list_name.length()>0){
        list_name.clear();
        list_num.clear();
        list_value.clear();
        te_value->clear();
        te_name->clear();

    }

    QString data=te_data->toPlainText();

    list_data=data.split("@");
    int n=list_data.length();

    for(int i=0;i<n;i++){

        QString dd=list_data[i];
        int nameindex=dd.indexOf("=");
        QString name=dd.mid(0,nameindex);
         list_name.append(name);//名称
         if(dd.contains("/")){
             int xgindex=dd.indexOf("/");
             QString value=dd.mid(nameindex+1,(xgindex-nameindex-1));
             list_value.append(value);//值
             QString num=dd.mid(xgindex+1,dd.length()-xgindex);
             list_num.append(num);//数量
         }else{
             QString value=dd.mid(nameindex+1,dd.length());
             list_value.append(value);
             list_num.append("1");
         }
    }
    //赋值与value
    int m=list_name.length();
    for(int i=0;i<m;i++){

        te_name->append(QString::number(i+1)+" >> "+list_name[i]+" 台 "+list_num[i]);
        te_value->append(QString::number(i+1)+" >> "+list_value[i]);
    }


    maincontent=te_data->toPlainText();
    Ori->setContent(maincontent);
    Car->setMemento(Ori->createMemento());

    menum=Car->getVector();
    mnum=menum.count(); //备忘录总数

}

void MainWindow::onparse()
{

    QXlsx::Document xlsx;
    prob->setValue(1);
    double fcxishu=dspinbox->value();

    QXlsx::Format format;
    format.setBorderStyle(QXlsx::Format::BorderThin);
    format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    xlsx.write("A1","序号",format);
    xlsx.write("B1","编号",format);
    xlsx.write("C1","单位",format);
    xlsx.write("D1","数量",format);
    xlsx.write("E1","箱体尺寸",format);
    xlsx.write("F1","箱体",format);
    xlsx.write("G1","材料",format);
     xlsx.write("H1","辅材",format);
     xlsx.write("I1","单台合计",format);
     xlsx.write("J1","总计",format);
     xlsx.write("K1","备注",format);

     prob->setValue(40);
    int l=list_name.length();//3
    for(int i=1;i<=l;i++){
        xlsx.write("A"+QString::number(i+1),i,format);
        xlsx.write("B"+QString::number(i+1),list_name[i-1],format);
        xlsx.write("C"+QString::number(i+1),"台",format);
        xlsx.write("D"+QString::number(i+1),list_num[i-1].toInt(),format);
        xlsx.write("E"+QString::number(i+1),"",format);
        xlsx.write("F"+QString::number(i+1),"",format);
        xlsx.write("G"+QString::number(i+1),"="+list_value[i-1],format);
        xlsx.write("H"+QString::number(i+1),"=G"+QString::number(i+1)+"*"+QString::number(fcxishu),format);
        xlsx.write("I"+QString::number(i+1),"=SUM(F"+QString::number(i+1)+":H"+QString::number(i+1)+")",format);
        xlsx.write("J"+QString::number(i+1),"=I"+QString::number(i+1)+"*D"+QString::number(i+1),format);
         xlsx.write("K"+QString::number(i+1),"",format);

    }
    prob->setValue(80);
    QDateTime currentdatetime=QDateTime::currentDateTime();
    QString currentdate=currentdatetime.toString("yyyyMMDDddhhmmsscw");
    xlsx.saveAs(currentdate+".xlsx");

    prob->setValue(100);
    ui->statusBar->showMessage("save "+currentdate+".xlsx success!");

}

void MainWindow::onclear()
{
    te_data->clear();

}

void MainWindow::onreset()
{
    te_data->clear();
    te_name->clear();
    te_value->clear();

    list_data.clear();
    list_name.clear();
    list_num.clear();
    list_value.clear();
}

void MainWindow::ontranslate()
{

    QString data=te_data->toPlainText();
    QString newdata="";

    QRegExp exp1("等于");
    newdata=data.replace(exp1,"=");
    QRegExp exp1a("等你");
    newdata=data.replace(exp1a,"=");
    QRegExp exp2("加");
    newdata=data.replace(exp2,"+");
    QRegExp exp2a1("家");
    newdata=data.replace(exp2a1,"+");
    QRegExp exp2a("加上个");
    newdata=data.replace(exp2a,"+");
    QRegExp exp2b("加上了");
    newdata=data.replace(exp2b,"+");
    QRegExp exp2c("加上");
    newdata=data.replace(exp2c,"+");
    QRegExp exp3("乘以");
    newdata=data.replace(exp3,"*");
    QRegExp exp4("  ");
    newdata=data.replace(exp4,"@");
    QRegExp exp4b("\\t");
    newdata=data.replace(exp4b,"@");
    QRegExp exp4a("\\n");
    newdata=data.replace(exp4a,"@");
    QRegExp exp5("斜杠");
    newdata=data.replace(exp5,"/");
    QRegExp exp5a("斜-");
    newdata=data.replace(exp5a,"/");
    QRegExp exp6("×");
    newdata=data.replace(exp6,"*");



    te_data->setText(newdata);

}

void MainWindow::onredo()
{

    if(undonum>=0 and undonum<mnum){
        if(redocishu==mnum-1){
            redocishu==mnum-1;


        }else{
             redocishu=redocishu+1;

        }

        redonum=undonum+redocishu;
        if(redonum>=mnum-1){
            redonum=mnum-1;
        }

        qDebug()<<"redonum"<<redonum;

      Ori->restoreMemento(Car->getMemento(redonum));
       te_data->setText(Ori->getContent());


    }
    undocishu=0;
}

void MainWindow::onundo()
{


    if(undocishu==(mnum-1)){
        undocishu=mnum-1;

    }else{

        undocishu=undocishu+1;

    }
    undonum=mnum-undocishu-1;
    Ori->restoreMemento(Car->getMemento(undonum));
    te_data->setText(Ori->getContent());

    qDebug()<<"undonum"<<undonum<<"undocishu"<<undocishu;

 redocishu=0;

}


