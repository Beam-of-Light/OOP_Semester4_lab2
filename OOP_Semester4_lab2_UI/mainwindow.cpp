#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../src/utils.h"
#include "../src/algorithms.h"
#include <QVector>
#include <QPair>
#include <algorithm>
#include <vector>

#define MAXRANDOM 10000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sizeLine->setText("0");
    ui->addLine->setText("0");
    ui->addRandNLine->setText("0");
    ui->removeLine->setText("0");

    ui->graph->xAxis->setLabel("size");
    ui->graph->yAxis->setLabel("time (s)");

    QString styleSheet = "::section {" // "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: white;"
                         "border: 1px solid red;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arial;"
                         "font-size: 12px; }";

    ui->benchmarkTable->horizontalHeaderItem(1)->setTextColor(QColor(207, 68, 43));
    ui->benchmarkTable->horizontalHeaderItem(2)->setTextColor(QColor(141, 94, 166));
    ui->benchmarkTable->horizontalHeaderItem(3)->setTextColor(QColor(34, 82, 179));
    ui->benchmarkTable->horizontalHeaderItem(4)->setTextColor(QColor(42, 107, 32));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::get_rand_int(){
    return utils::generate_int(0,MAXRANDOM);
}

void MainWindow::updateOutput(){
    QString text = "";
    for(auto i = container.begin(); i!= container.end(); ++i){
        text += QString::number(*i) + " ";
    }
    ui->vectorBrowser->setText(text);
    ui->sizeLine->setText(QString::number(container.size()));
}

void MainWindow::updateGraph(){
    QPair<QVector<double>, QVector<double>> bubble,merge,quick, combined;
    int pointAmount = ui->benchmarkTable->rowCount();
    double maxX = 0, maxY = 0;
    for (size_t rows = 0, rowsCount = ui->benchmarkTable->rowCount(), columnsCount = ui->benchmarkTable->columnCount(); rows < rowsCount; ++rows) {
        int curSize =  ui->benchmarkTable->item(rows, 0)->text().toInt();
        if (curSize > maxX){
            maxX = curSize;
        }

        for (size_t columns = 1; columns < columnsCount; ++columns) {
            double curTime = ui->benchmarkTable->item(rows, columns)->text().toDouble();

            if(curTime > maxY){
                maxY = curTime;
            }
            switch(columns){
            case 1:
                bubble.first.push_back(curSize);
                bubble.second.push_back(curTime);
                break;
            case 2:
                merge.first.push_back(curSize);
                merge.second.push_back(curTime);
                break;
            case 3:
                quick.first.push_back(curSize);
                quick.second.push_back(curTime);
                break;
            case 4:
                combined.first.push_back(curSize);
                combined.second.push_back(curTime);
                break;
            default:
                break;
            }
        }
    }

    qDebug()<<bubble.first.size();

    ui->graph->clearGraphs();
    ui->graph->addGraph();
    ui->graph->addGraph();
    ui->graph->addGraph();
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(bubble.first, bubble.second);
    ui->graph->graph(1)->setData(merge.first, merge.second);
    ui->graph->graph(2)->setData(quick.first, quick.second);
    ui->graph->graph(3)->setData(combined.first, combined.second);

    ui->graph->graph(0)->setPen(QColor(207, 68, 43));
    ui->graph->graph(1)->setPen(QColor(141, 94, 166));
    ui->graph->graph(2)->setPen(QColor(34, 82, 179));
    ui->graph->graph(3)->setPen(QColor(42, 107, 32));

    ui->graph->xAxis->setRange(0, maxX);
    ui->graph->yAxis->setRange(0,maxY);
    ui->graph->replot();
}

void MainWindow::on_addButton_clicked(){
    container.push_back(ui->addLine->text().toInt());
    updateOutput();
}

void MainWindow::on_removeButton_clicked(){
    auto it = std::find(container.begin(),container.end(),ui->removeLine->text().toInt());
    if (it != container.end())
        container.erase(it);
    updateOutput();
}

void MainWindow::on_addRandButton_clicked(){
    container.push_back(get_rand_int());
    updateOutput();
}

void MainWindow::on_addRandNButton_clicked(){
    for(auto i = 0; i < ui->addRandNLine->text().toInt();++i){
        container.push_back(get_rand_int());
    }
    updateOutput();
}

void MainWindow::on_shuffleButton_clicked(){
    std::random_shuffle(container.begin(),container.end());
    updateOutput();
}

double MainWindow::getTimeDuration(int algorithmType){
    std::vector<int> copy = container;
    timer.startTimer();
    switch(algorithmType){
       case 1: Sort<int>::bubble_sort(copy); break;
       case 2: Sort<int>::merge_sort(copy); break;
       case 3: Sort<int>::quick_sort(copy); break;
       case 4: Sort<int>::combined_sort(copy); break;
       default: return 0;
    }
    return timer.getDuration();
}

void MainWindow::on_sortButton_clicked(){
    int row = ui->benchmarkTable->rowCount();
    ui->benchmarkTable->insertRow(row);
    ui->benchmarkTable->setItem(row,0,new QTableWidgetItem(ui->sizeLine->text()));
    for(auto i = 1; i < 5; ++i){
        ui->benchmarkTable->setItem(row, i, new QTableWidgetItem(QString::number(getTimeDuration(i))));
    }

    updateGraph();
}

void MainWindow::on_removeAllButton_clicked(){
    container.erase(container.begin(),container.end());
    updateOutput();
}
