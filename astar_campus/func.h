#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data.h"

int manhatten(int, int);




 //优化：把一个元素插入开启列表中
void putInOpenList(struct baseNode inList)
{
    ++openListCount;

    OpenList[openListCount - 1] = inList;
    for (int i = openListCount - 1; i >0; i=(i-1)/2)
    {
        if (OpenList[i].f<OpenList[(i-1)/2].f)
        {
            OpenList[i]=OpenList[(i - 1) / 2];
            OpenList[(i - 1) / 2] = inList;
        }
        else
        {
            break;
        }
    }
}

//优化：取出开启列表中最小的数
struct baseNode readTopOpenList()
{
    return OpenList[0];
}

//优化：把一个元素加入关闭列表中
void putInCloseList(struct baseNode iter)
{
    CloseList[closeListCount] = iter;
    if(AsceneryList[1].i == iter.i && AsceneryList[1].j == iter.j)
    {
        FLAG=1;
    }

    struct baseNode temp;
    for (int i = closeListCount; i>0; --i)
    {
        if ((CloseList[i].i*MAX_number+CloseList[i].j+1)<(CloseList[i-1].i*MAX_number + CloseList[i-1].j + 1))
        {
            temp = CloseList[i];
            CloseList[i]=CloseList[i - 1];
            CloseList[i - 1] = temp;
        }
        else
        {
            break;
        }
    }
    ++closeListCount;
}

//优化：把开启列表中的当前节点删除（最小节点）
void outOpenList()
{
    --openListCount;

    OpenList[0]=OpenList[openListCount];
    struct baseNode temp;

    for (int i=0,p=0; 2*i+1<openListCount;i=p)
    {
        if (2*i+2>openListCount-1)
        {
            p = 2 * i + 1;
        }
        else
        {
            if (OpenList[2 * i + 1].f<OpenList[2 * i + 2].f)
            {
                p = 2 * i + 1;
            }
            else
            {
                p = 2 * i + 2;
            }
        }

        if (OpenList[p].f<OpenList[i].f)
        {
            temp=OpenList[p];
            OpenList[p]=OpenList[i];
            OpenList[i] = temp;
        }
        else
        {
            break;
        }
    }
}

//优化&&新加函数：删除开启列表中指定的元素，重构最小二叉堆
//（注：这个可以用很多方法实现，示例并非最优）
void outOpenList2(struct baseNode iter)
{
    int number=openListCount-1;
    struct baseNode openlist2[MAX_number*MAX_number];
    int j=0;
    for (int i = 0; i < openListCount; ++i)
    {
        if (OpenList[i].i==iter.i&&OpenList[i].j==iter.j)
        {
            continue;
        }
        openlist2[j]=OpenList[i];
        ++j;
    }

    openListCount = 0;
    for (int i = 0; i < number; ++i)
    {
        putInOpenList(openlist2[i]);
    }
}

//对于一路上的每个点，分析它的最多八个邻居，并加入邻居列表
void addNeibo(struct baseNode iter)
{
    neibNum = 0;

    for (int i = iter.i - 1; i <= iter.i + 1; ++i)
    {
        for (int j = iter.j - 1; j <= iter.j + 1; ++j)
        {
            if (i >= 0 && i <= MAX_number - 1 && j >= 0 && j <= MAX_number - 1)
            {
                if (i == iter.i&&j == iter.j)
                {
                }
                else
                {
                    map[i][j].h = manhatten(i, j);
                    //printf("(%d,%d)的h值为%d\n", i,j,map[i][j].h);
                    Neibo[neibNum] = map[i][j];
                    ++neibNum;
                }
            }
        }
    }
}

//查看临近格在不在开启列表中的函数
int isInOpenList(struct baseNode neibo)
{
    //printf("开启列表当前为：");
    //for(int i=0;i<openListCount;++i)
    //{
        //printf("(%d,%d)", OpenList[i].i, OpenList[i].j);
    //}
    //printf("\n");
    for (int i = 0; i <= openListCount - 1; ++i)
    {
        if (OpenList[i].i == neibo.i&&OpenList[i].j == neibo.j)
        {
            return 1;
        }
    }
    return 0;
}

