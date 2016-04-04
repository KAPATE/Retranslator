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
                std::ifstream fin(nameOfMainTable.c_str());
                std::ofstream fout("temporary_file.txt");
                std::string process {}, user {};
                std::int8_t priority {};
                std::int16_t memory {}, id {};
                while (fin) {
                    fin >> process >> memory >> priority >> user >> id;
                    std::cout << "kek" << process << priority << std::endl;
                }
                fin.close();
                fout.close();
                //remove(nameOfMainTable.c_str());
                //rename("temporary_file.txt", nameOfMainTable.c_str());
                break;
                };

                case (string2int("filter")): {
                break;
                };

                case (string2int("erase")): { //delete table. example syntax: erase table2
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
