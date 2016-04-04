#include "mainwindow.h"
#include "ui_mainwindow.h"

constexpr unsigned int string2int(const char* str, int h) {
    return !str[h] ? 5381 : (string2int(str, h + 1) * 33) ^ str[h];
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    countTables = 0;
    nameOfMainTable = "mainTable.txt";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
     tr("Text Files (*.txt)")).toStdString();

    if (!fileName.empty()) {
        std::ifstream file;
        std::ofstream mainTable;
        std::string buffer {};
        file.open(fileName);
        mainTable.open(nameOfMainTable, std::ios_base::trunc);
        mainTable << std::setw(20) <<"Process" << std::setw(8) << "Memory" << std::setw(10) << "Priority" << std::setw(15) << "User" << std::setw(5) << "id" << std::endl;
        while (file) {
            std::getline(file,buffer);
            std::string command = buffer.substr(0,buffer.find(' '));
            buffer.erase(0,buffer.find(' '));
            char chars[] = "{}- ";
            for (unsigned int i = 0; i < strlen(chars); ++i)
            {
               buffer.erase (std::remove(buffer.begin(), buffer.end(), chars[i]), buffer.end());
            }
            switch (string2int(command.c_str())) {
                case (string2int("add")): { //add process in MAIN table. example syntax of input string: add { ie.exe , 800, 1, user, 2783 }
                std::vector <std::string> code = add(buffer);
                //std::reverse(std::begin(code), std::end(code));
                mainTable << std::setw(20) << code[code.size()-5]<< std::setw(8) << code[code.size()-4] << std::setw(10) << code[code.size()-3] << std::setw(15) << code[code.size()-2] << std::setw(5) << code[code.size()-1]<< std::endl;
                break;
                };

                case (string2int("delete")): {
                break;
                };

                case (string2int("sort")): {
                break;
                };

                case (string2int("erase")): {
                if (buffer == "mainTable"){
                    break;
                }
                else {
                    std::string name = "/home/trasher/qt_projects/build-retranslator-Desktop_Qt_5_5_0_GCC_64bit-Debug/";
                    name.append(buffer);
                    remove("c://123.txt");
                    std::cout<<"delete table "<<buffer<<std::endl;
                }
                };

                case (string2int("copy")): {
                std::ifstream fin(nameOfMainTable);
                buffer.append(".txt");
                std::ofstream fout(buffer, std::ios_base::trunc);
                while( std::getline( fin, buffer) ) fout << buffer << std::endl ;
                fin.close();
                fout.close();
                break;
                };

                case (string2int("show")): {
                buffer.append(".txt");
                std::ifstream fin(buffer);
                std::string code;
                while (fin) {
                    std::getline(fin,buffer);
                    code.append(buffer);
                    code.append("\n");
                }
                ui->textBrowser->setText(code.c_str());
                fin.close();
                break;
                };

                case (string2int("append")): {
/*
                std::ofstream of_a("a.txt", std::ios_base::binary | std::ios_base::app);
                std::ifstream if_b("b.txt", std::ios_base::binary);

                of_a.seekp(0, std::ios_base::end);
                of_a << if_b.rdbuf();
*/
                std::string name = buffer.substr(0,buffer.find(','));
                name.append(".txt");
                std::ifstream fin(name, std::ios_base::binary);
                buffer.erase(0,buffer.find(',')+1);
                buffer.append(".txt");
                std::ofstream fout(buffer, std::ios_base::binary | std::ios_base::app);
                fout.seekp(0, std::ios_base::end);
                fout << fin.rdbuf();
                //while( std::getline( fin, buffer) ) fout << buffer << std::endl;
                fin.close();
                fout.close();
                break;
                };

                case (string2int("filter")): {
                break;
                };

                 default: { break;}
            }
        }
        file.close();
        mainTable.close();
    }
}
