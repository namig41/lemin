#include "graph.h"

Graph::Graph() :
    QGraphicsItemGroup()
{

}

Graph::~Graph()
{

}

QRectF Node::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    drawNode(painter);
    drawEdge(painter);
}



void Node::drawNode(QPainter *painter)
{
    for (size_t i = 0; i < nodes.size(); i++)
        painter->drawEllipse(nodes[i].boundingRect());
}

void Node::drawEdge(QPainter *painter)
{
    for (size_t i = 0; i < graphMatrix.size(); i++)
    {
        for (size_t j = i + 1; j < graphMatrix[i].size(); j++)
        {
            if (graphMatrix[i][j])
            {
                scene->addLine(nodes[j]->point.x(), nodes[j]->point.y(),
                               nodes[i]->point.x(), nodes[i]->point.y());
            }
        }
    }
}