//优化：查看指定的temp在不在关闭列表中的函数
int isInCloseList(struct baseNode temp)
{
    int low = 0, high = closeListCount - 1, mid = (low + high) / 2;

    for (; low<=high; mid = (low + high) / 2)
    {
        if ((CloseList[mid].i*MAX_number + CloseList[mid].j + 1)==(temp.i*MAX_number + temp.j + 1))
        {
            return 1;
        }
        else if((CloseList[mid].i*MAX_number + CloseList[mid].j + 1) > (temp.i*MAX_number + temp.j + 1))
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return 0;
}

//优化：A*中的启发式函数，用于求指定位置和终点之间的曼哈顿距离
int manhatten(int i, int j)
{
    int a= (abs(AsceneryList[1].i - i) + abs(AsceneryList[1].j - j));
    //if (a==0)
    //{
        //FLAG = 1;
    //}

    return a*10;
}

//求当前点与父亲节点的距离
int increment(struct baseNode thisnode)
{
    if ((abs(thisnode.father->i-thisnode.i)==1) && (abs(thisnode.father->j - thisnode.j) == 1))
    {
         return 14*thisnode.weigt;
    }
    else if ((thisnode.father->i - thisnode.i) == 0 && (thisnode.father->j - thisnode.j) == 0)
    {
        return 0;
    }
    else
    {
        return 10*thisnode.weigt;
    }
}

//求出用当前点作为父节点时这个点的G值
int NewG(struct baseNode thisnode,struct baseNode father)
{
    if (abs(father.i - thisnode.i) == 1 && abs(father.j - thisnode.j) == 1)
    {
        return father.g+14;
    }
    else if (abs(father.i - thisnode.i) == 0 && abs(father.j - thisnode.j) == 0)
    {
        return father.g;
    }
    else
    {
        return father.g+10;
    }
}


//存储最佳路线的数组
//把A*算法的节点按倒序整理到Astack里面
void arrange(struct baseNode iter)
{
    //printf("Astack：\n");
    AstackCount = 0;
    for (; ; iter=map[iter.father->i][iter.father->j])//map[Neibo[i].i][Neibo[i].j].father->i
    {
        //printf("考虑Astack中是否装入(%d,%d)\n",iter.i,iter.j);
        //printf("(%d,%d)的父亲(%d,%d)\n", iter.i,iter.j,iter.father->i,iter.father->j);
        Astack[AstackCount] = iter;
        ++AstackCount;
        //printf("Astack中装入(%d,%d)\n",iter.i,iter.j);
        if (iter.i == AsceneryList[0].i&&iter.j == AsceneryList[0].j)
        {
            //printf("是起点\n");
            break;
        }
        //printf("不是起点\n");
        //printf("下面考虑(%d,%d)\n",iter.father->i,iter.father->j);
    }
}

//打印出A*算法的路径矩阵
void printAstar()
{
    QString str_rode = "Optimal rode:(A stands for a step of optimal rode but Q does not:)\n";
    QString str_map = "Original map:\n";
    QString str_point = "Start point:("+QString::number(AsceneryList[0].i+1)+","+QString::number(AsceneryList[0].j+1)+")\n"
                       +"End point:("+QString::number(AsceneryList[1].i+1)+","+QString::number(AsceneryList[1].j+1)+")\n";

    int boole = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            str_map += QString::number(map[i][j].weigt)+" ";
            for (int w=0; w<AstackCount; ++w)
            {
                if (Astack[w].i==i&&Astack[w].j==j)
                {
                    boole = 1;
                    break;
                }
            }

            if (boole==1)
            {
                str_rode = str_rode + "A ";
                boole = 0;
            }
            else
            {
                str_rode = str_rode + "Q ";
            }
        }
        str_rode = str_rode + "\n";
        str_map += "\n";
    }

    QMessageBox *rodeBox;
    //rodeBox->reSize(300,300);
    rodeBox = new QMessageBox("Optimal Rode",       //--这里是设置消息框标题
    str_map+"\n"+str_point+"\n"+str_rode,                       //--这里是设置消息框显示的内容
    QMessageBox::Information,                          //--这里是在消息框显示的图标
    QMessageBox::Retry | QMessageBox::Default,     //---这里是显示消息框上的按钮情况
    QMessageBox::Cancel | QMessageBox::Escape,  //---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
    0);                                        //---这里是 定义第三个按钮， 该例子 只是 了显示2个按钮
    //if (rodeBox.exec() == QMessageBox::Retry)
    //        ui->lineEdit_x1->clear();
    rodeBox->show();                                  ///---显示消息框
}


