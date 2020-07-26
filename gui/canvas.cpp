#include "canvas.h"
#include <QDebug>


Canvas::Canvas(QWidget *parent) :
    QGraphicsScene(parent)
{

}

Canvas::~Canvas()
{

}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    qDebug() << "i am here";
}
