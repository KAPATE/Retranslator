#include "mainwindow.h"
#include "ui_mainwindow.h"

constexpr unsigned int string2int(const char* str, int h) {
    return !str[h] ? 5381 : (string2int(str, h + 1) * 33) ^ str[h];
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QObject::connect(this, SIGNAL(sort_me(std::vector <std::string>,std::vector <std::string>,std::vector <std::string>,std::vector <std::string>,std::vector <std::string>, int ,int)),this,SLOT(get_sort(std::vector <std::string>,std::vector <std::string>,std::vector <std::string>,std::vector <std::string>,std::vector <std::string>, int ,int)));
    ui->setupUi(this);
    nameOfMainTable = "mainTable.txt";
    //ui->tableView->hide();
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
                case (string2int("add")): { //add process in MAIN table. example syntax: add { ie.exe , 800, 1, user, 2034 }
                std::vector <std::string> code = add(buffer);
                //std::reverse(std::begin(code), std::end(code));
                mainTable << std::setw(20) << code[code.size()-5]<< std::setw(8) << code[code.size()-4] << std::setw(10) << code[code.size()-3] << std::setw(15) << code[code.size()-2] << std::setw(5) << code[code.size()-1]<< std::endl;
                break;
                };

                case (string2int("delete")): { // deletes a row with specified ID. example syntax: delete 2034
                std::ifstream fin(nameOfMainTable.c_str());
                std::ofstream fout("temporary_file.txt");
                std::string line {};
                while (fin) {
                    std::getline(fin,line);
                    if (line.find(buffer.c_str()) == std::string::npos) fout << line << std::endl;
                    else continue;
                }
                fin.close();
                fout.close();
                remove(nameOfMainTable.c_str());
                rename("temporary_file.txt", nameOfMainTable.c_str());
                break;
                }

                case (string2int("sort")): {
                std::ifstream fin(nameOfMainTable);
                std::ofstream fout("temporary_file.txt");
                std::string line {};
                std::vector <std::string> xz ;
                QString priority = "priority";
                QString process = "process";
                QString memory = "memory";
                QString user = "user";
                QString id = "id";
                QString buff = buffer.data();
                std::string temporary {};
                std::getline(fin,temporary);
                while (fin) {
                    std::getline(fin,line);
                    xz.push_back(line.c_str());
                }
                std::vector <std::string> xz_rezerv;
                for (int i = 0; i < xz.size();i++)
                {
                    xz_rezerv.push_back(xz.at(i).c_str());
                }
                qDebug()<<buff << process << buff.compare(process);
                if (!buff.compare(process)) {
                    std::cout<< "before sort "<<xz.begin().base()<<" probel "<<xz.end().base()<<std::endl;
                    for (int i = 0; i < xz.size(); i++)
                    {
                        std::cout << xz.at(i) << std::endl;
                    }
                    std::sort(xz.begin(), xz.end());
                    std::cout<< " after sort"<<xz.begin().base()<<" "<<xz.end().base() <<std::endl;
                    for (int i = 0; i < xz.size(); i++)
                    {
                        std::cout << xz.at(i) << std::endl;
                    }
                }

                if (buff == memory) {
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    std::sort(xz.begin(), xz.end());

                    for (int i = 0; i<xz.size(); i++) {
                        for (int j = 0; j<xz.size(); j++) {
                            if (xz_rezerv.at(i).find(xz.at(j).c_str()) != std::string::npos) {
                                std::string buffer = xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz.at(j).c_str());
                                //std::cout << xz.at(j).c_str() << " its hz " << std::endl;
                                xz.at(j).clear();
                                xz.at(j).append(buffer.c_str());
                                //std::cout<<buffer.c_str()<<" its buffer "<<std::endl;
                                break;
                            }
                        }
                    }
                    for (int i = 0; i< xz.size(); i++) {
                        std::cout << xz.at(i) << std::endl;
                    }
                }

                if (buff == priority) {
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    std::sort(xz.begin(), xz.end());

                    for (int i = 0; i<xz.size(); i++) {
                        for (int j = 0; j<xz.size(); j++) {
                            if (xz_rezerv.at(i).find(xz.at(j).c_str()) != std::string::npos) {
                                std::string buffer = xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1);
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                buffer.append(xz.at(j).c_str());
                                std::cout << xz.at(j).c_str() << " its hz " << std::endl;
                                xz.at(j).clear();
                                xz.at(j).append(buffer.c_str());
                                std::cout<<buffer.c_str()<<" its buffer "<<std::endl;
                                break;
                            }
                        }
                    }
                    for (int i = 0; i< xz.size(); i++) {
                        std::cout << xz.at(i) << std::endl;
                    }
                }

                if (buff == user) {
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    std::sort(xz.begin(), xz.end());

                    for (int i = 0; i<xz.size(); i++) {
                        for (int j = 0; j<xz.size(); j++) {
                            if (xz_rezerv.at(i).find(xz.at(j).c_str()) != std::string::npos) {
                                std::string buffer = xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1);                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1)); xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1); buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                buffer.append(xz.at(j).c_str());
                                //std::cout << xz.at(j).c_str() << " its hz " << std::endl;
                                xz.at(j).clear();
                                xz.at(j).append(buffer.c_str());
                                //std::cout<<buffer.c_str()<< " its buffer "<<std::endl;
                                break;
                            }
                        }
                    }
                    for (int i = 0; i< xz.size(); i++) {
                        std::cout << xz.at(i) << std::endl;
                    }
                }

                if (buff == id) {
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    xz.at(0).erase(0, xz.at(0).find(" ") + 1);
                    xz.at(1).erase(0, xz.at(1).find(" ") + 1);
                    xz.at(2).erase(0, xz.at(2).find(" ") + 1);
                    xz.at(3).erase(0, xz.at(3).find(" ") + 1);
                    xz.at(4).erase(0, xz.at(4).find(" ") + 1);
                    xz.at(5).erase(0, xz.at(5).find(" ") + 1);
                    std::sort(xz.begin(), xz.end());

                    for (int i = 0; i<xz.size(); i++) {
                        for (int j = 0; j<xz.size(); j++) {
                            if (xz_rezerv.at(i).find(xz.at(j).c_str()) != std::string::npos) {
                                std::string buffer = xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1);
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                //xz_rezerv.at(i).erase(0,xz_rezerv.at(i).find(" ")+1);
                                //xz_rezerv.at(i).erase(0,xz_rezerv.at(i).find(" ")+1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz_rezerv.at(i).substr(0, xz_rezerv.at(i).find(" ") + 1));
                                xz_rezerv.at(i).erase(0, xz_rezerv.at(i).find(" ") + 1);
                                buffer.append(xz.at(j).c_str());
                                //std::cout << xz.at(j).c_str() << " its hz " << std::endl;
                                xz.at(j).clear();
                                xz.at(j).append(buffer.c_str());
                                //std::cout<<buffer.c_str()<<" its buffer "<<std::endl;
                                break;
                            }
                        }
                    }
                    for (int i = 0; i< xz.size(); i++) {
                        std::cout << xz.at(i) << std::endl;
                    }
                }
                fin.close();
                fout.close();
                break;
                };

                case (string2int("filter")): {
                break;
                };

            case (string2int("erase")): {
                if (buffer == "mainTable") break;
                else {
                    buffer.append(".txt");
                    remove(buffer.c_str());
                }
                break;
                };

                case (string2int("copy")): { //copy table from mainTable to %nameOfNewTable%. example syntax: copy table2
                std::ifstream fin(nameOfMainTable);
                buffer.append(".txt");
                std::ofstream fout(buffer, std::ios_base::trunc);
                while( std::getline( fin, buffer) ) fout << buffer << std::endl;
                fin.close();
                fout.close();
                break;
                };

                case (string2int("show")): { //show %tableName% in qTextBrowser. example syntax: show   table1
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

                case (string2int("append")): { //append %table2% with %table1%. example syntax: append table1,table2
                std::string outputBuffer {};
                std::string name = buffer.substr(0,buffer.find(','));
                name.append(".txt");
                std::ifstream fin(name, std::ios_base::binary);
                buffer.erase(0,buffer.find(',')+1);
                buffer.append(".txt");
                std::ofstream fout(buffer, std::ios_base::binary | std::ios_base::app);
                fout.seekp(0, std::ios_base::end);
                std::getline(fin,buffer);
                while (std::getline(fin, outputBuffer)) { fout << outputBuffer << std::endl; }
                fin.close();
                fout.close();
                break;
                };
                default: { break;}
            }
        }
        file.close();
        mainTable.close();
    }
}