//寻径的函数
void Astar()
{
    //初始化A*
    FLAG =0;
    //每次执行A*算法，都初始化开启/关闭列表
    openListCount = 0;
    closeListCount = 0;

    //创建一个迭代器,每次都等于f值最小的节点
    struct baseNode iter;

    //让这个迭代器的初值为起点
    iter.i = AsceneryList[0].i;
    iter.j = AsceneryList[0].j;
    iter.weigt = map[AsceneryList[0].i][AsceneryList[0].j].weigt;

    //起点的没有父节点，且为唯一G值为0的点
    iter.g = 0;
    iter.h = manhatten(iter.i,iter.j);
    iter.f = iter.g + iter.h;

    //创建终点
    //struct baseNode ender;

    //ender.i = AsceneryList[1].i;
    //ender.j = AsceneryList[1].j;
    //printf("创建了终点，坐标是(%d,%d)\n", ender.i, ender.j);
    //把起点放入开启列表
    putInOpenList(iter);
    //printf("把起点放入开启列表\n");
    //当开启列表为空或者终点在关闭列表中，结束寻径
    for (; openListCount != 0 ;)
    {
        //取出开启列表中f值最小的节点（之一），并设为iter（当前点）
        iter = readTopOpenList();
        //printf("取出开启列表中f值最小的节点（之一）(%d,%d)\n",iter.i,iter.j);

        //把当前点从开启列表中删除
        outOpenList2(iter);
        //printf("把当前点(%d,%d)从开启列表中删除\n",iter.i,iter.j);

        //把当前点记录在关闭列表中
        putInCloseList(iter);
        //printf("把当前点(%d,%d)记录在关闭列表中\n",iter.i,iter.j);
        if(FLAG==1)
        {
            break;
        }

        //把当前点的邻居加入邻居列表
        addNeibo(iter);
        //printf("(%d,%d)邻居列表已加满\n",iter.i,iter.j);

        //对于每个邻居，分三种情况进行操作
        for (int i = 0; i < neibNum; ++i)
        {
            //如果这个邻居节点不可通过，或者这个邻居节点在关闭列表中，略过它
            if (Neibo[i].weigt==0 || isInCloseList(Neibo[i]))
            {
                //printf("这个邻居节点(%d,%d)不可通过，或者这个邻居节点在关闭列表中，略过它\n",Neibo[i].i,Neibo[i].j);
            }
            //如果这个邻居节点已经在开启列表中
            else if(isInOpenList(Neibo[i]))
            {
                //看看以当前格子为父节点，算出来的新G值是不是比原来的G值小，如果更小，就改变这一格的父节点，G值，重新计算F值
                if (NewG(Neibo[i],iter)<Neibo[i].g)
                {
                    //printf("算出来的新G值比原来的G值%d小，如果更小，就改变(%d,%d)这一格的父节点\n",Neibo[i].g,Neibo[i].i,Neibo[i].j);
                    map[Neibo[i].i][Neibo[i].j].father = &map[iter.i][iter.j];
                    map[Neibo[i].i][Neibo[i].j].g = map[iter.i][iter.j].g + increment(Neibo[i]);
                    map[Neibo[i].i][Neibo[i].j].f = map[Neibo[i].i][Neibo[i].j].g + map[Neibo[i].i][Neibo[i].j].h;
                    //printf("(%d,%d)的父亲(%d,%d),g=%d,f=%d\n", Neibo[i].i,Neibo[i].j,map[Neibo[i].i][Neibo[i].j].father->i,map[Neibo[i].i][Neibo[i].j].father->j,map[Neibo[i].i][Neibo[i].j].g,map[Neibo[i].i][Neibo[i].j].f);
                    //把这一格的旧记录从开启列表删除，把更新后的这一格的值加入开启列表等待处理
                    outOpenList2(Neibo[i]);
                    putInOpenList(Neibo[i]);
                    //printf("更新了开启列表中的节点(%d,%d)\n",Neibo[i].i,Neibo[i].j);
                }
                //printf("(%d,%d)这个邻居节点已经在开启列表中\n",Neibo[i].i,Neibo[i].j);
            }
            //如果这个邻居节点不在开启列表中
            else
            {
                //printf("(%d,%d)这个邻居节点不在开启列表中\n",Neibo[i].i,Neibo[i].j);
                map[Neibo[i].i][Neibo[i].j].father= Neibo[i].father = &map[iter.i][iter.j];
                map[Neibo[i].i][Neibo[i].j].g = map[iter.i][iter.j].g + increment(Neibo[i]);
                map[Neibo[i].i][Neibo[i].j].f = map[Neibo[i].i][Neibo[i].j].g + map[Neibo[i].i][Neibo[i].j].h;
                //printf("(%d,%d)的父亲(%d,%d),g=%d,f=%d\n", Neibo[i].i,Neibo[i].j,map[Neibo[i].i][Neibo[i].j].father->i,map[Neibo[i].i][Neibo[i].j].father->j,map[Neibo[i].i][Neibo[i].j].g,map[Neibo[i].i][Neibo[i].j].f);
                Neibo[i] = map[Neibo[i].i][Neibo[i].j];
                putInOpenList(Neibo[i]);
                //printf("(%d,%d)加入了开启列表\n",Neibo[i].i,Neibo[i].j);
            }
        }
    }
    //if(openListCount == 0)printf("开启列表为空\n");
    //else if(isInCloseList(ender)==1)printf("终点\在关闭列表中\n");
    //printf("终点的父亲是%d %d\n",CloseList[closeListCount-1].father->i, CloseList[closeListCount-1].father->j);
    //打印最优路径
    //printf("(%d,%d)\n",CloseList[closeListCount-1].i,CloseList[closeListCount-1].j);
    arrange(CloseList[closeListCount-1]);
    printAstar();
}

#endif // FUNC_H_INCLUDED
