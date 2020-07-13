#ifndef COMMON_H
#define COMMON_H

/***********************************
*FileName: Common.h
*Author: ��ǿ
*Version: 1.0
*Date: 2020��5��8��
*Description:  ��Ϸ��һЩ��������
************************************/

class Common
{
public:
    /*��Ϸ�ȼ�*/
    enum gameLeve
    {
        LOWLEVE = 0,       //��ģʽ
        MIDDLEVE = 1,      //����ģʽ
        HEIGHTLEVE = 2,    //��սģʽ
        CUSTOMLEVE = 3     //�Զ���ģʽ
    };

    /*��ģʽ������������*/
    enum lowset
    {
        LOWROWANDCOL = 9,
        LOWMINENUM = 10
    };

     /*����ģʽ������������*/
    enum middleset
    {
      MIDDLEROWANDCOL = 16,
      MIDDLEMINENUM = 40
    };

     /*��սģʽ������������*/
    enum heightset
    {
        HEIGHTROW = 25,
        HEIGHTCOL = 30,
        HEIGHTMINENUM = 99
    };

     /*����ͼƬ��С����*/
    enum mapset
    {
        MAPWIDTH = 25,
        MAPHEIGHT = 25
    };

};

#endif // COMMON_H
