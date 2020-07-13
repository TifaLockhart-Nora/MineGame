#include "minescene.h"
#include <QDebug>

QPoint t_around[8] =
{
    QPoint(-1,-1),
    QPoint(-1,0),
    QPoint(-1,1),
    QPoint(0,-1),
    QPoint(0,1),
    QPoint(1,-1),
    QPoint(1,0),
    QPoint(1,1)
};


MineScene::MineScene(QObject *parent) : QGraphicsScene(parent)
{
    m_isGameOver = false;
    m_soundOpen = true;
    timer_flag = false;
    m_signalMineNum = 0;
    m_rightMineNum = 0;
}


void MineScene::initScene()
{
    m_remainNoMines = m_scenecol * m_scenerow - m_minesum;
    for(int i = 0;i < m_scenerow;i++)
    {
        QVector<Mineitem *> m_Vec;
        for(int j = 0;j < m_scenecol;j++ )
        {
            Mineitem *item = new Mineitem(i,j,QPixmap(":/images/cover1.png"));
            item->setPos(j * Common::MAPWIDTH,i * Common::MAPHEIGHT);
            this->addItem(item);
            m_Vec.push_back(item);
        }
        this->m_itemVec.push_back(m_Vec);
    }
    srand(time(0));
    for(int i = 0; i < m_minesum;i++)
    {
         int t_row = rand()%m_scenerow;
         int t_col = rand()%m_scenecol;
         if(!this->m_itemVec[t_row][t_col]->m_isMine)
         {
            this->m_itemVec[t_row][t_col]->m_isMine = true;
            this->countArountMines(this->m_itemVec[t_row][t_col]);
         }
         else
             i--;
    }
    for(int i = 0;i < m_scenerow;i++)
    {
        for(int j = 0;j < m_scenecol;j++)
        {
            this->connect(this->m_itemVec[i][j],SIGNAL(signal_restartGame()),this,SIGNAL(signal_scenenewGame()));
            this->connect(this->m_itemVec[i][j],SIGNAL(signal_resetMineNum(int)),this,SIGNAL(signal_scenedisplayMineNum(int)));
            this->connect(this->m_itemVec[i][j],SIGNAL(signal_buttonChange()),this,SIGNAL(signal_scenebutton()));
            this->connect(this->m_itemVec[i][j],SIGNAL(signal_timerflag()),this,SIGNAL(signal_scenetimerflag()));
        }
    }
}


void MineScene::countArountMines(Mineitem *t_item)
{
   if(NULL == t_item || !t_item->m_isMine)
       return;
   for(int i = 0;i < 8;i++)
   {
       int item_x = t_item->m_X + t_around[i].x();
       int item_y = t_item->m_Y + t_around[i].y();
       if(item_x < 0 || item_x >= this->m_scenerow || item_y < 0 || item_y >= this->m_scenecol )
           continue;
       if(m_itemVec[item_x][item_y]->m_isMine)
           continue;
       m_itemVec[item_x][item_y]->m_aroundMineNum++;
   }
}


void MineScene::openAllItem()
{
    for(int i = 0;i < this->m_scenerow ;i++)
    {
        for(int j = 0;j< this->m_scenecol;j++)
        {
            m_itemVec[i][j]->m_isOpen = true;
            if(m_itemVec[i][j]->m_isMine)
                m_itemVec[i][j]->setPixmap(QPixmap(":/images/minetip0.png"));
            else
            {
                QString path = tr(":/images/") + QString::number(m_itemVec[i][j]->m_aroundMineNum)+ tr(".png");
                m_itemVec[i][j]->setPixmap(QPixmap(path));
            }
        }
    }
}


void MineScene::expendWater(Mineitem *t_item)
{
    if(NULL == t_item || t_item->m_isMine )
        return;
    for(int k = 0;k < 8;k++)
    {
        int item_x = t_item->m_X + t_around[k].x();
        int item_y = t_item->m_Y + t_around[k].y();
        if(item_x < 0 || item_x >= this->m_scenerow || item_y < 0 || item_y >= this->m_scenecol)
            continue;
        else if(m_itemVec[item_x][item_y]->m_isMine || m_itemVec[item_x][item_y]->m_isOpen)
            continue;
        else if(m_itemVec[item_x][item_y]->m_rMouseClickNum)
            continue;
        m_itemVec[item_x][item_y]->m_isOpen = true;
        this->m_remainNoMines--;
        if(m_itemVec[item_x][item_y]->m_aroundMineNum == 0 )
        {
            m_itemVec[item_x][item_y]->setPixmap(QPixmap(":/images/mine1_0.png"));
            this->expendWater(m_itemVec[item_x][item_y]);
        }
        else
        {
            QString path = tr(":/images/") + QString::number(m_itemVec[item_x][item_y]->m_aroundMineNum)+ tr(".png");
            m_itemVec[item_x][item_y]->setPixmap(QPixmap(path));
        }

        if(this->m_remainNoMines == 0)
        {
            this->m_isGameOver = true;
            if(this->m_soundOpen)
                QSound::play(":/sound/File0015.wav");
            openAllItem();
            emit signal_successPassGame();
        }
    }
}
