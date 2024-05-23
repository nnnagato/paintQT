#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    GLView glv;

signals:
    void isLineTool();
    void isSquareTool();

private slots:
    void on_lineButton_released();
    void on_squareButton_released();

private:
    Ui::MainWindow *ui;
    GLView oView;
};
#endif // MAINWINDOW_H
