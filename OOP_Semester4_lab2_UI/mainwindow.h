#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "../src/utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    std::vector<int> container;
    void updateOutput();
    void updateGraph();
    int get_rand_int();
    utils::Timer timer;
    double getTimeDuration(int algorithmType);
private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_addRandButton_clicked();
    void on_addRandNButton_clicked();
    void on_shuffleButton_clicked();
    void on_sortButton_clicked();
    void on_removeAllButton_clicked();
};
#endif // MAINWINDOW_H
