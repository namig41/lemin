#include "node.h"
#include <QDebug>

Node::Node() :
    QGraphicsItem()
{

}
Node::Node(const QString &n, const QPointF &p, const float &r) :
    QGraphicsItem(),
    name(n), point(p), radius(r)
{

}

Node::~Node()
{

}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(boundingRect());
}


QRectF Node::boundingRect() const
{
    return QRect(point.x() - radius / 2.f, point.y() - radius / 2.f, radius, radius);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "I AM HERE";
    //point = event->pos();
    //update();
    //QGraphicsItem::mouseReleaseEvent(event);



}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(mapToScene(event->pos()));
}
