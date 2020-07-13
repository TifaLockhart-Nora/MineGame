#ifndef HERODIALOG_H
#define HERODIALOG_H

/**********************
*FileName: heridialog.h
*Author: 阿强
*Version: 1.0
*Date: 2020年5月9日
*Description:  英雄榜设置
***********************/

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSettings>

class Herodialog : public QDialog
{
    Q_OBJECT
public:
    explicit Herodialog(QWidget *parent = nullptr);
    QLabel *lowrecordtimelabel;     //简单模式记录时间标签
    QLabel *middlerecordtimelabel;  //困难模式记录时间标签
    QLabel *heightrecordtimelabel;  //挑战模式记录时间标签
    QLabel *lowrecordnamelabel;     //简单模式记录名字标签
    QLabel *middlerecordnamelabel;  //困难模式记录名字标签
    QLabel *heightrecordnamelabel;  //挑战模式记录名字标签
    QSettings *settings;            //英雄榜数据注册表

    void readsettings();            //读取英雄榜数据注册表函数
    void init_herorecord();         //初始化英雄榜记录的数据函数
public slots:
    void slot_reset();              //重新设置英雄榜的数据槽函数
};

#endif // HERODIALOG_H
