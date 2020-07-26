#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas.h"
#include "graph.h"
#include "node.h"

#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QTextStream>
#include <QMouseEvent>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

#include <QBrush>
#include <QPen>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    typedef enum e_Section
    {
        NODES,
        RELATIONS,
        ANTS
    }			Section;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readFile(const QString &filenme);
    void parseAnts(const QString &line);
    void parseRooms(const QString &line);
    void parseSection(const QString &line, const Section &section, int &rowNode, int &countNode);
    void parseRelations(const QString &line, const int &row, const int &size);
    void parseAntsSteps(const QString &line, const size_t &row);

    void drawRooms();
    void drawRelations();
    void drawAnts();

    void initCellSize();

    virtual void keyPressEvent(QKeyEvent *event);

    void setSlider(int min, int max, int value);

    void runScene();
    void clearScene();
    void updateScene();

    void stepForward();
    void stepBack();

    size_t getNodeIndex(const QString &name) const;

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_lineEdit_editingFinished();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;


    Node *node;

    QPointF centerPainter;

    float scalingCanvas;

    int speedTimer;
    int numberAnts;
    int numberNodes;
    QSize cellSize;
    QSize roomSize;

    int currentStep;

    std::vector<Node *> nodes;
    std::vector<std::vector<int>> graphMatrix;

    std::vector<std::map<QString, QString>> antsSteps;

    std::vector<QRect> ants;

    QTimer *timer;
    QGraphicsView *view;
    QGraphicsScene *scene;

    Graph *graph;

    QPixmap background;
    QImage ant;

};

#endif // MAINWINDOW_H
