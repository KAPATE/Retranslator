#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
     tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
            tr("Could not open file"));
            return;
        }
        QString contents = file.readAll().constData();
        std::string code = parser(contents.toStdString());
        //qDebug()<<QString::fromUtf8(code.c_str());
        //ui->textBrowser->setText(contents);
        file.close();
    }
}
