#ifndef GLVIEW_H
#define GLVIEW_H

#include "qmenu.h"
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QString>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QThread>

class GLView : public QWidget
{
public:
    GLView(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    int currentTool;
    void setCoordinates(int x, int y);
//    qreal z_scale {1.0};
    QPointF z_camPos {0., 0.};
    qreal z_scale {1.0};

private:
    void getPositions();
    QPoint previousPress;
    QPoint currentPosition;
    QPoint upperPosition;
    QPoint lowerPosition;
    bool pressed = false;
    bool movement = false;
    QLabel coords;
    QPushButton lineButton;
    QPushButton rectButton;
    QPushButton ellipseButton;
    QPushButton penButton;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void on_lineButton_clicked();
    void on_rectButton_clicked();
    void on_ellipseButton_clicked();
    void on_penButton_clicked();
};



#endif // GLVIEW_H
