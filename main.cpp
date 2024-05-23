#include "mainwindow.h"
#include "glview.h"

#include <QApplication>
#include <QObject>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow m;
//    m.show();
    GLView w;
    w.show();
//    w.adjustSize();

    return a.exec();
}
