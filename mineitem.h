#ifndef MINEITEM_H
#define MINEITEM_H

/********************
*FileName: mineitem.h
*Author: ��ǿ
*Version: 1.0
*Date: 2020��5��11��
*Description: ��������
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
     * ������@t_x ��ǰ��������
     *      @t_y ��ǰ��������
     *      @itempixmap ����ͼƬ
     * ���ܣ�����ĵĹ��캯�������÷����ͼƬ
     *********************************/
    explicit Mineitem(int t_x,int t_y,QPixmap itempixmap,QGraphicsItem *parent = nullptr);
    int m_X;                    //�����е�����
    int m_Y;                    //�����е�����
    bool m_isMine;              //��ǰ�����Ƿ�����
    bool m_isOpen;              //��ǰ�����Ƿ��
    int m_aroundMineNum;        //��ǰ������Χ����
    int m_rMouseClickNum;       //��ǰ�����Ҽ��������
    bool m_isRightButtonflag;   //��ǰ�����Ҽ��Ƿ񱻱��
    void mousePressEvent(QGraphicsSceneMouseEvent *e);       //��갴���¼�
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);     //����ͷ��¼�
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e); //���˫���¼�
signals:
    void signal_restartGame();          //���¿�ʼ��Ϸ�ź�
    void signal_resetMineNum(int);      //���²����ź�
    void signal_buttonChange();         //Ц����ť�ı��ź�
    void signal_timerflag();            //��ʱ����ʼ�����ź�
};

#endif // MINEITEM_H
