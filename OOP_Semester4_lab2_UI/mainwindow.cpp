#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../src/utils.h"
#include "../src/algorithms.h"
#include <QVector>
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
   // QVector bubble,merge,quick, combined;
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
}
