#include "dialog.h"
#include "ui_dialog.h"
//This .cpp file implements User Interface (UI)

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QFont font("Franklin Gothic Book", 12, QFont::Normal);
    QFont font1("Franklin Gothic Book",10, QFont::Normal);

    begin=new QLineEdit("");
//begin->setStyleSheet("width:20px");

    end=new QLineEdit("");
//end->setStyleSheet("width:20px");
    QIntValidator *b=new QIntValidator(0,999,begin);
    QIntValidator *e=new QIntValidator(1,1000,end);

    begin->setValidator(b);
    end->setValidator(e);

    QLabel *space=new QLabel(" ");

    mm1=new QLabel("mm");
    mm2=new QLabel("mm");
    mm1->setFont(font1);

    mm2->setFont(font1);

    QLabel *cpanel=new QLabel("<b>Control panel</b>");
    cpanel->setFont(font);

    lbegin=new QLabel("From:");
    lend=new QLabel("To:");

    lbegin->setFont(font1);
    lend->setFont(font1);

    ldef=new QLabel("<b>View</b>");
    lview=new QLabel("<b>Set view</b>");
    changelabel=new QLabel("<b>Change view</b>");
    ldef->setFont(font);
    lview->setFont(font);
    changelabel->setFont(font);
    QLabel *depth=new QLabel("<b>Depth sensitivity</b>");
    depth->setFont(font);

    change=new QPushButton("Intensity");
    backDef=new QPushButton("Default view");
    pmdconnect=new QPushButton("Connect");
    pmddisconnect=new QPushButton("Disconnect");
    pmdstop=new QPushButton("Stop");
    pmdshowinvalid=new QPushButton("Show bad pixels");
    pmdauto=new QPushButton("Auto");
    pmdmanual=new QPushButton("Manual");

    pmdtopview=new QPushButton("Top view");
    pmdquadspoints=new QPushButton("Dotted view");
    pmdshowgrid=new QPushButton("Remove grid");


    QString *buttonStyle=new QString("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    pmdconnect->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");\
    pmddisconnect->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    pmdtopview->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    pmdquadspoints->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    pmdshowgrid->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    pmdstop->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    pmdauto->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    pmdmanual->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    change->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    backDef->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");
    pmdshowinvalid->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");


    pmdtopview->setFont(font);
    pmdquadspoints->setFont(font);
    change->setFont(font);
    backDef->setFont(font);
    pmdconnect->setFont(font);
    pmddisconnect->setFont(font);
    pmdstop->setFont(font);
    pmdauto->setFont(font);
    pmdmanual->setFont(font);
    pmdshowinvalid->setFont(font);
    pmdshowgrid->setFont(font);
    pmdstop->setDisabled(true);
    pmdauto->setDisabled(true);
    pmdmanual->setDisabled(true);
    change->setDisabled(true);
    backDef->setDisabled(true);
    pmddisconnect->setDisabled(true);
    ldef->setDisabled(true);
    lview->setDisabled(true);
    changelabel->setDisabled(true);
    pmdtopview->setDisabled(true);
    pmdquadspoints->setDisabled(true);
    pmdshowinvalid->setDisabled(true);

    pmdshowlayer=new QPushButton("Show this layer");
    pmdshowlayer->setFont(font);
    QHBoxLayout *main=new QHBoxLayout;
    pmdshowlayer->setStyleSheet("border-width: 1px;border-color: black;font: bold 14px;width:130px;padding: 2px;");

    p=new PMD;
    c=new COLORBAR;
    c->setFixedSize(100,600);
    p->setFixedSize(880,600);

    QGridLayout *top=new QGridLayout;
    //top->addWidget(pmdconnect,0,0,1,2,Qt::AlignCenter);
    //main->addLayout(top);
    //main->addWidget(c);
    //main->addWidget(p);

    slider = new QSlider(Qt::Horizontal);
    slider->setFocusPolicy(Qt::StrongFocus);
         slider->setTickPosition(QSlider::TicksBothSides);
         slider->setTickInterval(2);
         slider->setSingleStep(1);
    slider->setMinimum(1);
    slider->setMaximum(5);
    slider->setValue(3);



    QLabel *logo=new QLabel();

    QPixmap pix("Logo_device_111.png");

    logo->setPixmap(pix);

    QPixmap surveillance("surveillance.jpg");
    QIcon ButtonIcon1(surveillance);
    QPushButton *button1 = new QPushButton();
    button1->setIcon(ButtonIcon1);
    button1->setIconSize(surveillance.rect().size());

    QPixmap health("health.jpg");
    QIcon ButtonIcon2(health);
    QPushButton *button2 = new QPushButton();
    button2->setIcon(ButtonIcon2);
    button2->setIconSize(health.rect().size());

    QPixmap industrial("industrial.jpg");
    QIcon ButtonIcon3(industrial);
    QPushButton *button3 = new QPushButton();
    button3->setIcon(ButtonIcon3);
    button3->setIconSize(industrial.rect().size());

    QPixmap robo("robo.jpg");
    QIcon ButtonIcon4(robo);
    QPushButton *button4 = new QPushButton();
    button4->setIcon(ButtonIcon4);
    button4->setIconSize(robo.rect().size());


    QLabel *spacer=new QLabel();

    QPixmap pix1("spacer.png");

    spacer->setPixmap(pix1);


     top->addWidget(logo,0,0,1,1,Qt::AlignLeft);
     top->addWidget(spacer,0,1,1,1,Qt::AlignLeft);
     top->addWidget(button1,0,2,1,1,Qt::AlignLeft);
     top->addWidget(button2,0,3,1,1,Qt::AlignLeft);
      top->addWidget(button3,0,4,1,1,Qt::AlignLeft);
      top->addWidget(button4,0,5,1,1,Qt::AlignLeft);

    //top->addWidget(pmddisconnect,0,1,1,1,Qt::AlignCenter);

      QLabel *copyright=new QLabel("Copyright by <a href=www.akonin.com>Andrey Konin</a>, 2014");

    QVBoxLayout *left=new QVBoxLayout;
    QGridLayout *panel=new QGridLayout;
    panel->addLayout(top,0,0,2,5,Qt::AlignCenter);

    panel->addWidget(c,2,0,20,1,Qt::AlignCenter);
    panel->addWidget(p,2,1,20,1,Qt::AlignCenter);
