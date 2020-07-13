#include "mineitem.h"
#include "minescene.h"
#include "mainwindow.h"
#include <QDebug>
Mineitem::Mineitem(int t_x,int t_y,QPixmap itempixmap, QGraphicsItem *parent) : QGraphicsPixmapItem(itempixmap)
{
    m_X = t_x;
    m_Y = t_y;
    m_isMine = false;
    m_isOpen =false;
    m_isRightButtonflag = false;
    m_aroundMineNum = 0;
    m_rMouseClickNum = 0;
}


void Mineitem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    MineScene *minescene = (MineScene *)this->scene();
    if(minescene->m_isGameOver || this->m_isOpen)
        return;
    if(e->button() == Qt::LeftButton)
    {
        emit signal_timerflag();
        if(!m_isRightButtonflag)
        {
            m_isRightButtonflag = true;
            this->setPixmap(QPixmap(":/images/mine1_0.png"));
        }
        if(m_rMouseClickNum == 0)
            m_isRightButtonflag = false;
    }
    else if(e->button() == Qt::RightButton)
    {
        m_rMouseClickNum ++;
        if(m_rMouseClickNum == 1)
        {
            m_isRightButtonflag = true;
            minescene->m_signalMineNum++;
            this->setPixmap(QPixmap(":images/flag1.png"));
            emit signal_resetMineNum(minescene->m_signalMineNum);  //重新设置雷数信号
            if(this->m_isMine)
                minescene->m_rightMineNum++;        
        }
        if(m_rMouseClickNum == 2)
        {
            minescene->m_signalMineNum--;
            this->setPixmap(QPixmap(":/images/interrogation1_0.png"));
            emit signal_resetMineNum(minescene->m_signalMineNum);   //重新设置雷数信号
            if(this->m_isMine)
            {
                 minescene->m_rightMineNum--;
                 if(minescene->m_rightMineNum == 1)
                     minescene->m_rightMineNum = 0;
            }
        }
        if(m_rMouseClickNum == 3)
        {
            this->setPixmap(QPixmap(":/images/cover1.png"));
            m_rMouseClickNum = 0;
        }
    }
}


void Mineitem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    MineScene *minesc = (MineScene*)this->scene();
    if(minesc->m_isGameOver || m_isOpen || m_isRightButtonflag)
        return;
    if(e->button() == Qt::LeftButton)
    {
        if(this->m_rMouseClickNum == 1)
            return;
        m_isOpen = true;
        if(this->m_isMine)
        {
            this->setPixmap(QPixmap(":/images/minetip0.png"));
            if(minesc->m_soundOpen)
                QSound::play(":/sound/File0004.wav");
            minesc->openAllItem();
            minesc->m_isGameOver = true;
            emit signal_buttonChange();
            QMessageBox::critical((QWidget*)minesc->parent(),"Warning","Game Over!",QMessageBox::Ok);
            emit signal_restartGame();
            return;
        }
        else
        {
            if(m_aroundMineNum == 0)
            {
                this->setPixmap(QPixmap(":/images/mine1_0.png"));
                minesc->expendWater(this);
            }
            else
            {
                QString path = tr(":/images/") + QString::number(m_aroundMineNum) + tr(".png");
                this->setPixmap(QPixmap(path));
            }
        }
        minesc->m_remainNoMines--;
        if(minesc->m_remainNoMines == 0)
        {
            minesc->m_isGameOver = true;
            if(minesc->m_soundOpen)
                QSound::play(":/sound/File0015.wav");
            minesc->openAllItem();
            emit minesc->signal_successPassGame();
        }
    }
}


void Mineitem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
{
//    MineScene *minescene_double = (MineScene*)this->scene();
//    if(e->button() == Qt::LeftButton || e->button() == Qt::RightButton)
//    {
//        qDebug()<<"DoubleClick"<<endl;
//        if(!this->m_isMine)
//        {
//        }
//    }
}
