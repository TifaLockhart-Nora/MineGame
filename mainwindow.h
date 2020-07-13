#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/***********************
*FileName: mainwindow.h
*Author: 阿强
*Version: 1.0
*Date: 2020年5月10日
*Description: 主窗口
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
    QAction *newaction;             //开始游戏
    QAction *lowleveaction;         //简单模式
    QAction *middleleveaction;      //困难模式
    QAction *heightleveaction;      //挑战模式
    QAction *customaction;          //自定义模式
    QAction *coloraction;           //颜色设置
    QAction *soundaction;           //声音设置
    QAction *heroaction;            //英雄榜设置
    QAction *exitaction;            //退出游戏
    QAction *aboutaction;           //关于游戏

    QGraphicsView *mineView;    //主视图
    QPushButton *smilebutton;   //笑脸按钮
    QLCDNumber *mineNumLcd;     //雷数显示LCD
    QLCDNumber *timeLcd;        //时间显示LCD
    MineScene  *minScene;       //场景
    QSettings  *settings;       //游戏级别的数据注册表
    QWidget    *centralget;     //中心组件
    QSound *sound;              //特效声音
    QSound *BlackGround_sound;  //背景音乐
    QTimer *m_timer;            //定时器
    int    m_time;              //时间计数

    void goodGame();            //游戏结束后的设置函数
    void creatMenu();           //创建菜单
    void creatAction();         //创建行为
    void readSettings();        //读游戏级别数据注册表
    void writeSettings();       //写游戏级别数据到注册表
public slots:
    /***********************
     参数：@rows:    自定义行
          @cols:    自定义列
          @mines:   自定义雷数
     功能：接收自定义游戏的设置
     返回值：无
    ************************/
    void slot_accpetCustomval(int rows,int cols,int mines);

    /***********************
     参数：@action 游戏级别
     功能：选择游戏级别
     返回值：无
    ************************/
    void slot_newGameLeve(QAction *action);


    /***********************
     参数：@mines 显示的数值
     功能：显示雷数
     返回值：无
    ************************/
    void slot_displayMineNum(int mines);
    void slot_buttonChange();                                //笑脸按钮设置
    void slot_displayTime();                                 //显示游戏时间
    void slot_colorChange();                                 //颜色设置
    void slot_soundChange();                                 //声音设置
    void slot_updateHero();                                  //更新英雄榜
    void slot_timerflag();                                   //定时器设置
    void slot_showHero();                                    //显示英雄榜
    void slot_newGame();                                     //开始新游戏
    void slot_about();                                       //关于游戏
};
#endif // MAINWINDOW_H
