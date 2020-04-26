#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXlsx>
#include <QDebug>
#include <xlsxformat.h>
#include <QFileDialog>
#include<QKeyEvent>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("ConvertWord V0.1版");
    initui();
     wsave=new WorkSave;
    initMementoMode();
//    initregedittable();
    initTextDataEdit();


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
    pb_save=ui->pushbutton_save;
    pb_import=ui->pushButton_import;

    te_data=ui->te_data;
    te_name=ui->te_name;
    te_value=ui->te_value;
    cb_autosave=ui->cb_autosave;

    te_data->setFixedWidth(600);
    te_data->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    te_data->setFocus();
    te_data->installEventFilter(this);

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
    connect(pb_save,SIGNAL(clicked()),this,SLOT(onsave()));
    connect(pb_import,SIGNAL(clicked()),this,SLOT(onimport()));
    connect(te_data,SIGNAL(textChanged()),this,SLOT(ontextchanged()));
    connect(cb_autosave,SIGNAL(stateChanged(int)),this,SLOT(oncheckboxautosave(int)));




}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers()==Qt::ControlModifier){


        switch (event->key()) {
        case Qt::Key_T:
            ontranslate();
            moveCursorToEnd(te_data);
            break;

        case Qt::Key_R:
            onreset();
            break;
        case Qt::Key_D:
             oncopylastline();
//            moveCursorToEnd(te_data);
            break;
        case Qt::Key_Space:
            //            insertHeadData();
            te_data->setText(te_data->toPlainText().mid(0,te_data->toPlainText().length()-1));
            te_data->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
            break;
        case Qt::Key_P:
            moveCursorUp();
            break;
        case Qt::Key_N:
            moveCursorDown();
            break;
        case Qt::Key_F:
            moveCursorRight();
            break;
        case Qt::Key_B:
            moveCursorLeft();
            break;
        case Qt::Key_S:
            moveCursorStart();
            break;
        case Qt::Key_E:
            moveCursorEnd();
            break;
//        case Qt::Key_L:
//            qDebug()<<FilterTextHeadData(te_data);
//            break;
        case Qt::Key_Q:

//            QTextCursor tc=te_data->textCursor();
//            QTextLayout*
//            int ncurpos=tc.position()-tc.block().position();
//            QString curstr=te_data->toPlainText().mid(ncurpos-1,1);
//            if(curstr==" "){
//                qDebug()<<"this is null";
//            te_data->moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
            te_data->insertPlainText("=/1");

            te_data->moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
            te_data->moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
//            }


            break;

        case Qt::Key_G:
            ontranslate();
            onconvert();
            onparse();
            break;





        }


    }




    if(event->modifiers()==(Qt::ShiftModifier|Qt::ControlModifier) and event->key()==Qt::Key_Space){



            te_data->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
              insertHeadData();
//            te_data->insertPlainText("\n");
//            te_data->moveCursor(QTextCursor::End);

    }




}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==te_data){
        if(event->type()==QEvent::KeyPress){
            QKeyEvent* key=static_cast<QKeyEvent*>(event);
            if(key->key()==Qt::Key_Return){
                moveCursorToEnd(te_data);
               insertHeadData();
                return true;

            }
        }
    }

    return QMainWindow::eventFilter(obj,event);

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

void MainWindow::initregedittable()
{
    QString strPath=QDir::currentPath();
    strPath.replace("/","\\");
    qDebug()<<strPath;
    QCoreApplication::setOrganizationName("convertword");
    QCoreApplication::setApplicationName("shell\\open\\command");
    QSettings* set=new QSettings("HKEY_CLASSES_ROOT\\convertword\\shell\\open\\command\\",QSettings::NativeFormat);
    set->setValue("Default",strPath+"\\convertword.exe " +"%1");

}

void MainWindow::oncopylastline()
{
          moveCursorToEnd(te_data);

    te_data->insertPlainText("\n");
//    qDebug()<<te_data->toPlainText();
     int pdxnum=te_data->toPlainText().split("\n").length();
//     qDebug()<<pdxnum<<"<<";
      te_data->insertPlainText(QString::number(pdxnum)+">>>");
//      moveCursorToEnd(te_data);

      QString txt=te_data->toPlainText();
      QString lastline=txt.split("\n")[pdxnum-1-1];
      QString newlastline=lastline.mid(lastline.lastIndexOf(">")+1,lastline.length());

//    qDebug()<<newlastline;
    te_data->insertPlainText(newlastline);

}

void MainWindow::moveCursorUp()
{
    te_data->moveCursor(QTextCursor::Up,QTextCursor::MoveAnchor);

}

