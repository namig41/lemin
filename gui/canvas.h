#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include <QWheelEvent>

class Canvas : public QGraphicsScene
{
    Q_OBJECT

private:

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // CANVAS_H
