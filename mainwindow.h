#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "analyzer.h"

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
    QString fileName;

};

#endif // MAINWINDOW_H
