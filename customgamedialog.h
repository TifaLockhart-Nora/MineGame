#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

/****************************
*FileName: customgamedialog.h
*Author: 阿强
*Version: 1.0
*Date: 2020年5月8日
*Description:  自定义游戏框的设置
*****************************/

#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QSettings>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

/**************自定义游戏类****************/
class Customgamedialog : public QDialog
{
    Q_OBJECT
public:
    explicit Customgamedialog(QWidget *parent = nullptr);
    QSpinBox *rowspinbox;           //自定义行数
    QSpinBox *colspinbox;           //自定义列数
    QSpinBox *minenumspinbox;       //自定义雷数
    QSettings *settings;            //自定义设置数据的注册表
    void readsettings();            //读注册表函数
    void writesetting();            //写注册表函数

signals:
    /***********************
     参数：@row 自定义设置行数
          @col 自定义设置列数
          @mines 自定义设置雷数
     功能：发送自定义设置完成信号
     返回值：无
    ************************/
    void signal_sendCustomset(int row,int col,int mines);
public slots:
    void slot_acceptok();        //自定义设置完成的槽函数
};

#endif // CUSTOMGAMEDIALOG_H
