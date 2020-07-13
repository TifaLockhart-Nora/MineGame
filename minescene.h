#ifndef MINESCENE_H
#define MINESCENE_H

/**********************
*FileName: minscene.h
*Author: 阿强
*Version: 2.0
*Date: 2020年5月12日
*Description: 地雷场景设置
**********************/

#include <QObject>
#include <QGraphicsScene>
#include <QVector>
#include "mineitem.h"
#include "Common.h"
#include <time.h>

class MineScene :public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MineScene(QObject *parent = nullptr);
    QVector<QVector<Mineitem *>> m_itemVec;   // 存储方块的容器
    int m_scenerow;     //当前场景行数
    int m_scenecol;     //当前场景列数
    int m_minesum;      //当前场景雷数
    int m_currentLeve;  //当前场景级别
    int m_signalMineNum;//右键标记的雷数
    int m_rightMineNum; //右键标记正确的雷数
    bool m_isGameOver;  //游戏是否结束
    int m_remainNoMines;//剩余非雷数
    bool m_soundOpen;   //声音开关: true: 打开声音 false: 关闭声音
    bool timer_flag;    //定时器标志位

    /**********************
     * 参数：@t_item 当前方块
     * 功能：统计周围雷数
     * 返回值：无
     ********************/
    void countArountMines(Mineitem *t_item);

    /**********************
     * 参数：@t_item 当前方块
     * 功能：扩散函数
     * 返回值：无
     *********************/
    void expendWater(Mineitem *t_item);
    void initScene();                        //初始化场景
    void openAllItem();                      //打开所有方块
signals:
    void signal_successPassGame();           //游戏通关信号
    void signal_scenenewGame();              //开始新游戏信号
    void signal_scenedisplayMineNum(int);    //显示雷数信号
    void signal_scenebutton();               //笑脸按钮信号
    void signal_scenetimerflag();            //定时器信号
};

#endif // MINESCENE_H