panel->addWidget(cpanel,2,2,1,4,Qt::AlignCenter);
    panel->addWidget(pmdconnect,3,2,1,2,Qt::AlignCenter);
    panel->addWidget(pmddisconnect,3,4,1,2,Qt::AlignCenter);
    //panel->addWidget(space,1,0,1,4,Qt::AlignCenter);
    panel->addWidget(lview,4,2,1,4,Qt::AlignCenter);
    panel->addWidget(pmdauto,5,2,1,2,Qt::AlignCenter);
    panel->addWidget(pmdmanual,5,4,1,2,Qt::AlignCenter);
    panel->addWidget(lbegin,6,2,1,2,Qt::AlignLeft);
    panel->addWidget(lend,6,4,1,2,Qt::AlignLeft);
    panel->addWidget(begin,7,2,Qt::AlignLeft);
    panel->addWidget(mm1,7,3,Qt::AlignLeft);
    panel->addWidget(end,7,4,Qt::AlignLeft);
    panel->addWidget(mm2,7,5,Qt::AlignLeft);
    panel->addWidget(pmdshowlayer,8,2,1,4,Qt::AlignCenter);
    //panel->addWidget(space,7,0,1,4,Qt::AlignCenter);
    panel->addWidget(ldef,9,2,1,4,Qt::AlignCenter);
    panel->addWidget(backDef,10,2,1,4,Qt::AlignCenter);
    panel->addWidget(pmdtopview,11,2,1,4,Qt::AlignCenter);
    //panel->addWidget(space,10,0,1,4,Qt::AlignCenter);
    panel->addWidget(changelabel,12,2,1,4,Qt::AlignCenter);
    panel->addWidget(change,13,2,1,4,Qt::AlignCenter);
    panel->addWidget(pmdquadspoints,14,2,1,4,Qt::AlignCenter);

    panel->addWidget(pmdstop,15,2,1,4,Qt::AlignCenter);
    panel->addWidget(pmdshowinvalid,16,2,1,4,Qt::AlignCenter);
    panel->addWidget(pmdshowgrid,17,2,1,4,Qt::AlignCenter);
    panel->addWidget(depth,18,2,1,4,Qt::AlignCenter);
    panel->addWidget(slider,19,2,1,4,Qt::AlignCenter);
    panel->addWidget(space,20,2,1,4,Qt::AlignCenter);
