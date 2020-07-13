#ifndef MINEITEM_H
#define MINEITEM_H

/********************
*FileName: mineitem.h
*Author: 阿强
*Version: 1.0
*Date: 2020年5月11日
*Description: 地雷设置
********************/

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QSound>
#include <QMessageBox>


class Mineitem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    /**********************************
     * 参数：@t_x 当前方块行数
     *      @t_y 当前方块列数
     *      @itempixmap 方块图片
     * 功能：方块的的构造函数，设置方块的图片
     *********************************/
    explicit Mineitem(int t_x,int t_y,QPixmap itempixmap,QGraphicsItem *parent = nullptr);
    int m_X;                    //容器中的行数
    int m_Y;                    //容器中的列数
    bool m_isMine;              //当前方块是否是雷
    bool m_isOpen;              //当前方块是否打开
    int m_aroundMineNum;        //当前方块周围雷数
    int m_rMouseClickNum;       //当前方块右键点击次数
    bool m_isRightButtonflag;   //当前方块右键是否被标记
    void mousePressEvent(QGraphicsSceneMouseEvent *e);       //鼠标按下事件
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);     //鼠标释放事件
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e); //鼠标双击事件
signals:
    void signal_restartGame();          //重新开始游戏信号
    void signal_resetMineNum(int);      //重新布雷信号
    void signal_buttonChange();         //笑脸按钮改变信号
    void signal_timerflag();            //定时器开始工作信号
};

#endif // MINEITEM_H
