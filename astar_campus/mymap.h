#ifndef MYMAP_H
#define MYMAP_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <QStack>

namespace Ui {
class Mymap;
}

class Mymap : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mymap(QWidget *parent = 0);
    ~Mymap();

public slots:
    void clickClearButton();
    void clickRodeButton();

private slots:
    void on_actionHelp_triggered();

private:
    Ui::Mymap *ui;
};

#endif // MYMAP_H
