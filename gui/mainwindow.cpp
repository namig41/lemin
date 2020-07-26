#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentStep(0),
    background("/home/namig/Source/lemin/gui/img/background.jpg")
{
    ui->setupUi(this);

    setFixedSize(QSize(800, 600));
    //setSlider(-5, 5, 1);
    setMouseTracking(true);

    scene = new QGraphicsScene();

    graph = new Graph();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home");
    readFile(fileName);
}

void MainWindow::readFile(const QString &fileName)
{
    QFile inputFile(fileName);

    if (inputFile.open(QIODevice::ReadOnly))
    {
        Section section = NODES;
        int rowNode = 0;
        int countNode = 0;
        QTextStream in(&inputFile);

        parseAnts(in.readLine());
        while (!in.atEnd())
        {
            QString line = in.readLine();
            qDebug() << line;

            if (line.isEmpty())
            {
                switch (section)
                {
                    case NODES:
                        graphMatrix.resize(countNode);
                        numberNodes = countNode;
                        initCellSize();
                        section = RELATIONS;
                        break;

                    case RELATIONS:
                        rowNode = 0;
                        section = ANTS;
                        break;

                    case ANTS:
                        break;
                }
            }
            else
                parseSection(line, section, rowNode, countNode);
        }

        inputFile.close();
    }
    updateScene();
}

void MainWindow::parseSection(const QString &line, const Section &section, int &rowNode, int &countNode)
{
    switch (section)
    {

        case NODES:
            parseRooms(line);
            countNode++;
            break;

        case RELATIONS:
            parseRelations(line, rowNode, countNode);
            rowNode++;
            break;

        case ANTS:
            parseAntsSteps(line, rowNode);
            rowNode++;
            break;

        default:
            break;
    }
}

void MainWindow::parseAnts(const QString &line)
{
    numberAnts = line.toInt();
}

void MainWindow::parseRooms(const QString &line)
{
   QStringList list;

   list = line.split(' ');

   node = new Node(list[0], QPointF(list[1].toInt(), list[2].toInt()), 100);
   nodes.push_back(node);
}

void MainWindow::parseAntsSteps(const QString &line, const size_t &row)
{
    QStringList listStep;

    antsSteps.push_back(std::map<QString, QString>());
    listStep = line.split(' ');
    for (auto &it : listStep)
    {
        QStringList listAnts = it.split('-');
        antsSteps[row].insert(std::pair<QString, QString>(listAnts[0], listAnts[1]));
    }
}

void MainWindow::parseRelations(const QString &line, const int &row, const int &size)
{
    QStringList list;

    list = line.split('-');
    graphMatrix[row].resize(size);
    for (auto &it : list)
    {
        size_t index = getNodeIndex(it);
        graphMatrix[row][index] = 1;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key;

    key = event->key();
    if (key == Qt::Key::Key_Escape)
        close();
    else if (key == Qt::Key::Key_Right)
        stepForward();
    else if (key == Qt::Key::Key_Left)
        stepBack();
}

void MainWindow::on_action_2_triggered()
{

}

void MainWindow::on_action_3_triggered()
{

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //ui->graphicsView->scale(0.8 * value, 0.8 * value);
}

void MainWindow::setSlider(int min, int max, int value)
{
    ui->horizontalSlider->setMinimum(min);
    ui->horizontalSlider->setMaximum(max);
    ui->horizontalSlider->setValue(value);
}

void MainWindow::on_lineEdit_editingFinished()
{
    numberNodes = (int)nodes.size() * ui->lineEdit->text().toInt();
    initCellSize();
    updateScene();
}

void MainWindow::on_pushButton_3_clicked()
{
    stepBack();
}


void MainWindow::on_pushButton_4_clicked()
{
    stepForward();
}

void MainWindow::stepForward()
{
    if (currentStep < (int)antsSteps.size())
    {
        currentStep++;
        updateScene();
    }
}

void MainWindow::stepBack()
{
    if (currentStep > 0)
    {
        currentStep--;
        updateScene();
    }
}

void MainWindow::clearScene()
{
    numberAnts = 0;
    numberNodes = 0;
    currentStep = 0;
    nodes.clear();
    graphMatrix.clear();
    antsSteps.clear();
    ants.clear();
}

void MainWindow::drawRooms()
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        scene->addItem(nodes[i]);
    }
}

void MainWindow::drawRelations()
{

}

void MainWindow::drawAnts()
{

//    for (auto it = antsSteps[currentStep].begin(); it != antsSteps[currentStep].end(); ++it)
//    {
//        size_t index = getNodeIndex(it->second);

//        scene->addRect(QRect(nodes[index].point.x() * cellSize.width(),
//                             nodes[index].point.y() * cellSize.height(),
//                             cellSize.width(), cellSize.width()));
//    }
}

void MainWindow::initCellSize()
{
    cellSize.setWidth(ui->graphicsView->width() / numberNodes);
    cellSize.setHeight(ui->graphicsView->height() / numberNodes);
}

size_t MainWindow::getNodeIndex(const QString &nodeName) const
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->name == nodeName)
            return i;
    }
    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    updateScene();
}

void MainWindow::updateScene()
{
   scene->clear();

   if (nodes.empty())
       return ;
   //drawRelations();
   drawRooms();
   //drawAnts();
}
