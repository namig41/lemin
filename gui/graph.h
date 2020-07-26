#ifndef GRAPH_H
#define GRAPH_H

#include <QPainter>
#include <QPoint>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>

#include "node.h"

class Graph : public QGraphicsItemGroup
{
public:

    std::vector<Node *> nodes;
    std::vector<std::vector<int>> graphMatrix;

public:

    Graph();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void drawNodes(QPainter *paitner);
    void drawEdge(QPainter *painter);
};

#endif // GRAPH_H
