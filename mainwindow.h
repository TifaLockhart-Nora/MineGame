#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/***********************
*FileName: mainwindow.h
*Author: ��ǿ
*Version: 1.0
*Date: 2020��5��10��
*Description: ������
***********************/

#include <QAbstractButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QActionGroup>
#include <QInputDialog>
#include <QMessageBox>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLCDNumber>
#include <QSettings>
#include <QLineEdit>
#include <QMenuBar>
#include <QAction>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QSound>
#include <QMenu>
#include "customgamedialog.h"
#include "herodialog.h"
#include "minescene.h"
#include "Common.h"
#include <QSplashScreen>
#include <QMovie>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction *newaction;             //��ʼ��Ϸ
    QAction *lowleveaction;         //��ģʽ
    QAction *middleleveaction;      //����ģʽ
    QAction *heightleveaction;      //��սģʽ
    QAction *customaction;          //�Զ���ģʽ
    QAction *coloraction;           //��ɫ����
    QAction *soundaction;           //��������
    QAction *heroaction;            //Ӣ�۰�����
    QAction *exitaction;            //�˳���Ϸ
    QAction *aboutaction;           //������Ϸ

    QGraphicsView *mineView;    //����ͼ
    QPushButton *smilebutton;   //Ц����ť
    QLCDNumber *mineNumLcd;     //������ʾLCD
    QLCDNumber *timeLcd;        //ʱ����ʾLCD
    MineScene  *minScene;       //����
    QSettings  *settings;       //��Ϸ���������ע���
    QWidget    *centralget;     //�������
    QSound *sound;              //��Ч����
    QSound *BlackGround_sound;  //��������
    QTimer *m_timer;            //��ʱ��
    int    m_time;              //ʱ�����

    void goodGame();            //��Ϸ����������ú���
    void creatMenu();           //�����˵�
    void creatAction();         //������Ϊ
    void readSettings();        //����Ϸ��������ע���
    void writeSettings();       //д��Ϸ�������ݵ�ע���
public slots:
    /***********************
     ������@rows:    �Զ�����
          @cols:    �Զ�����
          @mines:   �Զ�������
     ���ܣ������Զ�����Ϸ������
     ����ֵ����
    ************************/
    void slot_accpetCustomval(int rows,int cols,int mines);

    /***********************
     ������@action ��Ϸ����
     ���ܣ�ѡ����Ϸ����
     ����ֵ����
    ************************/
    void slot_newGameLeve(QAction *action);


    /***********************
     ������@mines ��ʾ����ֵ
     ���ܣ���ʾ����
     ����ֵ����
    ************************/
    void slot_displayMineNum(int mines);
    void slot_buttonChange();                                //Ц����ť����
    void slot_displayTime();                                 //��ʾ��Ϸʱ��
    void slot_colorChange();                                 //��ɫ����
    void slot_soundChange();                                 //��������
    void slot_updateHero();                                  //����Ӣ�۰�
    void slot_timerflag();                                   //��ʱ������
    void slot_showHero();                                    //��ʾӢ�۰�
    void slot_newGame();                                     //��ʼ����Ϸ
    void slot_about();                                       //������Ϸ
};
#endif // MAINWINDOW_H
