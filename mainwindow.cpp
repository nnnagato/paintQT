#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glview.h"


#include <QOpenGLFunctions>
#include <QWidget>
#include <QMessageBox>
#include <QObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    oView.show();
    this->setWindowTitle("Tool bar");
//    QObject::connect(this, &MainWindow::isLineTool, &glv, &GLView::drawLine);
//    QObject::connect(this, &MainWindow::isSquareTool, &glv, &GLView::drawSquare);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_lineButton_released()
{
    emit isLineTool();
}


void MainWindow::on_squareButton_released()
{
    emit isSquareTool();
}

