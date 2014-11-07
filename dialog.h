#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "colorbar.h"
#include "pmd.h"

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    COLORBAR *c;
    PMD *p;
    QTimer *timer;
    //int time;
    QLineEdit *begin;
    QLineEdit *end;
    QLabel *ldef;
    QLabel *lview;
    QLabel *mm1;
    QLabel *mm2;
    QLabel *lbegin;
    QLabel *lend;
    QLabel *changelabel;
    QPushButton *pmdshowlayer;
    QPushButton *change;
    QPushButton *pmdconnect;
    QPushButton *pmddisconnect;
    QPushButton *backDef;
    QPushButton *pmdstop;
    QPushButton *pmdmanual;
    QPushButton *pmdauto;
    QPushButton *pmdtopview;
    QPushButton *pmdquadspoints;
    QPushButton *pmdshowinvalid;
    QPushButton *pmdshowgrid;
    QSlider *slider;
    //QTextEdit *message;
    //QPushButton *showvals;

public slots:
    void sendData();
    void manual();
    void pmdAuto();
    void pmdConnect();
    void pmdDisconnect();
    void backDefault();
    void pmdStop();
    void showvalues();
    void updateColorBar();
    void changeView();
    void switchtop();
    void switchquadspoints();
    void showInvalid();
    void showGrid();
    void valueChanged(int value);

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
