#include "herodialog.h"
#include <QDebug>

Herodialog::Herodialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("MyHero");
    QLabel *label_1 = new QLabel("LEVE");
    QLabel *label_2 = new QLabel("TIME");
    QLabel *label_3 = new QLabel("NAME");

    QLabel *low_label = new QLabel("LOW");
    QLabel *middle_label = new QLabel("MIDDLE");
    QLabel *height_label = new QLabel("HEIGHT");

    lowrecordtimelabel = new QLabel;
    middlerecordtimelabel = new QLabel;
    heightrecordtimelabel = new QLabel;

    lowrecordnamelabel = new QLabel;
    middlerecordnamelabel = new QLabel;
    heightrecordnamelabel = new QLabel;

    QPushButton *ok_button = new QPushButton("EXIT");
    QPushButton *reset_button = new QPushButton("Reset");
    this->connect(ok_button,SIGNAL(clicked(bool)),this,SLOT(close()));
    this->connect(reset_button,SIGNAL(clicked(bool)),this,SLOT(slot_reset()));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(label_1,0,0);
    layout->addWidget(label_2,0,1);
    layout->addWidget(label_3,0,2);

    layout->addWidget(low_label,1,0);
    layout->addWidget(lowrecordtimelabel,1,1);
    layout->addWidget(lowrecordnamelabel,1,2);

    layout->addWidget(middle_label,2,0);
    layout->addWidget(middlerecordtimelabel,2,1);
    layout->addWidget(middlerecordnamelabel,2,2);

    layout->addWidget(height_label,3,0);
    layout->addWidget(heightrecordtimelabel,3,1);
    layout->addWidget(heightrecordnamelabel,3,2);

    layout->addWidget(ok_button,4,0);
    layout->addWidget(reset_button,4,1);
    settings = new QSettings("HERO","MyHero",this);
    this->readsettings();
}

void Herodialog::readsettings()
{
    settings->beginGroup("time_name");
    QString lowtime = settings->value("low_time").toString();
    QString lowname = settings->value("low_name").toString();
    QString middletime = settings->value("middle_time").toString();
    QString middlename = settings->value("middle_name").toString();
    QString heighttime = settings->value("height_time").toString();
    QString heightname = settings->value("height_name").toString();
    settings->endGroup();
    this->lowrecordtimelabel->setText(lowtime);
    this->lowrecordnamelabel->setText(lowname);
    this->middlerecordtimelabel->setText(middletime);
    this->middlerecordnamelabel->setText(middlename);
    this->heightrecordtimelabel->setText(heighttime);
    this->heightrecordnamelabel->setText(heightname);
}

void Herodialog::init_herorecord()
{
    settings->beginGroup("time_name");
    settings->setValue("low_time",999);
    settings->setValue("low_name","Alice");
    settings->setValue("middle_time",999);
    settings->setValue("middle_name","Lucy");
    settings->setValue("height_time",999);
    settings->setValue("height_name","Jim");
    settings->endGroup();
}

void Herodialog::slot_reset()
{
    this->init_herorecord();
    readsettings();
}
