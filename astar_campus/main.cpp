#include "mymap.cpp"
#include <QApplication>//类管理图形用户界面应用程序的控制流和主要设置

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mymap w;
    w.show();

    return a.exec();
}
