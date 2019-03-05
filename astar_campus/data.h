#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdbool.h>
//A*的基本存储结构
const int MAX_number=9; //这是地图的最大值，可以自己修改以符合实际需求
int n;//实际地图的长宽
//一个比较基础的结构体，用于和地图联动
struct baseNode
{
    int i;
    int j;
    int weigt;

    int f;
    int g;
    int h;

    struct baseNode *father;
};
bool FLAG;
int AstackCount;
struct baseNode Astack[100]; //最优路径记录数组
int neibNum = 0;
struct baseNode Neibo[8]; //邻居列表，用于记录每个当前点的所有邻居

//定义了一个全局变量用来存储二维矩阵地图
struct baseNode map[MAX_number][MAX_number];

//记录起点和终点的数组，起点为Ascenery[0],终点为Ascenery[1]
struct baseNode AsceneryList[2];

//开启列表，用于A*算法
struct baseNode OpenList[MAX_number*MAX_number];

//关闭列表，用于A*算法
struct baseNode CloseList[MAX_number*MAX_number];

//用于记录开启列表中元素的个数
int openListCount = 0;

//用于记录关闭列表中元素的个数
int closeListCount = 0;

#endif // DATA_H_INCLUDED
