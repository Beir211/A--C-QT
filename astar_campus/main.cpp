#include "mymap.cpp"
#include <QApplication>//�����ͼ���û�����Ӧ�ó���Ŀ���������Ҫ����

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mymap w;
    w.show();

    return a.exec();
}
