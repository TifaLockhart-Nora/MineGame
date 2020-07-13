#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

/****************************
*FileName: customgamedialog.h
*Author: ��ǿ
*Version: 1.0
*Date: 2020��5��8��
*Description:  �Զ�����Ϸ�������
*****************************/

#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QSettings>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

/**************�Զ�����Ϸ��****************/
class Customgamedialog : public QDialog
{
    Q_OBJECT
public:
    explicit Customgamedialog(QWidget *parent = nullptr);
    QSpinBox *rowspinbox;           //�Զ�������
    QSpinBox *colspinbox;           //�Զ�������
    QSpinBox *minenumspinbox;       //�Զ�������
    QSettings *settings;            //�Զ����������ݵ�ע���
    void readsettings();            //��ע�����
    void writesetting();            //дע�����

signals:
    /***********************
     ������@row �Զ�����������
          @col �Զ�����������
          @mines �Զ�����������
     ���ܣ������Զ�����������ź�
     ����ֵ����
    ************************/
    void signal_sendCustomset(int row,int col,int mines);
public slots:
    void slot_acceptok();        //�Զ���������ɵĲۺ���
};

#endif // CUSTOMGAMEDIALOG_H