void MainWindow::moveCursorDown()
{
    te_data->moveCursor(QTextCursor::Down,QTextCursor::MoveAnchor);
}

void MainWindow::moveCursorLeft()
{
    te_data->moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
}

void MainWindow::moveCursorRight()
{
    te_data->moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
}

void MainWindow::moveCursorStart()
{
    te_data->moveCursor(QTextCursor::Start,QTextCursor::MoveAnchor);
}

void MainWindow::moveCursorEnd()
{
    te_data->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
}

void MainWindow::initTextDataEdit()
{
    te_data->setText("1>>>");
    moveCursorToEnd(te_data);
}

QString MainWindow::FilterTextHeadData(QString te)
{

    QRegExp exp4("[9-1][9-0]?[9-0]?[9-0]?[9-0]?[9-0]?>>>");
    return te.replace(exp4,"");
}

void MainWindow::insertHeadData()
{
    te_data->insertPlainText("\n");
     int pdxnum=te_data->toPlainText().split("\n").length();
     qDebug()<<pdxnum;
//                QString nd=FilterTextHeadData(te_data);
      te_data->insertPlainText(QString::number(pdxnum)+">>>");
      moveCursorToEnd(te_data);
}

//void MainWindow::initTextDataEdit()
//{
//    te_data->insertPlainText("1>>\b");
//}



void MainWindow::onconvert()
{
    prob->reset();//进度条

    ui->statusBar->clearMessage();


    if(list_name.length()>0){
        list_name.clear();
        list_num.clear();
        list_value.clear();
        te_value->clear();
        te_name->clear();

    }

    QString data=newdata;

    list_data=data.split("\n");
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




}

void MainWindow::onparse()
{



    int num=list_value.length();
    for(int i=0;i<num;i++){
        QString item=list_value[i];


        if(item.contains("-")){
//            qDebug()<<"##";
            int heng=item.indexOf("-");
            int xie=item.indexOf("/");
            int num=xie-heng;
            list_size.append(item.mid(item.indexOf("-")+1,num));
            list_itemsum.append(item.mid(0,heng));
        }else{
            list_size.append("@");
            list_itemsum.append(item);
        }
    }



//      qDebug()<<"#size "<<list_itemsum;


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
        xlsx.write("E"+QString::number(i+1),list_size[i-1],format);
        xlsx.write("F"+QString::number(i+1),"",format);
        xlsx.write("G"+QString::number(i+1),"="+list_itemsum[i-1],format);
        xlsx.write("H"+QString::number(i+1),"=G"+QString::number(i+1)+"*"+QString::number(fcxishu),format);
        xlsx.write("I"+QString::number(i+1),"=SUM(F"+QString::number(i+1)+":H"+QString::number(i+1)+")",format);
        xlsx.write("J"+QString::number(i+1),"=I"+QString::number(i+1)+"*D"+QString::number(i+1),format);
         xlsx.write("K"+QString::number(i+1),"",format);

    }
    xlsx.write("A"+QString::number(l+2),"",format);
    xlsx.write("B"+QString::number(l+2),"总计",format);
    xlsx.write("C"+QString::number(l+2),"",format);
    xlsx.write("D"+QString::number(l+2),"",format);
    xlsx.write("E"+QString::number(l+2),"",format);
    xlsx.write("F"+QString::number(l+2),"",format);
    xlsx.write("G"+QString::number(l+2),"",format);
     xlsx.write("H"+QString::number(l+2),"",format);
     xlsx.write("I"+QString::number(l+2),"",format);
     xlsx.write("J"+QString::number(l+2),"=SUM(J2:J"+QString::number(l+1)+")",format);
     xlsx.write("K"+QString::number(l+2),"",format);

     QXlsx::Format format1;

     format1.setHorizontalAlignment(QXlsx::Format::AlignLeft);
     format1.setVerticalAlignment(QXlsx::Format::AlignTop);
     format1.setTextWarp(true);
     xlsx.mergeCells("A"+QString::number(l+4)+":K"+QString::number(l+4),format1);
     QString con="报价说明:报价不含运费不含人工。低压元件按正泰产品报价。其他按常规配置，具体元件和数量详见报价清单。箱(柜)体尺寸仅供参考，箱柜体数量以报价数量为准（如果对报价数量未有异议，则以此报价数量为准，若后期有变动需要重新报价）。报价有效期5个工作日。";
     xlsx.write("A"+QString::number(l+4),con);


    prob->setValue(80);
