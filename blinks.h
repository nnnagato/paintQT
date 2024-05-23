#ifndef BLINKS_H
#define BLINKS_H

#include "glview.h"

#include <QObject>

class blinks : public QObject
{
    Q_OBJECT


public:
    blinks();
    GLView glv;
public slots:
    void start();
};

#endif // BLINKS_H