void MainWindow::get_sort(std::vector <std::string> process, std::vector <std::string> memory, std::vector <std::string> priority, std::vector <std::string> user, std::vector <std::string> id, int rows, int cols)
{
    QStandardItemModel *model = new QStandardItemModel(rows,cols,this); //2 Rows and 3 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("PROCESS")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("MEMORY")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("PRIORITY")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("USER")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("ID")));
    for (int i =0; i< process.size()-1; i++){
            QStandardItem *firstRow = new QStandardItem(QString(process.at(i).c_str()));
            model->setItem(i,0,firstRow);
    }
    for (int i =0; i< memory.size()-1; i++){
            QStandardItem *firstRow = new QStandardItem(QString(memory.at(i).c_str()));
            model->setItem(i,1,firstRow);
    }
    //for (int i =0; i< priority.size()-1; i++){
    {
            QStandardItem *firstRow = new QStandardItem(QString(priority.at(1).c_str()));
            model->setItem(2,2,firstRow);}
    //}
    //for (int i =0; i< user.size()-1; i++){
{
            QStandardItem *firstRow = new QStandardItem(QString(user.at(2).c_str()));
            model->setItem(3,3,firstRow);}
    //}
    //for (int i =0; i< id.size()-1; i++){
{
            QStandardItem *firstRow = new QStandardItem(QString(id.at(1).c_str()));
            model->setItem(4,4,firstRow);}
    //}
    ui->tableView->setModel(model);
}
