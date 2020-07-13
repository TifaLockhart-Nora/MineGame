#ifndef MINESCENE_H
#define MINESCENE_H

/**********************
*FileName: minscene.h
*Author: ��ǿ
*Version: 2.0
*Date: 2020��5��12��
*Description: ���׳�������
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
    QVector<QVector<Mineitem *>> m_itemVec;   // �洢���������
    int m_scenerow;     //��ǰ��������
    int m_scenecol;     //��ǰ��������
    int m_minesum;      //��ǰ��������
    int m_currentLeve;  //��ǰ��������
    int m_signalMineNum;//�Ҽ���ǵ�����
    int m_rightMineNum; //�Ҽ������ȷ������
    bool m_isGameOver;  //��Ϸ�Ƿ����
    int m_remainNoMines;//ʣ�������
    bool m_soundOpen;   //��������: true: ������ false: �ر�����
    bool timer_flag;    //��ʱ����־λ

    /**********************
     * ������@t_item ��ǰ����
     * ���ܣ�ͳ����Χ����
     * ����ֵ����
     ********************/
    void countArountMines(Mineitem *t_item);

    /**********************
     * ������@t_item ��ǰ����
     * ���ܣ���ɢ����
     * ����ֵ����
     *********************/
    void expendWater(Mineitem *t_item);
    void initScene();                        //��ʼ������
    void openAllItem();                      //�����з���
signals:
    void signal_successPassGame();           //��Ϸͨ���ź�
    void signal_scenenewGame();              //��ʼ����Ϸ�ź�
    void signal_scenedisplayMineNum(int);    //��ʾ�����ź�
    void signal_scenebutton();               //Ц����ť�ź�
    void signal_scenetimerflag();            //��ʱ���ź�
};

#endif // MINESCENE_H