panel->addWidget(copyright,21,2,1,4,Qt::AlignCenter);

    left->addLayout(panel);

    main->addLayout(left);

    mm1->setDisabled(true);
    mm2->setDisabled(true);
    begin->setDisabled(true);
    end->setDisabled(true);
    lbegin->setDisabled(true);
    lend->setDisabled(true);
    pmdshowlayer->setDisabled(true);
    c->setDisabled(true);

    QObject::connect(change,SIGNAL(clicked()),this,
                     SLOT(changeView()));
    QObject::connect(backDef,SIGNAL(clicked()),this,
                     SLOT(backDefault()));
    QObject::connect(pmdconnect,SIGNAL(clicked()),this,
                     SLOT(pmdConnect()));
    QObject::connect(pmddisconnect,SIGNAL(clicked()),this,
                     SLOT(pmdDisconnect()));
    QObject::connect(pmdauto,SIGNAL(clicked()),this,
                     SLOT(pmdAuto()));
    QObject::connect(pmdshowlayer,SIGNAL(clicked()),this,
                     SLOT(sendData()));
    QObject::connect(pmdmanual,SIGNAL(clicked()),this,
                     SLOT(manual()));
    QObject::connect(pmdstop,SIGNAL(clicked()),this,
                     SLOT(pmdStop()));
    QObject::connect(pmdtopview,SIGNAL(clicked()),this,
                     SLOT(switchtop()));

    QObject::connect(pmdquadspoints,SIGNAL(clicked()),this,
                     SLOT(switchquadspoints()));

    QObject::connect(pmdshowinvalid,SIGNAL(clicked()),this,
                     SLOT(showInvalid()));

    QObject::connect(pmdshowgrid,SIGNAL(clicked()),this,
                     SLOT(showGrid()));
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));


    Dialog::setLayout(main);

    pmdconnect->setDisabled(true);
    pmdstop->setDisabled(false);
    pmdauto->setDisabled(false);
    pmdmanual->setDisabled(false);
    change->setDisabled(false);
    backDef->setDisabled(false);
    pmddisconnect->setDisabled(false);
    ldef->setDisabled(false);
    lview->setDisabled(false);
    c->setDisabled(false);
    changelabel->setDisabled(false);
    pmdtopview->setDisabled(false);
    //pmdquadspoints->setDisabled(false);
    pmdshowinvalid->setDisabled(false);
    pmdshowgrid->setDisabled(false);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), p, SLOT(update()));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateColorBar()));
    timer->start(0);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::valueChanged(int value)
{

    emit p->changeValue(value);
}

void Dialog::switchtop()
{
    emit p->pmdtopview();
}

void Dialog::showInvalid()
{
    emit p->showinvalid();
    if (!p->invalid) pmdshowinvalid->setText("Remove bad pixels");
    else pmdshowinvalid->setText("Show bad pixels");
}

void Dialog::switchquadspoints()
{
    emit p->pmdquadspoints();
    if (p->qpmode=='q') pmdquadspoints->setText("Dotted view");
    else pmdquadspoints->setText("Surface view");
}

void Dialog::showGrid()
{
    emit p->showgrid();
    if (p->grid) pmdshowgrid->setText("Remove grid");
    else pmdshowgrid->setText("Show grid");
}