//    QDateTime currentdatetime=QDateTime::currentDateTime();
//    QString currentdate=currentdatetime.toString("yyyyMMDDddhhmmsscw");

   QString file_name=QFileDialog::getSaveFileName(this,"saveFile","D:/Baojia","*.xlsx");

           xlsx.saveAs(file_name);

    prob->setValue(100);
    ui->statusBar->showMessage("save "+file_name+" success!");

}

void MainWindow::onclear()
{
    te_data->clear();
    initTextDataEdit();
     te_data->setFocus();

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
    initTextDataEdit();
     te_data->setFocus();
}

void MainWindow::ontranslate()
{

    QString data=te_data->toPlainText();
    QStringList listnewdata;
    QStringList listhead;
    QStringList listbody;
    QStringList listend;

    //分离
    if(data.contains("=")){
         QStringList listval=data.split("\n");
         int num=listval.length();
         for(int i=0;i<num;i++){
             QString item=listval[i];
             int dh=item.indexOf("=");
             int xh;
             if(item.contains("/")){
                   xh=item.indexOf("/");
                   listhead.append(item.mid(0,item.indexOf("=")+1));
                   listbody.append(item.mid(item.indexOf("=")+1,xh-dh-1));
                   listend.append(item.mid(item.indexOf("/"),item.length()));

             }else{

                 listhead.append(item.mid(0,item.indexOf("=")+1));
                 listbody.append(item.mid(item.indexOf("=")+1,item.length()));
                 listend.append("");
             }


         }


    }

    QStringList listbodynew;
    //把body部分翻译
    int n=listbody.length();
    for(int i=0;i<n;i++){
        QString m=listbody[i];
        QRegExp exp4("m");
        m.replace(exp4,"*");
        QRegExp exp4b("p");
        m.replace(exp4b,"+");
        QRegExp exp4a("h");
        m.replace(exp4a,"-");
        QRegExp exp4c("j");
        m.replace(exp4c,"+");
        QRegExp exp4d("c");
        m.replace(exp4d,"*");
        QRegExp exp4e(",");
        m.replace(exp4e,"-");
        QRegExp exp4f("\\.");
        m.replace(exp4f,"--");
        QRegExp exp4f1("g");
        m.replace(exp4f1,"-");
        QRegExp exp4f2("s");
        m.replace(exp4f2,"-");
        listbodynew.append(m);

    }

    qDebug()<<listhead<<listbodynew<<listend<<"##";

    //combine
    int o=listhead.length();
    QStringList lastdata;
    for(int i=0;i<o;i++){
        QString item1=listhead[i];
        QString item2=listbodynew[i];
        QString item3=listend[i];
        lastdata.append(item1+item2+item3);

    }
    QString laststr=lastdata.join("\n");






    te_data->setText(laststr);


     newdata=FilterTextHeadData(laststr);

qDebug()<<newdata<<"new";
    ////////////////////////备忘录/////////////////
    maincontent=data;
    Ori->setContent(maincontent);
    Car->setMemento(Ori->createMemento());

    menum=Car->getVector();
    mnum=menum.count(); //备忘录总数
///////////////////////////////////////////////


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

void MainWindow::onsave()
{
    QString filename=QFileDialog::getSaveFileName(this,"save","D:/Baojia","*.conw");
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream ts(&file);
        ts.setAutoDetectUnicode(true);
        QString content=te_data->toPlainText();
        ts<<content;
        file.close();

    }



}

void MainWindow::onimport()
{
    QString filename=QFileDialog::getOpenFileName(this,"open","D:/Baojia","*.conw");
    QFile file(filename);

    if(file.exists() and file.open(QIODevice::ReadOnly|QIODevice::Text)){

        QTextStream ts(&file);
        ts.setAutoDetectUnicode(true);
        te_data->clear();
        QString content="";
        while (!ts.atEnd()) {
            content=ts.readLine();
            te_data->append(content);

        }
        file.close();

    }
}

void MainWindow::ontextchanged()
{
    QString aa=te_data->toPlainText();

    QString last=aa.mid(aa.length()-1,1);
 //    qDebug()<<aa<<"--"<<last;
     if(last==" "){
         te_data->setText(aa.mid(0,aa.length()-1)+"=/1");

         te_data->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
         te_data->moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
           te_data->moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
     }

     if(cb_autosave->checkState()){


      wsave->setContent(te_data->toPlainText());
       }

}

void MainWindow::oncheckboxautosave(int state)
{
    if(state==Qt::CheckState::Checked){
       wsave->start();
        wsave->startThread();

    }else{

        wsave->stopThread();
        wsave->wait();

    }
}


