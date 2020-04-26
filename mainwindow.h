#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "caretaker.h"
#include "originator.h"
#include "worksave.h"

#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QTextEdit>
#include<QFileDialog>
#include<QSettings>
#include<QCheckBox>
#include<QEvent>


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
    QPushButton* pb_save;
    QPushButton* pb_import;

    QStringList list_name;
    QStringList list_value;
    QStringList list_data;
    QStringList list_num;
    QStringList list_size;
    QStringList list_itemsum;
    QProgressBar* prob;
    QDoubleSpinBox* dspinbox;
    QCheckBox* cb_autosave;

    QString maincontent="";
    QString newdata="";

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

    void initregedittable();
    void oncopylastline();

    void moveCursorUp();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorStart();
    void moveCursorEnd();
    void initTextDataEdit();
    QString FilterTextHeadData(QString te);
    void insertHeadData();
    WorkSave* wsave;

public slots:
    void onconvert();
    void onparse();
    void onclear();
    void onreset();
    void ontranslate();
    void onredo();
    void onundo();
    void onsave();
    void onimport();
    void ontextchanged();
    void oncheckboxautosave(int state);


protected:
    void keyPressEvent(QKeyEvent* event);
    bool eventFilter(QObject* obj,QEvent* event);



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