void Dialog::changeView()
{
    if (p->mode=='i') change->setText("Intensity");
    else change->setText("Distance");
    emit p->changeView();

}

void Dialog::sendData()
{
    emit p->showLayer(begin->text(),end->text());
}

void Dialog::manual()
{
    mm1->setDisabled(false);
    mm2->setDisabled(false);
    begin->setDisabled(false);
    end->setDisabled(false);
    lbegin->setDisabled(false);
    lend->setDisabled(false);
    pmdshowlayer->setDisabled(false);
    emit p->showLayer(begin->text(),end->text());
}

void Dialog::pmdAuto()
{
    mm1->setDisabled(true);
    mm2->setDisabled(true);
    begin->setDisabled(true);
    end->setDisabled(true);
    lbegin->setDisabled(true);
    lend->setDisabled(true);
    pmdshowlayer->setDisabled(true);
    emit p->pmdauto();
}

void Dialog::pmdConnect()
{
    emit p->PMDConnect();
        pmdconnect->setDisabled(true);
        pmdstop->setDisabled(false);
        pmdauto->setDisabled(false);
        pmdmanual->setDisabled(false);
        change->setDisabled(false);
        backDef->setDisabled(false);
        pmddisconnect->setDisabled(false);
        ldef->setDisabled(false);
        lview->setDisabled(false);
        c->setDisabled(false);
        changelabel->setDisabled(false);
        pmdtopview->setDisabled(false);
        pmdquadspoints->setDisabled(false);
        pmdshowinvalid->setDisabled(false);
        pmdshowgrid->setDisabled(false);
pmdshowinvalid->setText("Show bad pixels");
pmdshowgrid->setText("Remove grid");
}

void Dialog::pmdDisconnect()
{

    emit p->PMDDisconnect();
    pmdconnect->setDisabled(false);
    pmdstop->setDisabled(true);
    pmdauto->setDisabled(true);
    pmdmanual->setDisabled(true);
    change->setDisabled(true);
    backDef->setDisabled(true);
    pmddisconnect->setDisabled(true);
    ldef->setDisabled(true);
    lview->setDisabled(true);
    begin->setText("");
    end->setText("");
    mm1->setDisabled(true);
    mm2->setDisabled(true);
    begin->setDisabled(true);
    end->setDisabled(true);
    lbegin->setDisabled(true);
    lend->setDisabled(true);
    pmdshowlayer->setDisabled(true);
    c->setDisabled(true);
    changelabel->setDisabled(true);
    pmdstop->setText("Stop");
    pmdtopview->setDisabled(true);
    pmdquadspoints->setDisabled(true);
    pmdshowinvalid->setDisabled(true);
    pmdshowinvalid->setText("Show bad pixels");

    pmdquadspoints->setText("Dotted view");
    pmdshowgrid->setDisabled(true);
    pmdshowgrid->setText("Remove grid");


    p->layer=false;
}

void Dialog::backDefault()
{
    if (p->layer)
    {
      //  p->layer=false;
        mm1->setDisabled(true);
        mm2->setDisabled(true);
        begin->setDisabled(true);
        end->setDisabled(true);
        lbegin->setDisabled(true);
        lend->setDisabled(true);
        pmdshowlayer->setDisabled(true);
    }
    emit p->backDefault();
}

void Dialog::pmdStop()
{
    if (!p->stop) pmdstop->setText("Start");
    else pmdstop->setText("Stop");
    p->stop=!p->stop;

}

void Dialog::showvalues()
{
    float minI=p->minI;
    float minD=p->minD;
    float maxI=p->maxI;
    float maxD=p->maxD;
    char mode=p->mode;
    char s[100];

}

void Dialog::updateColorBar()
{
    c->minD=p->minD;
    c->maxD=p->maxD;
    c->minI=p->minI;
    c->maxI=p->maxI;
    c->mode=p->mode;
    emit c->update();
}
