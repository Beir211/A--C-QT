#include "mymap.h"
#include "ui_mymap.h"
#include "process_control.h"

Mymap::Mymap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mymap)
{
    ui->setupUi(this);
    resize(600, 400);
    //testStart();
}

Mymap::~Mymap()
{
    delete ui;
}

void Mymap::clickClearButton()
{
    ui->lineEdit_x1->clear();
    ui->lineEdit_x2->clear();
    ui->lineEdit_y1->clear();
    ui->lineEdit_y2->clear();
    ui->textEdit_map->clear();

}
void Mymap::clickRodeButton()
{
    n = ui->comboBox_n-> currentIndex()+2;
    QString inputCheck;
    inputCheck = ui->textEdit_map->toPlainText();
    if(inputCheck.isEmpty())
    {
        QMessageBox::about(this,"Attention","Plz input map!");
        return;
    }
    //检查起点和终点坐标是否出界,若出界，弹出提示框并取消计算路径
    //QString inputCheck;
    inputCheck = ui->lineEdit_x1->text();
    if(inputCheck.toInt()>n || inputCheck.toInt()<1)
    {
        QMessageBox::about(this,"Attention "+inputCheck,"Plz input x1 as requested!");
        return;
    }
    inputCheck = ui->lineEdit_y1->text();
    if(inputCheck.toInt()>n || inputCheck.toInt()<1)
    {
        QMessageBox::about(this,"Attention "+inputCheck,"Plz input y1 as requested!");
        return;
    }
    inputCheck = ui->lineEdit_x2->text();
    if(inputCheck.toInt()>n || inputCheck.toInt()<1)
    {
        QMessageBox::about(this,"Attention "+inputCheck,"Plz input x2 as requested!");
        return;
    }
    inputCheck = ui->lineEdit_y2->text();
    if(inputCheck.toInt()>n || inputCheck.toInt()<1)
    {
        QMessageBox::about(this,"Attention "+inputCheck,"Plz input y2 as requested!");
        return;
    }

    QString mapText = ui->textEdit_map->toPlainText();
    QStringList mapTextList = mapText.split("\n");
    if(mapTextList.size()<n*n) //检查地图输入是否输入完成
    {
        QMessageBox::about(this,"Attention map input","Plz input n*n integers for a map!Map input is only "+QString::number(mapTextList.size(),10));
        return;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            map[i][j].weigt = mapTextList.at(i*n+j).toInt();
            map[i][j].i = i;
            map[i][j].j = j;
        }
    }

    int x1 = ui->lineEdit_x1->text().toInt();
    int y1 = ui->lineEdit_y1->text().toInt();
    int x2 = ui->lineEdit_x2->text().toInt();
    int y2 = ui->lineEdit_y2->text().toInt();
    if(map[x1-1][y1-1].weigt==0)//起点不可通过
    {
        QMessageBox::about(this,"Attention start point input","Start point is unaccessible!");
        return;
    }
    if(map[x2-1][y2-1].weigt==0)//终点不可通过
    {
        QMessageBox::about(this,"Attention end point input","End point is unaccessible!");
        return;
    }
    if(x1==x2 && y1==y2)//起终点相同
    {
        QMessageBox::about(this,"Attention start point and end point","Start point is end point!");
        return;
    }
    AsceneryList[0].i = x1 - 1;
    AsceneryList[0].j = y1 - 1;
    AsceneryList[1].i = x2 - 1;
    AsceneryList[1].j = y2 - 1;

    //QString str_n = QString::number(n, 10);
    //QString str_x1 = QString::number(x1, 10);//把int 转换为10进制的QString
    //QString str_y1 = QString::number(y1, 10);
    //QString str_x2 = QString::number(x2, 10);
    //QString str_y2 = QString::number(y2, 10);

    testStart();
}



void Mymap::on_actionHelp_triggered()
{
    QMessageBox::about(this,"Introduction","Input a map and I will tell you an optimal rode "
                                           "from start point to end point."
                                           "You should type how accessible every point is."
                                           "Thank you for trying!");
}
