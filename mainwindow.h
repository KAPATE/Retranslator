#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QFileDialog>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "analyzer.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include <QStandardItemModel>
#include <QStandardItem>
#include <functional>
#include <cctype>
#include <locale>

constexpr unsigned int string2int(const char* str, int h = 0);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    std::string fileName;
    std::string nameOfMainTable;
};

#endif // MAINWINDOW_H
