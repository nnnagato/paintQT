#ifndef GLVIEW_H
#define GLVIEW_H

#include "qmenu.h"
#include <QMouseEvent>
#include <QString>
#include <QToolButton>
#include <QPushButton>
#include <QThread>

class QLabel;



class GLView : public QWidget
{
    enum class ToolType
    {
        Line,
        Rect,
        Ellipse,
        Pen,
    };

public:
    GLView(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void setCoordinates(int x, int y);

signals:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void on_lineButton_clicked();
    void on_rectButton_clicked();
    void on_ellipseButton_clicked();
    void on_penButton_clicked();
    void on_saveButton_clicked();

private:
    void getPositions();
    void hideButtons();
    void showButtons();
    void drawFigure();

private:
    QLabel& coords;
    QPushButton lineButton;
    QPushButton rectButton;
    QPushButton ellipseButton;
    QPushButton penButton;
    QPushButton saveButton;
    QPixmap* pix = nullptr;

    QPoint previousPress;
    QPoint currentPosition;
    QPoint upperPosition;
    QPoint lowerPosition;
    bool pressed = false;
    bool movement = false;

    QPointF z_camPos {0., 0.};
    qreal z_scale {1.0};
    ToolType currentTool;
};



#endif // GLVIEW_H
