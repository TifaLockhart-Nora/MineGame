#ifndef COMMON_H
#define COMMON_H

/***********************************
*FileName: Common.h
*Author: 阿强
*Version: 1.0
*Date: 2020年5月8日
*Description:  游戏的一些基本设置
************************************/

class Common
{
public:
    /*游戏等级*/
    enum gameLeve
    {
        LOWLEVE = 0,       //简单模式
        MIDDLEVE = 1,      //困难模式
        HEIGHTLEVE = 2,    //挑战模式
        CUSTOMLEVE = 3     //自定义模式
    };

    /*简单模式行列数，雷数*/
    enum lowset
    {
        LOWROWANDCOL = 9,
        LOWMINENUM = 10
    };

     /*困难模式行列数，雷数*/
    enum middleset
    {
      MIDDLEROWANDCOL = 16,
      MIDDLEMINENUM = 40
    };

     /*挑战模式行列数，雷数*/
    enum heightset
    {
        HEIGHTROW = 25,
        HEIGHTCOL = 30,
        HEIGHTMINENUM = 99
    };

     /*地雷图片大小设置*/
    enum mapset
    {
        MAPWIDTH = 25,
        MAPHEIGHT = 25
    };

};

#endif // COMMON_H
