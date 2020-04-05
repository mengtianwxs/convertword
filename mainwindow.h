#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "caretaker.h"
#include "originator.h"

#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPushButton* pb_convert;
    QPushButton* pb_parse;
    QPushButton* pb_clear;
    QPushButton* pb_reset;
    QPushButton* pb_translate;
    QTextEdit* te_data;
    QTextEdit* te_name;
    QTextEdit* te_value;
    QPushButton* pb_undo;
    QPushButton* pb_redo;

    QStringList list_name;
    QStringList list_value;
    QStringList list_data;
    QStringList list_num;
    QProgressBar* prob;
    QDoubleSpinBox* dspinbox;

    QString maincontent="";

    void initui();



    void initMementoMode();
    void moveCursorToEnd(QTextEdit* te);

    Caretaker* Car;
    Originator* Ori;
    QVector<Memento*> menum;
    int mnum;
    int undonum=0;
    int undocishu=0;
    int redonum=0;
    int redocishu=0;
    bool isundo=false;


public slots:
    void onconvert();
    void onparse();
    void onclear();
    void onreset();
    void ontranslate();
    void onredo();
    void onundo();

protected:
    void keyPressEvent(QKeyEvent* event);



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
