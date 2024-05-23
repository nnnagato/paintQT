#include "glview.h"
#include "blinks.h"
#include "mainwindow.h"
#include "qthread.h"

#include <QObject>
#include <QPainter>
#include <QMouseEvent>
#include <QRegion>
#include <math.h>
#include <QObject>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QFileDialog>

GLView :: GLView(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    //starting tool = rect
    currentTool = 1;


     //setting up main workspace parametres
    this -> setWindowState(Qt::WindowMaximized);
    this -> setWindowTitle("Workspace");
    this -> setMouseTracking(true);


    //setting the coordinates label
    coords.setParent(this);
    coords.setMouseTracking(true);
    coords.setGeometry(QRect(0,0,100,100));
    coords.setTextFormat(Qt::PlainText);


    //creating buttons, set their size
    QSize btnSize(100,25);
    lineButton.setParent(this);
    rectButton.setParent(this);
    ellipseButton.setParent(this);
    penButton.setParent(this);
    saveButton.setParent(this);
    lineButton.setMinimumSize(btnSize);
    rectButton.setMinimumSize(btnSize);
    ellipseButton.setMinimumSize(btnSize);
    saveButton.setMinimumSize(btnSize);
    lineButton.setGeometry(QRect(QPoint(0,0),btnSize));
    rectButton.setGeometry(QRect(QPoint(100,0),btnSize));
    ellipseButton.setGeometry(QRect(QPoint(200,0),btnSize));
    penButton.setGeometry(QRect(QPoint(300,0),btnSize));
    saveButton.setGeometry(QRect(QPoint(800,0),btnSize));
    penButton.setParent(this);
    lineButton.setText("Линия");
    rectButton.setText("Прямоугольник");
    ellipseButton.setText("Элипс");
    penButton.setText("Карандаш");
    saveButton.setText("Сохранить как");


    //connecting buttons handlers
    QObject::connect(&lineButton, &QPushButton::clicked, [=]() {
        on_lineButton_clicked();
    });
    QObject::connect(&rectButton, &QPushButton::clicked, [=]() {
        on_rectButton_clicked();
    });

    QObject::connect(&ellipseButton, &QPushButton::clicked, [=]() {
        on_ellipseButton_clicked();
    });

    QObject::connect(&penButton, &QPushButton::clicked, [=]() {
        on_penButton_clicked();
    });

    QObject::connect(&saveButton, &QPushButton::clicked, [=]() {
        on_saveButton_clicked();
    });

}

void GLView::setCoordinates(int x, int y)
{
    QString coordinates;
    coordinates = "X: ";
    coordinates.append(QString::number(x/z_scale));
    coordinates.append("\nY: ");
    coordinates.append(QString::number(y/z_scale));
    coordinates.append("\nscale: ");
    coordinates.append(QString::number(z_scale));
    coords.setText(coordinates);
}

void GLView::paintEvent(QPaintEvent* event)
{    
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::red);
//    painter.translate(z_camPos);
    if(movement)
    {
        painter.scale(z_scale, z_scale);
        movement = false;
    }
    switch (currentTool) {
    case 0: //line
        painter.drawLine(previousPress.x(),
                         previousPress.y(),
                         currentPosition.x(),
                         currentPosition.y());
        break;

    case 1: //rectangle
        painter.drawRect(upperPosition.x(),
                         upperPosition.y(),
                         lowerPosition.x()-upperPosition.x(),
                         lowerPosition.y()-upperPosition.y());
        break;

    case 2://ellipse
        painter.drawEllipse(upperPosition.x(),
                            upperPosition.y(),
                            lowerPosition.x()-upperPosition.x(),
                            lowerPosition.y()-upperPosition.y());
        break;

    case 3://pen
        if(pressed==true)
        {
            painter.drawEllipse(QRect(currentPosition.x(),
                                      currentPosition.y(),
                                      2,
                                      2));
        }
        break;

    default:
        break;

    }

}

void GLView::on_lineButton_clicked()
{
    currentTool = 0;
}

void GLView::on_rectButton_clicked()
{
    currentTool = 1;
}

void GLView::on_ellipseButton_clicked()
{
    currentTool = 2;
}

void GLView::on_penButton_clicked()
{
    currentTool = 3;
}

void GLView::on_saveButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");

    if(filename.isEmpty())
        return;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;

    QPixmap pic = QPixmap::grabWidget(this);
    pic.save(filename, 0, 1);

     file.close();
}

void GLView::mousePressEvent(QMouseEvent* event)
{
    pressed = true;
    previousPress = event->pos();
//    if(event -> button() == Qt::MiddleButton)
//    {
//        movement=true;
//        currentTool = -1;
//    }
};

void GLView::getPositions()
{
    upperPosition.setX((std::min(previousPress.x(), currentPosition.x())));
    upperPosition.setY((std::min(previousPress.y(), currentPosition.y())));
    lowerPosition.setX((std::max(previousPress.x(), currentPosition.x())));
    lowerPosition.setY((std::max(previousPress.y(), currentPosition.y())));
};

void GLView::mouseReleaseEvent(QMouseEvent* event)
{
    pressed = false;
    currentPosition = event -> pos();
    getPositions();
    QRegion region(QRect(upperPosition.x(),
                         upperPosition.y(),
                         lowerPosition.x()-upperPosition.x()+1,
                         lowerPosition.y()-upperPosition.y()+1));
    if(currentTool!=3)
        update(region);
//    if(event -> button() == Qt::MiddleButton)
//    {
//        movement = false;
//    }

};



void GLView::mouseMoveEvent(QMouseEvent* event)
{
    setCoordinates(event -> x(), event->y());
    if(pressed == true && currentTool == 3)
    {
        currentPosition = event -> pos();
        update(QRect(currentPosition.x(),
                     currentPosition.y(),
                     2,2));
        previousPress = event -> pos();
    };
//    if(movement)
//    {
//        QPointF deltaMouse = event -> pos() - previousPress;
//        z_camPos -= deltaMouse;
//        update();
//    }

}

void GLView::wheelEvent(QWheelEvent* event)
{
        const qreal scaleCoef = 1.1;
        qreal newScale = event->angleDelta().y() > 0 ? z_scale * scaleCoef :
            z_scale / scaleCoef;
        z_scale = newScale;
        movement = true;
        setCoordinates(event -> x(), event -> y());
        repaint();

}


