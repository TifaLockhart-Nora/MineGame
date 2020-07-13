#ifndef HERODIALOG_H
#define HERODIALOG_H

/**********************
*FileName: heridialog.h
*Author: ��ǿ
*Version: 1.0
*Date: 2020��5��9��
*Description:  Ӣ�۰�����
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
    QLabel *lowrecordtimelabel;     //��ģʽ��¼ʱ���ǩ
    QLabel *middlerecordtimelabel;  //����ģʽ��¼ʱ���ǩ
    QLabel *heightrecordtimelabel;  //��սģʽ��¼ʱ���ǩ
    QLabel *lowrecordnamelabel;     //��ģʽ��¼���ֱ�ǩ
    QLabel *middlerecordnamelabel;  //����ģʽ��¼���ֱ�ǩ
    QLabel *heightrecordnamelabel;  //��սģʽ��¼���ֱ�ǩ
    QSettings *settings;            //Ӣ�۰�����ע���

    void readsettings();            //��ȡӢ�۰�����ע�����
    void init_herorecord();         //��ʼ��Ӣ�۰��¼�����ݺ���
public slots:
    void slot_reset();              //��������Ӣ�۰�����ݲۺ���
};

#endif // HERODIALOG_H
