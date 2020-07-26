#ifndef NODE_H
#define NODE_H

#include <QPainter>
#include <QPoint>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class Node : public QGraphicsItem
{

public:

    QString name;
    QPointF point;
    float radius;

public:
    Node();
    Node(const QString &n, const QPointF &p, const float &r);
    ~Node();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // NODE_H
