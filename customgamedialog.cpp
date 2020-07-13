#include "customgamedialog.h"

Customgamedialog::Customgamedialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Custom Game");
    QLabel *row_label = new QLabel("Row");
    QLabel *col_label = new QLabel("Col");
    QLabel *minenum_label = new QLabel("Mines");
    rowspinbox = new QSpinBox;
    rowspinbox->setRange(10,100);
    rowspinbox->setValue(10);
    rowspinbox->setSingleStep(1);

    colspinbox = new QSpinBox;
    colspinbox->setRange(10,100);
    colspinbox->setValue(10);
    colspinbox->setSingleStep(1);

    minenumspinbox = new QSpinBox;
    minenumspinbox->setRange(1,100);
    minenumspinbox->setValue(10);
    minenumspinbox->setSingleStep(2);

    QPushButton *ok_button = new QPushButton("OK");
    QPushButton *cancle_button = new QPushButton("Cancle");

    QGridLayout *glayout = new QGridLayout(this);
    glayout->addWidget(row_label,0,0);
    glayout->addWidget(rowspinbox,0,1);
    glayout->addWidget(col_label,1,0);
    glayout->addWidget(colspinbox,1,1);
    glayout->addWidget(minenum_label,2,0);
    glayout->addWidget(minenumspinbox,2,1);
    glayout->addWidget(ok_button,3,0);
    glayout->addWidget(cancle_button,3,1);
    this->connect(ok_button,SIGNAL(clicked(bool)),this,SLOT(slot_acceptok()));
    this->connect(cancle_button,SIGNAL(clicked(bool)),this,SLOT(close()));
    settings = new QSettings("FINAL","MyMines",this);   
    this->readsettings();
}


void Customgamedialog::readsettings()
{
    settings->beginGroup("customGame");
    int row = settings->value("customrow",10).toInt();
    int col = settings->value("customcol",10).toInt();
    int mines = settings->value("custommines",10).toInt();
    settings->endGroup();

    rowspinbox->setValue(row);
    colspinbox->setValue(col);
    minenumspinbox->setValue(mines);   
}


void Customgamedialog::writesetting()
{
    settings->beginGroup("customGame");
    settings->setValue("customrow",this->rowspinbox->value());
    settings->setValue("customcol",this->colspinbox->value());
    settings->setValue("custommines",this->minenumspinbox->value());
    settings->endGroup();
}


void Customgamedialog::slot_acceptok()
{
    int row = rowspinbox->value();
    int col = colspinbox->value();
    int mines = minenumspinbox->value();

    emit this->signal_sendCustomset(row,col,mines);
    this->writesetting();
    this->close(); 
}
